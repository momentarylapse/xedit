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

	Theme::load_default();

	font_init();
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
