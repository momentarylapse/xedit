#include "lib/xhui/xhui.h"
#include "lib/xhui/controls/Button.h"
#include "lib/xhui/controls/CheckBox.h"
#include "lib/xhui/controls/Label.h"
#include "lib/xhui/controls/ListView.h"
#include "lib/xhui/controls/Edit.h"
#include "lib/xhui/controls/Grid.h"
#include "lib/xhui/controls/DrawingArea.h"
#include "lib/xhui/controls/MultilineEdit.h"
#include "lib/os/msg.h"

#include "lib/xhui/Theme.h"
#include "lib/xhui/draw/font.h"

int main() {

	try {
		hui::init();
	} catch (Exception &e) {
		msg_error(e.message());
		return 1;
	}

	auto w = new hui::Window("test", 1024, 768);
	auto g = new hui::Grid("grid");
	auto g2 = new hui::Grid("grid2");
	auto ll = new hui::Label("label", "test");
	auto ed = new hui::Edit("edit", "bla");
	auto list = new hui::ListView("list", "a\\b\\c");
	w->add(g);
	g->add(ll, 0, 0);
	g->add(new hui::Button("button1", "a small test g"), 1, 0);
	g->add(new hui::Button("button2", "more test"), 1, 1);
	g->add(ed, 2, 0);
	g->add(new hui::Button("button3", "x"), 2, 1);
	g->add(new hui::DrawingArea("area"), 2, 2);
	g->add(g2, 1, 2);
	g2->add(new hui::CheckBox("checkbox", "bb"), 0, 0);
	g2->add(list, 0, 1);
	g2->add(new hui::MultilineEdit("multilineedit", "just a small\ntest"), 0, 2);

	list->add_string("1\\2\\3");
	list->add_string("hallo\\test\\3");
	list->add_string("1\\2\\3");

	w->event("button1", [] {
		msg_write("event button1 click");
	});
	w->event("button2", [ll] {
		msg_write("event button2 click");
		ll->set_string("x");
	});
	w->event_xp("area", "hui:draw", [] (Painter *p) {
		p->set_color(hui::Theme::_default.background_low);
		p->set_roundness(8);
		p->draw_rect(p->area());
		p->set_roundness(0);
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

		p->set_roundness(20);
		p->draw_rect({50, 300, 150, 250});
		((hui::Painter*)p)->softness = 10;
		p->draw_rect({50, 300, 300, 400});
		((hui::Painter*)p)->softness = 0;
	});
	w->event("edit", [ed] {
		msg_write("edit: " + ed->text);
	});

	hui::run();

	return 0;
}

