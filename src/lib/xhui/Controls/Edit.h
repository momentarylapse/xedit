#pragma once

#include "Control.h"

namespace hui {

class Edit : public Control {
public:
	Edit(Window *win, const string &id, const string &title);

	void get_content_min_size(int &w, int &h) override;

	void set_string(const string &s) override;

	//void on_mouse_enter() override;
	//void on_mouse_leave() override;
	//void on_left_button_down() override;
	//void on_left_button_up() override;
	void on_key_down(int key) override;

	void _draw(Painter *p) override;

	string text;
	int cursor_pos = 0;
};

}
