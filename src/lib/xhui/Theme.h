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

	float focus_frame_width;

	color background, background_button;
	color background_button_primary;
	color background_header, background_header_button;
	color background_hover, background_active;
	color background_low, background_low_hover, background_low_selected;
	color text, text_label, text_disabled;
	color border;

	static void load_default();
	static Theme _default;
};

}
