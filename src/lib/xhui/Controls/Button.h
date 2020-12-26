#pragma once

#include "Control.h"

namespace hui {



class Button : public Control {
public:
	Button(Window *win, const string &id, const string &title);

	void on_mouse_enter() override;
	void on_mouse_leave() override;
	void on_left_button_down() override;
	void on_left_button_up() override;

	void _draw(Painter *p) override;

	string title;
	State state;
};

}