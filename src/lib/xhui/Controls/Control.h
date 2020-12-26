#pragma once

#include "../../base/base.h"
#include "../../math/rect.h"

namespace hui {

class Painter;
class Window;

class Control : public VirtualBase {
	friend class Window;
public:
	Control(Window *win, const string &id);

	virtual void _draw(Painter *p);
	
	rect _area;
	string id;
	Window *window;
};

}