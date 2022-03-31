#pragma once

#include "xhui.h"
#include "../image/ImagePainter.h"
#include "../math/vec2.h"

namespace hui {

class Window;

class Painter : public ::Painter {
	public:

	Painter(Window *w);
	//virtual ~Painter();


	void _cdecl end();
	void _cdecl set_color(const color &c) override;
	void _cdecl set_font(const string &font, float size, bool bold, bool italic) override;
	void _cdecl set_font_size(float size) override;
	void _cdecl set_antialiasing(bool enabled) override {};
	void _cdecl set_line_width(float w) override {};
	void _cdecl set_line_dash(const Array<float> &dash, float offset) override {};
	void _cdecl set_fill(bool fill) override { this->fill = fill; };
	void _cdecl set_clip(const rect &r) override;
	void _cdecl draw_point(const vec2 &p) override {};
	void _cdecl draw_line(const vec2 &a, const vec2 &b) override {};
	void _cdecl draw_lines(const Array<vec2> &p) override {};
	void _cdecl draw_polygon(const Array<vec2> &p) override {};
	void _cdecl draw_rect(const rect &r) override;
	void _cdecl draw_circle(const vec2 &p, float radius) override {};
	void _cdecl draw_str(const vec2 &p, const string &str) override;
	float _cdecl get_str_width(const string &str) override;
	void _cdecl draw_image(const vec2 &p, const Image *image) override {};
	void _cdecl draw_mask_image(const vec2 &p, const Image *image) override {};

	void _cdecl set_transform(float rot[], const vec2 &offset);

	rect clip() const override { return rect::ID; };

	color _color;
	string font_name;
	//rect _clip;
	//Array<float> dash;
	//float dash_offset;
	//float line_width;
	//bool anti_aliasing;
	float offset_x, offset_y;
	bool fill;

	Window *window;
};

}
