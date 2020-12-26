#include "Label.h"
#include "../Painter.h"

namespace hui {

Label::Label(Window *w, const string &_id, const string &t) : Control(w, _id) {
	title = t;
	state = State::DEFAULT;

	expand_x = false;
	expand_y = false;
}

void Label::set_string(const string &s) {
	title = s;
	request_redraw();
}

void Label::get_content_min_size(int &w, int &h) {
	auto p = new Painter(window);
	w = p->get_str_width(title) + 20;
	h = max(40, int(p->font_size + 20));
	delete p;
}

void Label::_draw(Painter *p) {
	p->set_color(color(1, 0.7f, 0.7f, 0.7f));
	float w = p->get_str_width(title);
	p->draw_str(_area.mx() - w/2, _area.my() - p->font_size * 0.8f, title);
}

}
