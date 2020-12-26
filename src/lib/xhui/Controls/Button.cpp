#include "Button.h"
#include "../Painter.h"
#include "../../file/msg.h"

namespace hui {

Button::Button(Window *w, const string &_id, const string &t) : Control(w, _id) {
	state = State::DEFAULT;

	expand_x = true;
	expand_y = false;

	set_string(t);
}

void Button::set_string(const string &s) {
	title = s;
	request_redraw();
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
	auto p = new Painter(window);
	w = p->get_str_width(title) + 20;
	h = max(40, int(p->font_size + 20));
	delete p;
}

void Button::_draw(Painter *p) {
	if (state == State::HOVER) {
		p->set_color(color(1, 0.25f, 0.25f, 0.25f));
		p->draw_rect(_area);
	} else if (state == State::PRESSED) {
		p->set_color(color(1, 0.3f, 0.3f, 0.5f));
		p->draw_rect(_area);
	}
	p->set_color(color(1, 0.9f, 0.9f, 0.9f));
	float w = p->get_str_width(title);
	if (state == State::PRESSED)
		p->draw_str(_area.mx() - w/2 + 1, _area.my() - p->font_size * 0.8f + 1, title);
	else
		p->draw_str(_area.mx() - w/2, _area.my() - p->font_size * 0.8f, title);
	//p->set_color(color(1, 0.8f, 0.2f, 0.2f));
	//p->draw_rect(rect(200,250, 200,300));
}

}
