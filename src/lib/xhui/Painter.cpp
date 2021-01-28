#include "Painter.h"

#include "../nix/nix.h"
#include "../image/image.h"

#include <ft2build.h>
#include FT_FREETYPE_H


#include <cairo/cairo.h>
//#include <pango/pango.h>
#include <gtk/gtk.h>

namespace nix {
	matrix create_pixel_projection_matrix();
}


namespace hui {


nix::Texture *tex_text = nullptr;
nix::Texture *tex_white = nullptr;
nix::VertexBuffer *vb_rect = nullptr;
nix::Shader *shader = nullptr;
nix::Texture *tex_xxx = nullptr;

void cairo_render_text(const string &font_name, float font_size, const string &text, Align align, Image &im);


FT_Library ft2;
FT_Face face;
bool _nix_inited = false;

void init_nix() {
	nix::Init();
	tex_text = new nix::Texture();
	tex_white = new nix::Texture();
	Image im;
	im.create(8, 8, White);
	tex_white->overwrite(im);
	vb_rect = new nix::VertexBuffer("3f,3f,2f");
	vb_rect->create_rect(rect::ID, rect::ID);

	shader  = nix::Shader::create(
		"<VertexShader>\n"
		"#version 330 core\n"
		"#extension GL_ARB_separate_shader_objects : enable"
		"\n"
		"struct Matrix { mat4 model, view, project; };\n"
		"/*layout(binding = 0)*/ uniform Matrix matrix;\n"
		"\n"
		"layout(location = 0) in vec3 in_position;\n"
		"layout(location = 1) in vec3 in_normal;\n"
		"layout(location = 2) in vec2 in_uv;\n"
		"\n"
		"layout(location = 0) out vec2 out_uv;\n"
		"\n"
		"void main() {\n"
		"	gl_Position = matrix.project * matrix.view * matrix.model * vec4(in_position, 1);\n"
		"	out_uv = in_uv;\n"
		"}\n"
		"\n"
		"</VertexShader>\n"
		"<FragmentShader>\n"
		"#version 330 core\n"
		"#extension GL_ARB_separate_shader_objects : enable"
		"\n"
		"layout(location = 0) in vec2 in_uv;\n"
		"uniform sampler2D tex0;\n"
		"uniform vec4 _color_;\n"
		"out vec4 color;\n"
		"\n"
		"void main() {\n"
		"	color = texture(tex0, in_uv);\n"
		"	color *= _color_;\n"
		"}\n"
		"</FragmentShader>");
	shader->filename = "-my-shader-";


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
	FT_Set_Char_Size(face, 0, 32*64, 300, 300);
	auto glyph_index = FT_Get_Char_Index(face, 'A');
	msg_write(glyph_index);
	//errpr = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT); //load_flags);
	//error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL); //render_mode);
	error = FT_Load_Char(face, 'A', FT_LOAD_RENDER);
	msg_write(error);
	msg_write(face->glyph->bitmap.rows);
	msg_write(face->glyph->bitmap.width);
	msg_write(face->glyph->bitmap.pixel_mode);

	tex_xxx = new nix::Texture();
	im.create(face->glyph->bitmap.width, face->glyph->bitmap.rows, White);
	for (int i=0; i<face->glyph->bitmap.width; i++)
		for (int j=0; j<face->glyph->bitmap.rows; j++) {
			float f = (float)face->glyph->bitmap.buffer[i + j*face->glyph->bitmap.width] / 255.0f;
			im.set_pixel(i,j, color(f, 1,1,1));
		}
	tex_xxx->overwrite(im);

	_nix_inited = true;
}

Painter::Painter(Window *w) {
	window = w;
	glfwMakeContextCurrent(w->window);
	if (!_nix_inited)
		init_nix();
	_color = White;
	font_size = 12;
	font_name = "CAC Champagne";
	fill = true;


	int ww, hh;
	glfwGetWindowSize(window->window, &ww, &hh);
	width = (float)ww / ui_scale;
	height = (float)hh / ui_scale;



	nix::StartFrameGLFW(window->window);
	nix::SetProjectionMatrix(nix::create_pixel_projection_matrix() * matrix::scale(ui_scale, ui_scale, 1));
	nix::ResetToColor(color(1, 0.15f, 0.15f, 0.15f));
	nix::SetCull(CULL_NONE);
	nix::SetZ(false, false);



	nix::SetWorldMatrix(matrix::translation(vector(100, 100, 0)) * matrix::scale(100, 100, 1));

	nix::SetShader(shader);
	_color = White;
	nix::SetAlpha(ALPHA_SOURCE_ALPHA, ALPHA_SOURCE_INV_ALPHA);
	shader->set_color(shader->get_location("_color_"), _color);
	nix::SetTexture(tex_xxx);
	nix::DrawTriangles(vb_rect);
	nix::SetAlpha(ALPHA_NONE);
}

void Painter::end() {
	nix::EndFrameGLFW(window->window);
}

void Painter::set_font(const string &font, float size, bool bold, bool italic) {
	font_name = font;
	font_size = size;
}

void Painter::set_font_size(float size) {
	font_size = size;
}

void Painter::set_color(const color &c) {
	_color = c;
}

void Painter::draw_str(float x, float y, const string &str) {
	Image im;
	cairo_render_text(font_name, font_size * ui_scale, str, Align::LEFT, im);
	tex_text->overwrite(im);
	float w = im.width / ui_scale;
	float h = im.height / ui_scale;
	nix::SetWorldMatrix(matrix::translation(vector(x, y, 0)) * matrix::scale(w, h, 1));

	nix::SetShader(shader);
	nix::SetAlpha(ALPHA_SOURCE_ALPHA, ALPHA_SOURCE_INV_ALPHA);
	shader->set_color(shader->get_location("_color_"), _color);
	nix::SetTexture(tex_text);
	nix::DrawTriangles(vb_rect);
	nix::SetAlpha(ALPHA_NONE);
}

float Painter::get_str_width(const string &str) {
	Image im;
	cairo_render_text(font_name, font_size * ui_scale, str, Align::LEFT, im);
	tex_text->overwrite(im);
	return im.width / ui_scale;
}

void Painter::draw_rect(const rect &r) {
	nix::SetWorldMatrix(matrix::translation(vector(r.x1, r.y1, 0)) * matrix::scale(r.width(), r.height(), 1));

	nix::SetShader(shader);
	//nix::SetAlpha(ALPHA_SOURCE_ALPHA, ALPHA_SOURCE_INV_ALPHA);
	shader->set_color(shader->get_location("_color_"), _color);
	nix::SetTexture(tex_white);
	nix::DrawTriangles(vb_rect);
}



void cairo_render_text(const string &font_name, float font_size, const string &text, Align align, Image &im) {

	// initial surface size guess
	int w_surf = 200;
	int h_surf = font_size * 2;

	for (int i=0; i<2; i++) {

		cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w_surf, h_surf);
		cairo_t *cr = cairo_create(surface);

		cairo_set_source_rgba(cr, 0, 0, 0, 1);
		cairo_rectangle(cr, 0, 0, w_surf, h_surf);
		cairo_fill(cr);

		int x = 0, y = 0;

		cairo_set_source_rgba(cr, 1, 1, 1, 1);

		PangoLayout *layout = pango_cairo_create_layout(cr);
		PangoFontDescription *desc = pango_font_description_from_string((font_name + "," + f2s(font_size, 1)).c_str());
		pango_layout_set_font_description(layout, desc);
		pango_font_description_free(desc);

		if (align & Align::RIGHT)
			pango_layout_set_alignment(layout, PANGO_ALIGN_RIGHT);
		else if (align & Align::CENTER_H)
			pango_layout_set_alignment(layout, PANGO_ALIGN_CENTER);
		else
			pango_layout_set_alignment(layout, PANGO_ALIGN_LEFT);
		pango_layout_set_text(layout, (char*)text.data, text.num);
		//int baseline = pango_layout_get_baseline(layout) / PANGO_SCALE;
		int w_used, h_used;
		pango_layout_get_pixel_size(layout, &w_used, &h_used);


		if ((w_used <= w_surf and h_used <= h_surf) or (i == 1)) {


			pango_cairo_show_layout(cr, layout);
			g_object_unref(layout);

			cairo_surface_flush(surface);
			unsigned char *c0 = cairo_image_surface_get_data(surface);
			im.create(w_used, h_used, White);
			for (int y=0;y<h_used;y++) {
				unsigned char *c = c0 + 4 * y * w_surf;
				for (int x=0;x<w_used;x++) {
					float a = (float)c[1] / 255.0f;
					im.set_pixel(x, y, color(a, 1, 1, 1));
					c += 4;
				}
			}
			im.alpha_used = true;

			// finished
			i = 666;
		}

		w_surf = w_used;
		h_surf = h_used;
		//if (w_used > w_surf)
		//	std::cerr << "Text: too large!\n";
		cairo_destroy(cr);
		cairo_surface_destroy(surface);
	}
}

}
