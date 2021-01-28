#include "Painter.h"

#include "../nix/nix.h"
#include "../image/image.h"


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

void cairo_render_text(const string &font_name, float font_size, const string &text, Align align, Image &im);


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
