#pragma once

#include "Control.h"

namespace hui {



class DrawingArea : public Control {
public:
	DrawingArea(Window *win, const string &id);

	void _draw(Painter *p) override;
};

}