#include "Button.h"
#include "../Painter.h"
#include "../draw/font.h"
#include "../Theme.h"

namespace hui {

Button::Button(Window *w, const string &_id, const string &t) : Label(w, _id, t) {
	can_grab_focus = true;
	expand_x = true;
	expand_y = false;
}

void Button::on_left_button_down() {
	state = State::PRESSED;
	request_redraw();
}
void Button::on_left_button_up() {
	state = State::HOVER;
	request_redraw();

	window->handle_event(id, "hui:click");
}
void Button::on_mouse_enter() {
	state = State::HOVER;
	request_redraw();
}
void Button::on_mouse_leave() {
	state = State::DEFAULT;
	request_redraw();
}

void Button::get_content_min_size(int &w, int &h) {
	if (text_w < 0) {
		auto dim = font_get_text_dimensions(Theme::_default.font_name, Theme::_default.font_size, title);
		text_w = int(dim.bounding_width);
		text_h = int(dim.bounding_height);
	}
	w = text_w + Theme::_default.button_margin * 2;
	h = text_h + Theme::_default.button_margin * 2;
}

void Button::_draw(Painter *p) {
	color bg = Theme::_default.background_button;
	if (state == State::HOVER) {
		bg = Theme::_default.background_hover;
	} else if (state == State::PRESSED) {
		bg = Theme::_default.background_active;
	}
	p->set_color(bg);
	p->draw_rect(_area);
	p->set_color(Theme::_default.text);

	auto dim = font_get_text_dimensions(Theme::_default.font_name, Theme::_default.font_size, title);

	//if (state == State::PRESSED)
	//	p->draw_str(_area.mx() - w/2 + 1, _area.my() - p->font_size * 0.8f + 1, title);
	//else
		p->draw_str({_area.center().x - dim.bounding_width/2, _area.center().y - dim.bounding_height/2}, title);
	//p->set_color(color(1, 0.8f, 0.2f, 0.2f));
	//p->draw_rect(rect(200,250, 200,300));
}

}
