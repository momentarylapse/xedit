#pragma once

#include "Control.h"

namespace hui {


class Button : public Control {
public:
	Button(Window *win, const string &id, const string &title);

	void _draw(Painter *p) override;

	string title;
};

}