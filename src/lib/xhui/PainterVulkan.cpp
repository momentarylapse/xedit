#if HAS_LIB_VULKAN

#include "Painter.h"
#include "Theme.h"
#include "draw/font.h"

#include "../vulkan/vulkan.h"
#include "../image/image.h"


namespace hui {


Painter::Painter(Window *w) {
}

void Painter::end() {
}

void Painter::clear(const color &c) {
}

void Painter::set_font(const string &font, float size, bool bold, bool italic) {
	font_name = font;
	font_size = size;
	font::set_font(font, size* ui_scale);
}

void Painter::set_font_size(float size) {
	font_size = size;
	font::set_font(font_name, font_size* ui_scale);
}

void Painter::set_color(const color &c) {
	_color = c;
}

void Painter::draw_str(const vec2 &p, const string &str) {
	if (str.num == 0)
		return;
}

float Painter::get_str_width(const string &str) {
	return font::get_text_width(str);
}

void Painter::set_line_width(float width) {
	line_width = width;
}

void Painter::set_roundness(float radius) {
	corner_radius = radius;
}

void Painter::draw_arc(const vec2& p, float r, float w0, float w1) {
	//float w = (w0 + w1) / 2;
	draw_line({p.x + r * cos(w0), p.y - r * sin(w0)}, {p.x + r * cos(w1), p.y - r * sin(w1)});
	//draw_line({p.x + r * cos(w), p.y - r * sin(w)}, {p.x + r * cos(w1), p.y - r * sin(w1)});
}

void Painter::draw_rect(const rect &r) {
}

void Painter::draw_line(const vec2 &a, const vec2 &b) {
}

void Painter::draw_lines(const Array<vec2> &p) {
	for (int i=0; i<p.num-1; i++)
		draw_line(p[i], p[i+1]);
}


void Painter::set_transform(float rot[], const vec2 &offset) {
	offset_x = offset.x;
	offset_y = offset.y;
}

void Painter::set_clip(const rect &r) {
}

}

#endif
