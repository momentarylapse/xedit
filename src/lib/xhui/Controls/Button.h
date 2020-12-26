#pragma once

#include "Control.h"

namespace hui {



class Button : public Control {
public:
	Button(Window *win, const string &id, const string &title);

	void set_string(const string &s) override;

	void on_mouse_enter() override;
	void on_mouse_leave() override;
	void on_left_button_down() override;
	void on_left_button_up() override;

	void _draw(Painter *p) override;
	void get_content_min_size(int &w, int &h) override;

	string title;
	State state;
};

}