#include "font.h"
#include "../../image/image.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace hui {

static FT_Library ft2;
static FT_Face face;
static int dpi = 96;


void font_init() {
	auto error = FT_Init_FreeType(&ft2);
	if (error) {
		throw Exception("can not initialize freetype2 library");
	}
	error = FT_New_Face(ft2, "/usr/share/fonts/noto/NotoSans-Regular.ttf", 0, &face);
	if (error == FT_Err_Unknown_File_Format) {
		throw Exception("font unsupported");
	} else if (error) {
		throw Exception("font can not be loaded");
	}
}

void font_set_font(const string &font_name, float font_size) {
	FT_Set_Char_Size(face, 0, int(font_size*64.0f), dpi, dpi);
}

TextDimensions font_get_text_dimensions(const string &font_name, float font_size, const string &text) {
	auto utf32 = text.utf8_to_utf32();
	TextDimensions dim;

	font_set_font(font_name, font_size);

	//auto glyph_index = FT_Get_Char_Index(face, 'A');
	//msg_write(glyph_index);
	//errpr = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT); //load_flags);
	//error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL); //render_mode);

	int wmax = 0;
	int x = 0;
	int n = 1;

	for (int u: utf32) {
		if (u == '\n') {
			wmax = max(wmax, x);
			x = 0;
			n ++;
			continue;
		}
		int error = FT_Load_Glyph(face, u, FT_LOAD_DEFAULT); //load_flags);
		if (error)
			continue;
		//wmax = max(wmax, x + face->glyph->width);
		x += face->glyph->advance.x >> 6;
	}
	dim.bounding_width = max(x, wmax) + font_size*0.1f;
	dim.line_dy = font_size * 1.35f;
	dim.bounding_top_to_line = font_size;
	dim.bounding_height = dim.line_dy * n;
	return dim;
}


float font_get_text_width(const string &font_name, float font_size, const string &text) {
	auto dim = font_get_text_dimensions(font_name, font_size, text);
	return dim.bounding_width;
}

void font_render_text(const string &font_name, float font_size, const string &text, Align align, Image &im) {
	auto utf32 = text.utf8_to_utf32();

	font_set_font(font_name, font_size);

	//auto glyph_index = FT_Get_Char_Index(face, 'A');
	//msg_write(glyph_index);
	//errpr = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT); //load_flags);
	//error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL); //render_mode);

	auto dim = font_get_text_dimensions(font_name, font_size, text);

	int nn = 1;
	for (int u: utf32)
		if (u == '\n')
			nn ++;

	im.create(dim.bounding_width, dim.bounding_height, color(0,0,0,0));

	int x=0, y = dim.bounding_top_to_line;

	for (int u: utf32) {
		if (u == '\n') {
			x = 0;
			y += dim.line_dy;
			continue;
		}
		int error = FT_Load_Char(face, u, FT_LOAD_RENDER);
		if (error)
			continue;

		for (int i=0; i<face->glyph->bitmap.width; i++)
			for (int j=0; j<face->glyph->bitmap.rows; j++) {
				float f = (float)face->glyph->bitmap.buffer[i + j*face->glyph->bitmap.width] / 255.0f;
				im.set_pixel(x+face->glyph->bitmap_left+i,y-face->glyph->bitmap_top+j, color(f, 1,1,1));
			}
		x += face->glyph->advance.x >> 6;
	}
}

}
