#include "Edit.h"
#include "../Painter.h"
#include "../Theme.h"
#include "../draw/font.h"
#include "../../os/msg.h"

namespace hui {

Edit::Edit(const string &_id, const string &t) : Control(_id) {
	//state = State::DEFAULT;
	can_grab_focus = true;

	expand_x = true;
	expand_y = false;

	set_string(t);
}

void Edit::set_string(const string &s) {
	text = s;
	cursor_pos = text.num;
	request_redraw();
}

void Edit::get_content_min_size(int &w, int &h) {
	w = 80;
	h = 30;
}

void Edit::on_key_down(int key) {
	if (key == KEY_LEFT)
		cursor_pos = clamp(cursor_pos - 1, 0, text.num + 1);
	if (key == KEY_RIGHT)
		cursor_pos = clamp(cursor_pos + 1, 0, text.num + 1);
	if (key == KEY_BACKSPACE)
		if (cursor_pos > 0) {
			text = text.sub_ref(0, cursor_pos - 1) + text.sub_ref(cursor_pos);
			cursor_pos --;
			if (owner)
				owner->handle_event(id, "hui:changed");
		}
	if (key == KEY_DELETE)
		if (cursor_pos < text.num) {
			text = text.sub_ref(0, cursor_pos) + text.sub_ref(cursor_pos + 1);
			if (owner)
				owner->handle_event(id, "hui:changed");
		}

	auto insert = [this] (char c) {
		text = text.sub_ref(0, cursor_pos) + string(&c, 1) + text.sub_ref(cursor_pos);
		cursor_pos ++;
		if (owner)
			owner->handle_event(id, "hui:changed");
	};
	if (key >= KEY_A and key <= KEY_Z)
		insert('a' + (key - KEY_A));
	if (key >= KEY_0 and key <= KEY_9)
		insert('0' + (key - KEY_0));
	if (key == KEY_SPACE)
		insert(' ');

	request_redraw();
}

void Edit::_draw(Painter *p) {
	// background
	color bg = Theme::_default.background_button;
	p->set_color(bg);
	p->set_roundness(Theme::_default.button_radius);
	p->draw_rect(_area);

	// focus frame
	if (has_focus()) {
		p->set_color(Theme::_default.background_button_primary.with_alpha(0.6f));
		p->draw_rect(_area);

		float dr = Theme::_default.focus_frame_width;
		p->set_roundness(Theme::_default.button_radius - dr);
		p->set_color(bg);
		p->draw_rect(smaller_rect(_area, dr));
	}
	p->set_line_width(1);
	p->set_roundness(0);

	// text
	p->set_color(Theme::_default.text_label);
	auto dim = font::get_text_dimensions(text);
	float dx = Theme::_default.edit_margin_x;
	float y0 = _area.center().y - dim.inner_height()/2;
	p->draw_str({_area.x1 + dx, y0}, text);


	// cursor
	if (has_focus()) {
		font::set_font(Theme::_default.font_name, Theme::_default.font_size);
		auto dim = font::get_text_dimensions(text.sub_ref(0, cursor_pos));
		p->set_color(Theme::_default.text_label);
		float x = _area.x1 + dx + dim.bounding_width;
		p->draw_line({x, y0}, {x, y0 + Theme::_default.font_size});
	}
}

}
