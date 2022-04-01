#pragma once

#include "../../base/base.h"

class Image;

namespace hui {

enum class Align;

void font_init();

struct TextDimensions {
	float bounding_width;
	float bounding_height;
	float bounding_top_to_line;
	float line_dy;
};

void fontt_set_font(const string &font_name, float font_size);
float font_get_text_width(const string &font_name, float font_size, const string &text);
TextDimensions font_get_text_dimensions(const string &font_name, float font_size, const string &text);
void font_render_text(const string &font_name, float font_size, const string &text, Align align, Image &im);

}
