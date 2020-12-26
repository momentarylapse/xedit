#include "Window.h"
#include "xhui.h"
#include "Painter.h"
#include <stdio.h>


namespace hui {

Array<Window*> _windows_;


Window::Window(const string &title, int w, int h) {
	window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);


	glfwSetKeyCallback(window, _key_callback);
	glfwSetCursorPosCallback(window, _cursor_position_callback);
	glfwSetMouseButtonCallback(window, _mouse_button_callback);
	glfwSetScrollCallback(window, _scroll_callback);
	glfwSetWindowRefreshCallback(window, _refresh_callback);

	_windows_.add(this);
}

Window::~Window() {
	glfwDestroyWindow(window);
}


/*bool Window::get_key_up(int k) {
	if (k < 0 or k >= 256)
		return false;
	return !state.key[k] and state_prev.key[k];
}*/

int key_decode(int key) {
	for (int i=0; i<10; i++)
		if (key == GLFW_KEY_0 + i)
			return hui::KEY_0 + i;
	for (int i=0; i<26; i++)
		if (key == GLFW_KEY_A + i)
			return hui::KEY_A + i;
	for (int i=0; i<12; i++)
		if (key == GLFW_KEY_F1 + i)
			return hui::KEY_F1 + i;
	if (key == GLFW_KEY_ENTER)
				return hui::KEY_RETURN;
	if (key == GLFW_KEY_SPACE)
				return hui::KEY_SPACE;
	if (key == GLFW_KEY_BACKSPACE)
				return hui::KEY_BACKSPACE;
	if (key == GLFW_KEY_UP)
				return hui::KEY_UP;
	if (key == GLFW_KEY_DOWN)
				return hui::KEY_DOWN;
	if (key == GLFW_KEY_LEFT)
				return hui::KEY_LEFT;
	if (key == GLFW_KEY_RIGHT)
				return hui::KEY_RIGHT;
	if (key == GLFW_KEY_LEFT_SHIFT)
				return hui::KEY_LSHIFT;
	if (key == GLFW_KEY_RIGHT_SHIFT)
				return hui::KEY_RSHIFT;
	if (key == GLFW_KEY_LEFT_CONTROL)
				return hui::KEY_LCONTROL;
	if (key == GLFW_KEY_RIGHT_CONTROL)
				return hui::KEY_RCONTROL;
	if (key == GLFW_KEY_PAGE_UP)
				return hui::KEY_PAGE_UP;
	if (key == GLFW_KEY_PAGE_DOWN)
				return hui::KEY_PAGE_DOWN;
	if (key == GLFW_KEY_HOME)
				return hui::KEY_HOME;
	if (key == GLFW_KEY_END)
				return hui::KEY_END;
	if (key == GLFW_KEY_DELETE)
				return hui::KEY_DELETE;
	if (key == GLFW_KEY_INSERT)
				return hui::KEY_INSERT;
	if (key == GLFW_KEY_TAB)
				return hui::KEY_TAB;
	return -1;
}

int mods_decode(int mods) {
	int r = 0;
	if (mods == GLFW_MOD_SHIFT)
		r += hui::KEY_SHIFT;
	if (mods == GLFW_MOD_CONTROL)
		r += hui::KEY_CONTROL;
	if (mods == GLFW_MOD_ALT)
		r += hui::KEY_ALT;
	//if (mods == GLFW_MOD_SUPER)
	//	r += hui::KEY_SUPER;
	return r;
}


void Window::_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	int k = key_decode(key);
	if (k < 0)
		return;

	auto w = (Window*)glfwGetWindowUserPointer(window);

	if (action == GLFW_PRESS) {
		w->state.key[k] = true;
	} if (action == GLFW_RELEASE) {
		w->state.key[k] = false;
	}

	k += mods_decode(mods);
	//std::cout << "key " << k << "    " << key << " " << action << " " << mods << "\n";

	if (action == GLFW_PRESS) {
		//w->state.key
		w->_on_key_down(k);
	} if (action == GLFW_RELEASE) {
		w->_on_key_up(k);
	}
}

void Window::_cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
	//std::cout << "mouse " << xpos << " " << ypos << "\n";
	auto w = (Window*)glfwGetWindowUserPointer(window);
	w->state.mx = xpos;
	w->state.my = ypos;
	w->_on_mouse_move(xpos, ypos);

	//SEND_EVENT(on_mouse_move);
}

void Window::_mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	//std::cout << "button " << button << " " << action << " " << mods << "\n";
	auto w = (Window*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			w->_on_left_button_down();
		if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			w->_on_middle_button_down();
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
			w->_on_right_button_down();
	} else if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			w->_on_left_button_up();
		if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			w->_on_middle_button_up();
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
			w->_on_right_button_up();
	}
}

void Window::_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	//std::cout << "scroll " << xoffset << " " << yoffset << "\n";
	auto w = (Window*)glfwGetWindowUserPointer(window);
	w->state.scroll_x = xoffset;
	w->state.scroll_y = yoffset;
	w->_on_mouse_wheel(xoffset, yoffset);
}

void Window::_refresh_callback(GLFWwindow *window) {
	auto w = (Window*)glfwGetWindowUserPointer(window);
	w->_refresh_requested = true;
}

struct ColorScheme {
	color background;
	color text;
};

void Window::_on_left_button_down() {
	on_left_button_down();
}
void Window::_on_left_button_up() {
	on_left_button_up();
}
void Window::_on_middle_button_down() {
	on_middle_button_down();
}
void Window::_on_middle_button_up() {
	on_middle_button_up();
}
void Window::_on_right_button_down() {
	on_right_button_down();
}
void Window::_on_right_button_up() {
	on_right_button_up();
}
void Window::_on_mouse_move(float mx, float my) {
	on_mouse_move(mx, my);
}
void Window::_on_mouse_wheel(float dx, float dy) {
	on_mouse_wheel(dx, dy);
}
void Window::_on_key_down(int k) {
	on_key_down(k);
}
void Window::_on_key_up(int k) {
	on_key_up(k);
}


void Window::_on_draw() {
	//printf("draw...\n");

	auto p = new Painter(this);
	p->draw_str(100, 100, "a small test");
	p->set_color(color(1, 0.8f, 0.2f, 0.2f));
	p->draw_rect(rect(200,250, 200,300));
	p->end();
	_refresh_requested = false;
	delete p;
}

void Window::_handle_events() {

	if (_refresh_requested)
		_on_draw();

	if (glfwWindowShouldClose(window)) {
		//glfwWin
		//ddd
		printf("fake...close...\n");
		exit(0);
	}
}



}