#include "Control.h"
#include "../Painter.h"

namespace hui {

Control::Control(Window *w, const string &_id) {
	window = w;
	id = _id;
}

void Control::request_redraw() {
	window->redraw(id);
}

}
