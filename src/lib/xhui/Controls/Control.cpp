#include "Control.h"
#include "../Painter.h"

namespace hui {

Control::Control(Window *w, const string &_id) {
	window = w;
	id = _id;
}

void Control::_draw(Painter *p) {
	p->set_color(color(1, 0.3f, 0.3f, 0.3f));
	p->draw_rect(_area);
	p->set_color(color(1, 0.9f, 0.9f, 0.9f));
	p->draw_str(100, 100, "a small test");
	p->set_color(color(1, 0.8f, 0.2f, 0.2f));
	p->draw_rect(rect(200,250, 200,300));
}

}
