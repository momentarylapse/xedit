#include "lib/xhui/xhui.h"
#include "lib/xhui/Controls/Button.h"
#include "lib/xhui/Controls/Label.h"
#include "lib/xhui/Controls/Grid.h"
#include "lib/xhui/Controls/DrawingArea.h"
#include "lib/file/msg.h"

int main() {

	hui::init();

	auto w = new hui::Window("test", 800, 600);
	auto g = new hui::Grid(w, "grid");
	auto ll = new hui::Label(w, "label", "test");
	g->add(ll, 0, 0);
	g->add(new hui::Button(w, "button1", "a small test"), 1, 0);
	g->add(new hui::Button(w, "button2", "more test"), 1, 1);
	g->add(new hui::Button(w, "button3", "x"), 2, 1);
	g->add(new hui::DrawingArea(w, "area"), 2, 2);
	w->add(g);

	w->event("button1", [] {
			msg_write("event button1 click");
	});
	w->event("button2", [ll] {
		msg_write("event button2 click");
		ll->set_string("x");
	});
	w->event_xp("area", "hui:draw", [] (Painter *p) {
		p->set_color(Black);
		p->draw_rect(p->area());
		p->set_color(Red);
		p->set_font_size(25);
		p->draw_str({0, 0}, "Test");

	});

	hui::run();

	delete w;


	return 0;
}

