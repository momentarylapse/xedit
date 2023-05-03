#pragma once

#include "../image/color.h"

namespace hui {

class Theme {
public:
	string font_name;
	float font_size;

	float spacing, window_margin;
	float label_margin;
	float button_margin;
	float button_radius;

	color background, background_button;
	color background_header, background_header_button;
	color background_hover, background_active;
	color text, text_label;

	static void load_default();
	static Theme _default;
};

}
