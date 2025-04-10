#include "EditorWindow.h"

#include <lib/os/file.h>
#include <lib/os/filesystem.h>

#include "DocumentEditor.h"
#include <lib/xhui/xhui.h>
#include <lib/xhui/dialogs/FileSelectionDialog.h>
#include <lib/xhui/controls/MultilineEdit.h>

EditorWindow::EditorWindow() : obs::Node<Window>("", 800, 600) {
	from_source(R"foodelim(
Window test 'test' padding=0
	TabControl tab 'a' bar=no
)foodelim");

#ifdef OS_MAC
	int mod = xhui::KEY_SUPER;
#else
	int mod = xhui::KEY_CONTROL;
#endif

	set_key_code("new", xhui::KEY_N + mod);
	set_key_code("open", xhui::KEY_O + mod);
	set_key_code("save", xhui::KEY_S + mod);
	set_key_code("save-as", xhui::KEY_S + mod + xhui::KEY_SHIFT);
	set_key_code("next-document", xhui::KEY_TAB + xhui::KEY_CONTROL);


	event("new", [this] {
		create_document_editor();
	});
	event("open", [this] {
		xhui::FileSelectionDialog::ask(this, "open..", os::fs::current_directory(), {}).then([this] (const Path& filename) {
			auto e = create_document_editor();
			e->load(filename);
		});
		create_document_editor();
	});
}

DocumentEditor* EditorWindow::create_document_editor() {
	static int counter = 0;
	string id = format("edit-%d", counter ++);

	set_target("tab");
	add_control("MultilineEdit", "", document_editors.num, 0, id);
	auto edit = (xhui::MultilineEdit*)get_control(id);
	edit->set_option("focusframe", "no");
	edit->set_option("monospace", "");
	edit->set_option("fontsize", "15");


	auto e = new DocumentEditor(edit);
	document_editors.add(e);

	e->out_changed >> create_sink([this] {
		update_title();
	});


	set_active(e);

	return e;
}

void EditorWindow::set_active(DocumentEditor* editor) {
	active_editor = editor;
	int index = weak(document_editors).find(editor);
	set_int("tab", index);

	focus(editor->edit->id);
	update_title();
}

void EditorWindow::update_title() {
	if (active_editor)
		set_title(active_editor->title() + " - xedit");
}




