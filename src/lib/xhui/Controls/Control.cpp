#include "Control.h"
#include "../Painter.h"
#include "../../file/msg.h"

namespace hui {

Control::Control(Window *w, const string &_id) {
	window = w;
	id = _id;
	min_width_req = 0;
	min_height_req = 0;
	min_width = 0;
	min_height = 0;
	expand_x = true;
	expand_y = true;
	w->controls.add(this);
}

void Control::request_redraw() {
	window->redraw(id);
}

void Control::negotiate_min_size() {
	min_width = min_width_req;
	min_height = min_height_req;
}

void Control::negotiate_area(const rect &available) {
	_area = available;
}

}
