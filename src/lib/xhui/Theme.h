#pragma once

#include "../image/color.h"

namespace hui {

class Theme {
public:
	string font_name;
	float font_size;

	float spacing, window_margin;
	float label_margin;

	color background, background_hover, background_active;
	color text, text_label;

	static void load_default();
	static Theme _default;
};

}
