#include "DocumentEditor.h"

#include <HighlightScheme.h>

#include "parser/BaseParser.h"
#include <lib/os/file.h>
#include <lib/xhui/controls/MultilineEdit.h>

DocumentEditor::DocumentEditor(xhui::MultilineEdit* _edit) {
	edit = _edit;
}

void DocumentEditor::load(const Path& _filename) {
	filename = _filename;
	edit->set_string(os::fs::read_text(filename));

	// experiment...
//	edit->add_markup({5, 20, xhui::FontFlags::Bold, Red});
//	edit->add_markup({30, 40, xhui::FontFlags::Bold, Green});
	auto p = GetParser(filename);
	if (p)
		p->CreateTextColors(this);

	edit->clear_history();

	out_changed();
}

string DocumentEditor::title() const {
	if (filename.is_empty())
		return "new document";
	return filename.basename();
}

int DocumentEditor::get_num_lines() const {
	return edit->cache.lines.num;
}

string DocumentEditor::get_line(int line_no) const {
	return edit->cache.lines[line_no];
}

DocumentEditor::Index DocumentEditor::line_start(int line_no) const {
	return edit->cache.line_first_index[line_no];
}

DocumentEditor::Index DocumentEditor::line_end(int line_no) const {
	return edit->cache.line_first_index[line_no] + edit->cache.line_num_characters[line_no];
}

void DocumentEditor::mark_word(Index i0, Index i1, int type) {
	const auto& c = HighlightScheme::default_scheme->context[type];
	edit->add_markup({i0, i1, c.bold ? xhui::FontFlags::Bold : xhui::FontFlags::None, c.fg});
}


void DocumentEditor::clear_markings(int first_line, int last_line) {
	edit->clean_markup(line_start(first_line), line_end(last_line));
}






