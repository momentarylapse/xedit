#include "Label.h"
#include "../Painter.h"

namespace hui {

Label::Label(Window *w, const string &_id, const string &t) : Control(w, _id) {
	text_w = text_h = 0;
	state = State::DEFAULT;

	expand_x = false;
	expand_y = false;

	set_string(t);
}

void Label::set_string(const string &s) {
	title = s;
	text_w = text_h = -1;
	request_redraw();
}

void Label::get_content_min_size(int &w, int &h) {
	if (text_w < 0) {
		auto p = new Painter(window);
		text_w = p->get_str_width(title);
		text_h = int(p->font_size);
		delete p;
	}
	w = text_w + 16;
	h = text_h + 16;
}

void Label::_draw(Painter *p) {
	p->set_color(color(1, 0.7f, 0.7f, 0.7f));
	float w = p->get_str_width(title);
	p->draw_str({_area.mx() - w/2, _area.my() - p->font_size * 0.8f}, title);
}

}
