#pragma once

#include "../base/base.h"
#include "../math/vec2.h"
#include <GLFW/glfw3.h>

class Painter;

namespace hui {

class Control;
class Painter;

typedef std::function<void()> Callback;
typedef std::function<void(::Painter*)> CallbackP;

class Window : public VirtualBase {
	friend class Painter;
	friend class Control;
public:

	Window(const string &title, int width, int height);
	~Window() override;

	virtual void on_left_button_down() {}
	virtual void on_left_button_up() {}
	virtual void on_middle_button_down() {}
	virtual void on_middle_button_up() {}
	virtual void on_right_button_down() {}
	virtual void on_right_button_up() {}
	virtual void on_mouse_move(const vec2 &m) {}
	virtual void on_mouse_enter() {}
	virtual void on_mouse_leave() {}
	virtual void on_mouse_wheel(const vec2 &d) {}
	virtual void on_key_down(int key) {}
	virtual void on_key_up(int key) {}

	void _poll_events();

	void redraw(const string &id);

	void add(Control *c);
	void event(const string &id, Callback f);
	void event_x(const string &id, const string &msg, Callback f);
	void event_xp(const string &id, const string &msg, CallbackP f);

private:
	GLFWwindow *window;

	struct InputState {
		vec2 m;;
		vec2 scroll;
		bool lbut, mbut, rbut;
		bool key[256];
	} state, state_prev;

	static void _key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void _cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	static void _cursor_enter_callback(GLFWwindow *window, int enter);
	static void _mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
	static void _scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
	static void _refresh_callback(GLFWwindow *window);


	void _on_left_button_down();
	void _on_left_button_up();
	void _on_middle_button_down();
	void _on_middle_button_up();
	void _on_right_button_down();
	void _on_right_button_up();
	void _on_mouse_move(const vec2 &m);
	void _on_mouse_enter();
	void _on_mouse_leave();
	void _on_mouse_wheel(const vec2 &d);
	void _on_key_down(int key);
	void _on_key_up(int key);

	bool _refresh_requested = true;
	void _on_draw();

	Control *get_hover_control(const vec2 &p);

	Control *control;
	Array<Control*> controls;
	Control *hover_control;
	Control *focus_control;
	float padding;

	class EventHandler {
		public:
		EventHandler() {};
		string id, msg;
		Callback f;
		CallbackP fp;
	};
	Array<EventHandler> event_handlers;

public:
	void handle_event(const string &id, const string &msg);
	void handle_event_p(const string &id, const string &msg, Painter *p);
};

}
