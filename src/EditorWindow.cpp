#include "EditorWindow.h"
#include "DocumentEditor.h"
#include <lib/xhui/controls/MultilineEdit.h>

EditorWindow::EditorWindow() : obs::Node<Window>("", 800, 600) {
	from_source(R"foodelim(
Window test 'test' padding=0
	TabControl tab 'a' bar=no
)foodelim");
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




