#include "DocumentEditor.h"

#include <HighlightScheme.h>
#include <lib/base/iter.h>

#include "parser/BaseParser.h"
#include <lib/os/file.h>
#include <lib/xhui/Theme.h>
#include <lib/xhui/Window.h>
#include <lib/xhui/xhui.h>
#include <lib/xhui/controls/MultilineEdit.h>

DocumentEditor::DocumentEditor() = default;

void DocumentEditor::create_controls(xhui::Window* win, int index) {

	static int counter = 0;
	grid_id = format("grid-%d", counter);
	edit_id = format("edit-%d", counter);
	lines_id = format("lines-%d", counter);
	counter ++;

	win->set_target("tab");
	win->add_control("Grid", "", index, 0, grid_id);
	win->set_options(grid_id, "spacing=0");
	win->set_target(grid_id);
	win->add_control("DrawingArea", "", 0, 0, lines_id);
	win->set_options(lines_id, "width=50");
	win->add_control("MultilineEdit", "", 1, 0, edit_id);
	edit = (xhui::MultilineEdit*)win->get_control(edit_id);
	edit->set_option("focusframe", "no");
	edit->set_option("monospace", "");
	edit->set_option("fontsize", "14");
//	edit->set_option("fontsize", "13");
	edit->set_option("lineheightscale", "1.2f");
	edit->set_option("altbg", "");

	/*win->event(edit_id, [this, win] {
		int n = edit->cache.lines.num;
		int digits = log10(n);
		win->set_options(lines_id, "width=50");
	});*/

	win->event_xp(lines_id, xhui::event_id::Draw, [this] (Painter* p) {
		const rect area = p->area();
		p->set_color(xhui::Theme::_default.background);
		p->draw_rect(area);
		p->set_font("monospace", 14, false, false);
		int cursor_line = edit->index_to_line_pos(edit->cursor_pos).line;
		for (const auto& [l, y0]: enumerate(edit->cache.line_y0))
			if (y0 + edit->cache.line_height[l] > area.y1 and y0 < area.y2) {
				p->set_color(xhui::Theme::_default.text_disabled);
				if (l == cursor_line)
					p->set_color(xhui::Theme::_default.text);
				p->draw_str({area.x1, y0}, format("%3d", l+1));
			}
	});

	xhui::run_later(0.1f, [this, win] {
		win->request_redraw();
	});
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






