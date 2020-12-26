#include "xhui.h"
#include "Window.h"
#include "../file/msg.h"
#include "../nix/nix.h"

namespace hui {

extern Array<Window*> _windows_;

void init() {
	//msg_init();
	glfwInit();
}

void run() {
	while (true) {
		glfwPollEvents();

		for (auto w: _windows_)
			w->_handle_events();
	};
}

}