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

	virtual void set_string(const string &s) {};

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

	int min_width_user, min_height_user;
	bool expand_x, expand_y;
	bool ignore_hover = false;

	virtual void get_content_min_size(int &w, int &h);
	void get_effective_min_size(int &w, int &h);

	//virtual void negotiate_min_size();
	virtual void negotiate_area(const rect &available);


	enum class State {
		DEFAULT,
		HOVER,
		PRESSED,
		DISABLED
	};
};

}