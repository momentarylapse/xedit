#include "EditorWindow.h"
#include "dialogs/DocumentSwitcher.h"
#include <lib/xhui/xhui.h>
#include <lib/xhui/dialogs/FileSelectionDialog.h>
#include <lib/xhui/controls/MultilineEdit.h>
#include <lib/xhui/Theme.h>
#include <lib/os/file.h>
#include <lib/os/filesystem.h>
#include <lib/os/msg.h>
#include <lib/codeeditor/CodeEditor.h>

#include "lib/xhui/controls/TabControl.h"


void draw_boxed_str(Painter* p, const vec2& _pos, const string& str, int align, EditorWindow::Message::Type style) {
	vec2 size = p->get_str_size(str);
	vec2 pos = _pos;
	if (align == 0)
		pos.x -= size.x / 2;
	if (align == 1)
		pos.x -= size.x;
	if (style == EditorWindow::Message::Type::ERROR)
		p->set_color(color(1, 0.6f, 0.1f, 0.1f));
	else if (style == EditorWindow::Message::Type::WARNING)
		p->set_color(xhui::Theme::_default.background_button_danger);
	else
		p->set_color(xhui::Theme::_default.background_button);
	p->set_roundness(7);
	p->draw_rect(rect(pos, pos + size).grow(7));
	p->set_color(xhui::Theme::_default.text_label);
	p->set_roundness(0);
	p->draw_str(pos, str);
}

EditorWindow::EditorWindow() : obs::Node<Window>("", 800, 600) {
	from_source(R"foodelim(
Window test 'test' padding=0
	Grid ? ''
		FileSelector files '' width=250
		Overlay ? '' expandx
			TabControl tab 'a' bar=no
			DrawingArea overlay-area '' ignorehover
)foodelim");

	maximize(true);

#ifdef OS_MAC
	int mod = xhui::KEY_SUPER;
#else
	int mod = xhui::KEY_CONTROL;
#endif

#ifdef OS_MAC
	int key_next_doc = xhui::KEY_TAB + xhui::KEY_ALT;//xhui::KEY_CONTROL;
#else
	int key_next_doc = xhui::KEY_TAB + xhui::KEY_CONTROL;
#endif

	set_key_code("new", xhui::KEY_N + mod);
	set_key_code("open", xhui::KEY_O + mod);
	set_key_code("save", xhui::KEY_S + mod);
	set_key_code("save-as", xhui::KEY_S + mod + xhui::KEY_SHIFT);
	set_key_code("close-document", xhui::KEY_W + mod);
	set_key_code("next-document", key_next_doc);
	set_key_code("previous-document", key_next_doc + xhui::KEY_SHIFT);


	event("new", [this] {
		create_document_editor();
	});
	event("open", [this] {
		Path dir = os::fs::current_directory();
		if (active_editor and active_editor->filename)
			dir = active_editor->filename.parent();
		xhui::FileSelectionDialog::ask(this, "open..", dir, {}).then([this] (const Path& filename) {
			open_document(filename);
		});
	});
	event("save", [this] {
		if (!active_editor)
			return;
		if (active_editor->filename) {
			active_editor->save(active_editor->filename);
			info("saved");
		} else {
			xhui::FileSelectionDialog::ask(this, "save..", os::fs::current_directory(), {"save"}).then([this] (const Path& filename) {
				active_editor->save(filename);
				info("saved");
			});
		}
	});
	event("next-document", [this] {
		if (switcher) {
			switcher->next();
		} else {
			switcher = new DocumentSwitcher(this);
			open_dialog(switcher);
		}
	});
	event("previous-document", [this] {
		if (switcher) {
			switcher->previous();
		} else {
			switcher = new DocumentSwitcher(this);
			open_dialog(switcher);
		}
	});
	event("close-document", [this] {
		close_document(active_editor);
	});
	event_xp("overlay-area", xhui::event_id::Draw, [this] (Painter* p) {
		for (const auto& m : messages) {
			draw_boxed_str(p, p->area().center(), m.message, 0, m.type);
		}
	});

	set_options("files", "linkevents");
	set_options("files", format("directory=%s", os::fs::current_directory()));
	event("files", [this] {
		open_document(get_string("files"));
	});
}

void EditorWindow::on_key_up(int key_code) {
	int key = key_code & 0xff;
	if ((key == xhui::KEY_LCONTROL or key == xhui::KEY_LALT) and switcher) {
		switcher->request_destroy();
		switcher = nullptr;
	}
}


codeedit::CodeEditor* EditorWindow::create_document_editor() {
	auto e = new codeedit::CodeEditor();
	embed("tab", document_editors.num, 0, e);
	document_editors.add(e);

	e->out_changed >> create_sink([this] {
		update_title();
	});
	e->out_info >> create_data_sink<string>([this] (const string& m) {
		info(m);
	});
	e->out_error >> create_data_sink<string>([this] (const string& m) {
		error(m);
	});
	e->out_request_open_file >> create_data_sink<codeedit::CodeEditor::Location>([this] (const codeedit::CodeEditor::Location& l) {
		if (l.filename) {
			auto ee = open_document(l.filename);
			ee->edit->set_cursor_pos(l.offset);
		}
	});


	set_active(e);

	return e;
}

codeedit::CodeEditor* EditorWindow::open_document(const Path& _filename) {
	auto filename = _filename.absolute().canonical();

	for (auto e : weak(document_editors))
		if (e->filename == filename) {
			set_active(e);
			return e;
		}

	auto e = create_document_editor();
	e->load(filename);
	set_options("files", format("directory=%s", filename.parent()));
	return e;
}

void EditorWindow::set_active(codeedit::CodeEditor* editor) {
	active_editor = editor;
	int index = weak(document_editors).find(editor);
	set_int("tab", index);

	if (active_editor)
		active_editor->activate(editor->id_edit);
	update_title();
}

void EditorWindow::close_document(codeedit::CodeEditor* editor) {
	int index = weak(document_editors).find(editor);
	if (index < 0)
		return;
	codeedit::CodeEditor* next = nullptr;
	if (document_editors.num >= 2)
		next = weak(document_editors)[(index + 1) % document_editors.num];

	document_editors.erase(index);
	auto tab = get_control("tab");
	tab->remove_child(editor);

	set_active(next);
}

void EditorWindow::update_title() {
	if (active_editor) {
		string x;
		if (!active_editor->is_save_state())
			x = "*";
		set_title(active_editor->title() + x + " - xedit");
	}
}

void EditorWindow::add_message(Message::Type type, const string& message) {
	messages.add({type, message});
	xhui::run_later(4.0f, [this] {
		messages.erase(0);
		request_redraw();
	});
	request_redraw();
}

void EditorWindow::info(const string &message) {
	add_message(Message::Type::INFO, message);
}

void EditorWindow::error(const string &message) {
	add_message(Message::Type::ERROR, message);
}


