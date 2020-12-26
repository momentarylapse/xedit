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

	virtual void on_left_button_down() {}
	virtual void on_left_button_up() {}
	virtual void on_middle_button_down() {}
	virtual void on_middle_button_up() {}
	virtual void on_right_button_down() {}
	virtual void on_right_button_up() {}
	virtual void on_mouse_move(float mx, float my) {}
	virtual void on_mouse_enter() {}
	virtual void on_mouse_leave() {}
	virtual void on_mouse_wheel(float dx, float dy) {}
	virtual void on_key_down(int key) {}
	virtual void on_key_up(int key) {}

	virtual void _draw(Painter *p) {}

	void request_redraw();

	rect _area;
	string id;
	Window *window;


	enum class State {
		DEFAULT,
		HOVER,
		PRESSED,
		DISABLED
	};
};

}