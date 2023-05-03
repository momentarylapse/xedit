#include "lib/xhui/xhui.h"
#include "lib/xhui/Controls/Button.h"
#include "lib/xhui/Controls/Label.h"
#include "lib/xhui/Controls/Grid.h"
#include "lib/xhui/Controls/DrawingArea.h"
#include "lib/os/msg.h"

#include "lib/xhui/Theme.h"
#include "lib/xhui/draw/font.h"

int main() {

	hui::init();

	auto w = new hui::Window("test", 800, 600);
	auto g = new hui::Grid(w, "grid");
	auto ll = new hui::Label(w, "label", "test");
	g->add(ll, 0, 0);
	g->add(new hui::Button(w, "button1", "a small test g"), 1, 0);
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
		p->set_color(hui::Theme::_default.background_low);
		p->draw_rect(p->area());
		float font_size = 50;
		p->set_font_size(font_size);
		vec2 p0 = {20, 20};
		string text = "Test  g";
		auto dims = font::get_text_dimensions(text);
		p->set_color(hui::Theme::_default.border);
		p->draw_line({p0.x, p0.y + dims.bounding_top_to_line}, {p0.x + dims.bounding_width, p0.y + dims.bounding_top_to_line});
		p->set_fill(false);
		p->draw_rect(dims.bounding_box(p0));
		p->set_fill(true);

		p->set_color(hui::Theme::_default.text);
		p->draw_str(p0, text);

		//p->draw_str({50, 200}, "Test g\nbla gg");

	});

	hui::run();

	delete w;


	return 0;
}

