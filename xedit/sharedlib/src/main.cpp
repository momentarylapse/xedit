#include "EditorWindow.h"
#include <lib/codeeditor/CodeEditor.h>
#include <lib/syntaxhighlight/Theme.h>
#include <lib/syntaxhighlight/BaseParser.h>
#include <lib/os/msg.h>
#include <lib/xhui/xhui.h>
#include <lib/kaba/kaba.h>
#include <lib/kapi/KabaExporter.h>
#include <lib/kaba/Context.h>

#include "lib/os/msg.h"

bool app_init() {
	try {
		xhui::init({}, "xhui");
	} catch (Exception &e) {
		msg_error(e.message());
		return false;
	}

	syntaxhighlight::init();
	syntaxhighlight::default_theme = syntaxhighlight::get_theme("dark2");
	InitParser();
	return true;
}

void app_run(const Array<string>& args) {
	auto w = new EditorWindow();

	for (const auto& a: args)
		w->open_document(a);
	if (args.num == 0)
		w->create_document_editor();

	xhui::fly(w);

	xhui::run();
}

codeedit::CodeEditor* create_code_editor() {
	return new codeedit::CodeEditor();
}

extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::IExporter* e) {
	kaba::make_context_public(e);

	e->package_info("xedit", "0.1");

	e->declare_class_size("CodeEditor", sizeof(codeedit::CodeEditor));
	e->declare_class_element("CodeEditor.out_changed", &codeedit::CodeEditor::out_changed);
	e->declare_class_element("CodeEditor.out_info", &codeedit::CodeEditor::out_info);
	e->declare_class_element("CodeEditor.out_error", &codeedit::CodeEditor::out_error);
	e->declare_class_element("CodeEditor.out_request_open_file", &codeedit::CodeEditor::out_request_open_file);
	e->declare_class_element("CodeEditor.filename", &codeedit::CodeEditor::filename);
	e->declare_class_element("CodeEditor.id_edit", &codeedit::CodeEditor::id_edit);
	e->declare_class_element("CodeEditor.id_structure", &codeedit::CodeEditor::id_structure);
	e->link_class_func("CodeEditor.load", &codeedit::CodeEditor::load);
	e->link_class_func("CodeEditor.save", &codeedit::CodeEditor::save);
	e->link_class_func("CodeEditor.title", &codeedit::CodeEditor::title);
	e->link_class_func("CodeEditor.undo", &codeedit::CodeEditor::undo);
	e->link_class_func("CodeEditor.redo", &codeedit::CodeEditor::redo);
	e->link_class_func("CodeEditor.is_undoable", &codeedit::CodeEditor::is_undoable);
	e->link_class_func("CodeEditor.is_redoable", &codeedit::CodeEditor::is_redoable);
	e->link_class_func("CodeEditor.is_save_state", &codeedit::CodeEditor::is_save_state);
	e->link_class_func("CodeEditor.set_save_state", &codeedit::CodeEditor::set_save_state);

	e->link_func("create_code_editor", &create_code_editor);

	e->link_func("run", &app_run);

	if (!app_init())
		msg_error("failed to initialize...");
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}

