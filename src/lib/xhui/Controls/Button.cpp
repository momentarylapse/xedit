#include "Button.h"
#include "../Painter.h"

namespace hui {

Button::Button(Window *w, const string &_id, const string &t) : Control(w, _id) {
	title = t;
}

void Button::_draw(Painter *p) {
	p->set_color(color(1, 0.3f, 0.3f, 0.3f));
	p->draw_rect(_area);
	p->set_color(color(1, 0.9f, 0.9f, 0.9f));
	float w = p->get_str_width(title);
	p->draw_str(_area.width() / 2 - w/2, _area.height() / 2 - p->font_size / 2, title);
	p->set_color(color(1, 0.8f, 0.2f, 0.2f));
	p->draw_rect(rect(200,250, 200,300));
}

}
