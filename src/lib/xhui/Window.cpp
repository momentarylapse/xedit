#include "Window.h"
#include "xhui.h"
#include "Painter.h"
#include "Controls/Button.h"
#include "Controls/Grid.h"
#include "../file/msg.h"


namespace hui {

Array<Window*> _windows_;


Window::Window(const string &title, int w, int h) {
	window = glfwCreateWindow(w * ui_scale, h * ui_scale, title.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);

	padding = 10;
	auto g = new Grid(this, "grid");
	g->add(new Button(this, "button", "a small test"), 0, 0);
	g->add(new Button(this, "button", "more test"), 0, 1);
	control = g;

	event("button", [=] { msg_write("event button click"); });

	hover_control = nullptr;
	focus_control = nullptr;

	glfwSetKeyCallback(window, _key_callback);
	glfwSetCursorPosCallback(window, _cursor_position_callback);
	glfwSetCursorEnterCallback(window, _cursor_enter_callback);
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
	w->state.mx = xpos/ui_scale;
	w->state.my = ypos/ui_scale;
	w->_on_mouse_move(xpos/ui_scale, ypos/ui_scale);
}

void Window::_cursor_enter_callback(GLFWwindow *window, int enter) {
	auto w = (Window*)glfwGetWindowUserPointer(window);
	if (enter == 1)
		w->_on_mouse_enter();
	else
		w->_on_mouse_leave();
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

void Window::redraw(const string &id) {
	_refresh_requested = true;
}

struct ColorScheme {
	color background;
	color text;
};

void Window::_on_left_button_down() {
	if (hover_control)
		hover_control->on_left_button_down();
	on_left_button_down();
}
void Window::_on_left_button_up() {
	if (hover_control)
		hover_control->on_left_button_up();
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
	auto hover = get_hover_control(mx, my);
	if (hover != hover_control) {
		if (hover_control)
			hover_control->on_mouse_leave();
		hover_control = hover;
		if (hover_control)
			hover_control->on_mouse_enter();
	}
	on_mouse_move(mx, my);
}
void Window::_on_mouse_enter() {
	on_mouse_enter();
}
void Window::_on_mouse_leave() {
	if (hover_control) {
		hover_control->on_mouse_leave();
		hover_control = nullptr;
	}
	on_mouse_leave();
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

	auto p = new Painter(this);
	auto a = p->area();
	if (control) {
		control->negotiate_area(rect(a.x1 + padding, a.x2 - padding, a.y1 + padding, a.y2 - padding));
		control->_draw(p);
	}
	p->end();
	_refresh_requested = false;
	delete p;
}

void Window::_poll_events() {

	if (_refresh_requested)
		_on_draw();

	if (glfwWindowShouldClose(window)) {
		//glfwWin
		//ddd
		msg_write("fake...close...");
		exit(0);
	}
}

void Window::event(const string &id, Callback f) {
	EventHandler e;
	e.id = id;
	e.f = f;
	event_handlers.add(e);
}

void Window::handle_event(const string &id, const string &msg) {
	for (auto &e: event_handlers)
		if (e.id == id) {
			e.f();
		}
}

Control *Window::get_hover_control(float x, float y) {
	for (auto c: controls)
		if (c->_area.inside(x, y) and !c->ignore_hover)
			return c;
	return nullptr;
}


}