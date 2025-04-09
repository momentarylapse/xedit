#include "DocumentEditor.h"
#include <lib/os/file.h>
#include <lib/xhui/controls/MultilineEdit.h>

DocumentEditor::DocumentEditor(xhui::MultilineEdit* _edit) {
	edit = _edit;
}

void DocumentEditor::load(const Path& _filename) {
	filename = _filename;
	edit->set_string(os::fs::read_text(filename));

	// experiment...
	edit->add_markup({5, 20, xhui::FontFlags::Bold, Red});
	edit->add_markup({30, 40, xhui::FontFlags::Bold, Green});

	out_changed();
}

string DocumentEditor::title() const {
	if (filename.is_empty())
		return "new document";
	return filename.basename();
}



