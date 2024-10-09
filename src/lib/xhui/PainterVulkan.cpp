#if HAS_LIB_VULKAN

#include "Painter.h"
#include "Theme.h"
#include "draw/font.h"

#include "../vulkan/vulkan.h"
#include "../image/image.h"
#include "../os/msg.h"


using namespace vulkan;


namespace hui {


Instance *instance = nullptr;
DescriptorPool *pool = nullptr;
Device *device = nullptr;
Texture* tex_white = nullptr;
Texture* tex_black = nullptr;


	Fence* in_flight_fence;
	Array<Fence*> wait_for_frame_fences;
	Semaphore *image_available_semaphore, *render_finished_semaphore;

	Array<CommandBuffer*> command_buffers;

	SwapChain *swap_chain;
	RenderPass* render_pass;
	DepthBuffer* depth_buffer;
	Array<FrameBuffer*> frame_buffers;
	int image_index;
	bool framebuffer_resized;
	
	
	
void _create_swap_chain_and_stuff(GLFWwindow* window) {
	swap_chain = new vulkan::SwapChain(window, device);
	auto swap_images = swap_chain->create_textures();
	for (auto t: swap_images)
		wait_for_frame_fences.add(new vulkan::Fence(device));

	for (auto t: swap_images)
		command_buffers.add(device->command_pool->create_command_buffer());

	depth_buffer = swap_chain->create_depth_buffer();
	render_pass = swap_chain->create_render_pass(depth_buffer);
	frame_buffers = swap_chain->create_frame_buffers(render_pass, depth_buffer);
}

void api_init(GLFWwindow* window) {
	instance = vulkan::init({"glfw", "validation", "api=1.2", "verbosity=2"});
	device = Device::create_simple(instance, window, {"graphics", "present", "swapchain", "anisotropy", "validation"});
	msg_write("device found");

	//device->create_query_pool(MAX_TIMESTAMP_QUERIES);
	pool = new DescriptorPool("buffer:4096,sampler:4096", 65536);

	tex_white = new Texture();
	tex_black = new Texture();
	tex_white->write(Image(16, 16, White));
	tex_black->write(Image(16, 16, Black));

	//return new Context;
	
	

	image_available_semaphore = new vulkan::Semaphore(device);
	render_finished_semaphore = new vulkan::Semaphore(device);


	framebuffer_resized = false;

	_create_swap_chain_and_stuff(window);
}


void rebuild_default_stuff(GLFWwindow* window) {
	msg_write("recreate swap chain");

	device->wait_idle();

	//_delete_swap_chain_and_stuff();
	_create_swap_chain_and_stuff(window);
}

CommandBuffer* cb;


Painter::Painter(Window *w) {
	window = w;
	glfwMakeContextCurrent(w->window);
	if (!instance)
		api_init(w->window);
		
		
	// start frame
	
	if (!swap_chain->acquire_image(&image_index, image_available_semaphore)) {
		rebuild_default_stuff(w->window);
		return;
	}

	auto f = wait_for_frame_fences[image_index];
	f->wait();
	f->reset();
	
	cb = command_buffers[image_index];
	auto fb = frame_buffers[image_index];
	
	
	cb->begin();

	cb->set_viewport({0, (float)swap_chain->width, 0, (float)swap_chain->height});
	cb->begin_render_pass(render_pass, fb);
}

void Painter::end() {

	cb->end_render_pass();
	cb->end();


	auto f = wait_for_frame_fences[image_index];
	device->present_queue.submit(command_buffers[image_index], {image_available_semaphore}, {render_finished_semaphore}, f);

	swap_chain->present(image_index, {render_finished_semaphore});

	device->wait_idle();
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
