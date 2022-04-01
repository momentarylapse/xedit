#include "Painter.h"
#include "Theme.h"
#include "draw/font.h"

#include "../nix/nix.h"
#include "../image/image.h"

namespace nix {
	mat4 create_pixel_projection_matrix();
	extern mat4 projection_matrix,view_matrix,model_matrix;
}


namespace hui {


nix::Texture *tex_text = nullptr;
nix::Texture *tex_white = nullptr;
nix::VertexBuffer *vb_rect = nullptr;
nix::Shader *shader = nullptr;
nix::Texture *tex_xxx = nullptr;

bool _nix_inited = false;

void init_nix() {
	nix::init();
	tex_text = new nix::Texture();
	tex_white = new nix::Texture();
	Image im;
	im.create(8, 8, White);
	tex_white->write(im);
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


	tex_xxx = new nix::Texture();

	_nix_inited = true;
}

Painter::Painter(Window *w) {
	window = w;
	glfwMakeContextCurrent(w->window);
	if (!_nix_inited)
		init_nix();
	_color = Theme::_default.text;
	font_size = Theme::_default.font_size;
	font_name = Theme::_default.font_name;//"CAC Champagne";
	fill = true;

	offset_x = 0;
	offset_y = 0;


	int ww, hh;
	glfwGetWindowSize(window->window, &ww, &hh);
	width = (float)ww / ui_scale;
	height = (float)hh / ui_scale;



	nix::start_frame_glfw(window->window);
	nix::set_projection_matrix(nix::create_pixel_projection_matrix() * mat4::translation({0,0,0.5f}) * mat4::scale(ui_scale, ui_scale, 1));
	//nix::clear(color(1, 0.15f, 0.15f, 0.3f));
	nix::set_cull(nix::CullMode::NONE);
	nix::set_z(false, false);
}

void Painter::end() {
	nix::end_frame_glfw(window->window);
}

void Painter::clear(const color &c) {
	nix::clear(c);
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
	font_render_text(font_name, font_size * ui_scale, str, Align::LEFT, im);
	tex_text->write(im);
	float w = im.width / ui_scale;
	float h = im.height / ui_scale;
	nix::set_model_matrix(mat4::translation(vec3(offset_x + p.x, offset_y + p.y, 0)) * mat4::scale(w, h, 1));

	nix::set_shader(shader);
	nix::set_alpha_sd(nix::Alpha::SOURCE_ALPHA, nix::Alpha::SOURCE_INV_ALPHA);
	shader->set_color("_color_", _color);
	nix::set_texture(tex_text);
	nix::draw_triangles(vb_rect);
	nix::disable_alpha();
}

float Painter::get_str_width(const string &str) {
	return font_get_text_width(font_name, font_size /* * ui_scale*/, str);
}

void Painter::draw_rect(const rect &r) {
	nix::set_model_matrix(mat4::translation(vec3(offset_x + r.x1, offset_y + r.y1, 0)) * mat4::scale(r.width(), r.height(), 1));
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

}
