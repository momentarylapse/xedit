#pragma once

#include "xhui.h"
#include "../image/ImagePainter.h"

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
	void _cdecl draw_point(float x, float y) override {};
	void _cdecl draw_line(float x1, float y1, float x2, float y2) override {};
	void _cdecl draw_lines(const Array<complex> &p) override {};
	void _cdecl draw_polygon(const Array<complex> &p) override {};
	void _cdecl draw_rect(float x1, float y1, float w, float h) override { draw_rect(rect(x1, x1+w, y1, y1+h)); };
	void _cdecl draw_rect(const rect &r) override;
	void _cdecl draw_circle(float x, float y, float radius) override {};
	void _cdecl draw_str(float x, float y, const string &str) override;
	float _cdecl get_str_width(const string &str) override;
	void _cdecl draw_image(float x, float y, const Image *image) override {};
	void _cdecl draw_mask_image(float x, float y, const Image *image) override {};
	void _cdecl set_transform(float rot[], const complex &offset) override;

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