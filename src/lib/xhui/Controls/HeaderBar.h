#pragma once

#include "Control.h"

namespace hui {



class HeaderBar : public Control {
public:
	HeaderBar(Window *win, const string &id);

	void _draw(Painter *p) override;
	void get_content_min_size(int &w, int &h) override;

	void on_left_button_down(const vec2& m) override;
	void on_left_button_up(const vec2& m) override;
	void on_mouse_move(const vec2& m, const vec2& d) override;

	bool dragging = false;
	vec2 drag_m0;
	int window_pos_x0;
	int window_pos_y0;
};

}
