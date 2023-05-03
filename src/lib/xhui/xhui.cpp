#include "xhui.h"
#include "Window.h"
#include "Theme.h"
#include "draw/font.h"
#include <unistd.h>

namespace hui {

float ui_scale = 1.0f;

extern Array<Window*> _windows_;

void init() {
	//msg_init();
	glfwInit();

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	Theme::load_default();

	font::init();
}

void run() {
	while (true) {
		glfwPollEvents();

		for (auto w: _windows_)
			w->_poll_events();
		usleep(8000);
	};
}

}
