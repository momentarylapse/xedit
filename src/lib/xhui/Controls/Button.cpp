#include "Button.h"
#include "../Painter.h"
#include "../../file/msg.h"

namespace hui {

Button::Button(Window *w, const string &_id, const string &t) : Control(w, _id) {
	title = t;
	state = State::DEFAULT;
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
		p->draw_str(_area.width() / 2 - w/2 + 1, _area.height() / 2 - p->font_size / 2 + 2, title);
	else
		p->draw_str(_area.width() / 2 - w/2, _area.height() / 2 - p->font_size / 2, title);
	//p->set_color(color(1, 0.8f, 0.2f, 0.2f));
	//p->draw_rect(rect(200,250, 200,300));
}

}
