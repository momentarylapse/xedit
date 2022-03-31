#include "Painter.h"

#include "../nix/nix.h"
#include "../image/image.h"

#include "../file/msg.h"

#include <ft2build.h>
#include FT_FREETYPE_H

//#define USE_CAIRO 1


#ifdef USE_CAIRO
#include <cairo/cairo.h>
//#include <pango/pango.h>
#include <gtk/gtk.h>
#endif

namespace nix {
	matrix create_pixel_projection_matrix();
	extern matrix projection_matrix,view_matrix,model_matrix;
}


namespace hui {


nix::Texture *tex_text = nullptr;
nix::Texture *tex_white = nullptr;
nix::VertexBuffer *vb_rect = nullptr;
nix::Shader *shader = nullptr;
nix::Texture *tex_xxx = nullptr;

void cairo_render_text(const string &font_name, float font_size, const string &text, Align align, Image &im);
void ft_render_text(const string &font_name, float font_size, const string &text, Align align, Image &im);
float ft_get_text_width(const string &font_name, float font_size, const string &text);
void ft_set_font(const string &font_name, float font_size);


FT_Library ft2;
FT_Face face;
static int dpi = 96;
bool _nix_inited = false;

void init_nix() {
	nix::init();
	tex_text = new nix::Texture();
	tex_white = new nix::Texture();
	Image im;
	im.create(8, 8, White);
	tex_white->override(im);
	vb_rect = new nix::VertexBuffer("3f,3f,2f");
	vb_rect->create_quad(rect::ID, rect::ID);



#if 0
	<VertexShader>
	#version 330 core
	#extension GL_ARB_separate_shader_objects : enable

	struct Matrix { mat4 model, view, project; };
	/*layout(binding = 0)*/ uniform Matrix matrix;

	layout(location = 0) in vec3 in_position;
	layout(location = 1) in vec3 in_normal;
	layout(location = 2) in vec2 in_uv;

	layout(location = 0) out vec2 out_uv;

	void main() {
		gl_Position = matrix.project * matrix.view * matrix.model * vec4(in_position, 1);
		out_uv = in_uv;
	}

	</VertexShader>
#endif


	shader  = nix::Shader::create(
			R"foodelim(
<Layout>
	version = 330 core
</Layout>
<VertexShader>

#extension GL_ARB_separate_shader_objects : enable

struct Matrix { mat4 model, view, project; };
/*layout(binding = 0)*/ uniform Matrix matrix;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;

layout(location = 0) out vec3 out_normal;
layout(location = 1) out vec2 out_uv;
layout(location = 2) out vec4 out_pos; // camera space

void main() {
	gl_Position = matrix.project * matrix.view * matrix.model * vec4(in_position, 1);
	out_normal = (matrix.view * matrix.model * vec4(in_normal, 0)).xyz;
	out_uv = in_uv;
}
</VertexShader>
<FragmentShader>
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 in_normal;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec4 in_pos;
uniform sampler2D tex0;
uniform vec4 _color_;
out vec4 out_color;

void main() {
	out_color = texture(tex0, in_uv);
	out_color *= _color_;
}
</FragmentShader>
)foodelim");
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

	tex_xxx = new nix::Texture();
	ft_render_text("xxx", 25, u8"Hallo, test bla bla bla 923847298347\nÖÄÜßöäü 典范条目", Align::LEFT, im);
	tex_xxx->override(im);

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

	offset_x = 0;
	offset_y = 0;


	int ww, hh;
	glfwGetWindowSize(window->window, &ww, &hh);
	width = (float)ww / ui_scale;
	height = (float)hh / ui_scale;



	nix::start_frame_glfw(window->window);
	nix::set_projection_matrix(nix::create_pixel_projection_matrix() * matrix::scale(ui_scale, ui_scale, 1));
	nix::clear(color(1, 0.15f, 0.15f, 0.15f));
	//nix::clear(color(1, 0.15f, 0.15f, 0.3f));
	nix::set_cull(nix::CullMode::NONE);
	nix::set_z(false, false);
}

void Painter::end() {
	nix::end_frame_glfw(window->window);
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

void Painter::draw_str(const vec2 &p, const string &str) {
	Image im;
	ft_render_text(font_name, font_size * ui_scale, str, Align::LEFT, im);
	tex_text->override(im);
	float w = im.width / ui_scale;
	float h = im.height / ui_scale;
	nix::set_model_matrix(matrix::translation(vector(offset_x + p.x, offset_y + p.y, 0)) * matrix::scale(w, h, 1));

	nix::set_shader(shader);
	nix::set_alpha_sd(nix::Alpha::SOURCE_ALPHA, nix::Alpha::SOURCE_INV_ALPHA);
	shader->set_color("_color_", _color);
	nix::set_texture(tex_text);
	nix::draw_triangles(vb_rect);
	nix::disable_alpha();
}

float Painter::get_str_width(const string &str) {
#ifdef USE_CAIRO
	Image im;
	cairo_render_text(font_name, font_size * ui_scale, str, Align::LEFT, im);
	tex_text->overwrite(im);
	return im.width / ui_scale;
#endif
	return ft_get_text_width(font_name, font_size /* * ui_scale*/, str);
}

void Painter::draw_rect(const rect &r) {
	nix::set_model_matrix(matrix::translation(vector(offset_x + r.x1, offset_y + r.y1, 0)) * matrix::scale(r.width(), r.height(), 1));
	nix::set_shader(shader);
	//nix::SetAlpha(ALPHA_SOURCE_ALPHA, ALPHA_SOURCE_INV_ALPHA);
	shader->set_color("_color_", _color);
	nix::set_texture(tex_white);
	nix::draw_triangles(vb_rect);
}



void Painter::set_transform(float rot[], const vec2 &offset) {
	offset_x = offset.x;
	offset_y = offset.y;
}

void Painter::set_clip(const rect &r) {
	nix::set_scissor(r);
}


void ft_set_font(const string &font_name, float font_size) {
	FT_Set_Char_Size(face, 0, int(font_size*64.0f), dpi, dpi);
}

float ft_get_text_width(const string &font_name, float font_size, const string &text) {
	auto utf32 = text.utf8_to_utf32();

	ft_set_font(font_name, font_size);

	//auto glyph_index = FT_Get_Char_Index(face, 'A');
	//msg_write(glyph_index);
	//errpr = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT); //load_flags);
	//error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL); //render_mode);

	int wmax = 0;
	int x = 0;

	for (int u: utf32) {
		if (u == '\n') {
			wmax = max(wmax, x);
			x = 0;
			continue;
		}
		int error = FT_Load_Glyph(face, u, FT_LOAD_DEFAULT); //load_flags);
		if (error)
			continue;
		//wmax = max(wmax, x + face->glyph->width);
		x += face->glyph->advance.x >> 6;
	}
	return max(x, wmax) + font_size*0.1f;
}

void ft_render_text(const string &font_name, float font_size, const string &text, Align align, Image &im) {
	auto utf32 = text.utf8_to_utf32();

	ft_set_font(font_name, font_size);

	//auto glyph_index = FT_Get_Char_Index(face, 'A');
	//msg_write(glyph_index);
	//errpr = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT); //load_flags);
	//error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL); //render_mode);

	int h_per_line = font_size * 1.7f;
	int w = ft_get_text_width(font_name, font_size, text);

	int nn = 1;
	for (int u: utf32)
		if (u == '\n')
			nn ++;

	im.create(w, h_per_line * nn, color(0,0,0,0));

	int x=0, y = font_size * 1.35f;

	for (int u: utf32) {
		if (u == '\n') {
			x = 0;
			y += h_per_line;
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

#ifdef USE_CAIRO

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

#endif

}
