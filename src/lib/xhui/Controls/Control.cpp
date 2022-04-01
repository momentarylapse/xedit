#include "Control.h"
#include "../Painter.h"
#include "../../os/msg.h"

namespace hui {

Control::Control(Window *w, const string &_id) {
	window = w;
	id = _id;
	min_width_user = -1;
	min_height_user = -1;
	expand_x = true;
	expand_y = true;
	w->controls.add(this);
}

void Control::request_redraw() {
	window->redraw(id);
}

void Control::get_content_min_size(int &w, int &h) {
	w = 0;
	h = 0;
}

void Control::get_greed_factor(float &x, float &y) {
	x = y = 0;
	if (expand_x)
		x = 1;
	if (expand_y)
		y = 1;
}

void Control::get_effective_min_size(int &w, int &h) {
	get_content_min_size(w, h);
	if (min_width_user >= 0)
		w = min_width_user;
	if (min_height_user >= 0)
		h = min_height_user;
}

void Control::negotiate_area(const rect &available) {
	_area = available;
}

}
