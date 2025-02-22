#include "lib/xhui/xhui.h"
#include "lib/xhui/controls/Button.h"
#include "lib/xhui/controls/CheckBox.h"
#include "lib/xhui/controls/Label.h"
#include "lib/xhui/controls/ListView.h"
#include "lib/xhui/controls/Edit.h"
#include "lib/xhui/controls/Grid.h"
#include "lib/xhui/controls/DrawingArea.h"
#include "lib/xhui/controls/MultilineEdit.h"
#include "lib/xhui/controls/SpinButton.h"
#include "lib/os/msg.h"

#include "lib/xhui/Theme.h"
#include "lib/xhui/draw/font.h"

int xhui_main(const Array<string>& args) {

	try {
		xhui::init({""}, "xhui");
	} catch (Exception &e) {
		msg_error(e.message());
		return 1;
	}

	auto w = new xhui::Window("test", 600,400);//1024, 768);
	w->from_source(R"foodelim(
Window test 'test'
	Grid grid ''
		Label label 'test'
		Button button1 'a small test g'
		Edit edit 'bla'
		---|
		.
		Button button2 'more test'
		Button button3 'x'
		---|
		.
		Grid grid2 '' vertical
			CheckBox checkbox 'bb'
			SpinButton spin '13' range=0:20:0.1
			ListView list 'a\\b\\c'
			MultilineEdit multilineedit 'just a small\ntest'
		Viewport vp '' noexpandy
			Grid ? '' vertical
				Label ? 'a'
				Label ? 'a'
				Label ? 'a'
				Button ? 'xhgfhgf'
				Label ? 'a'
				Label ? 'a'
				Label ? 'a'
				Label ? 'a'
				Label ? 'a'
				Label ? 'a'
				Label ? 'a'
				Label ? 'a'
				Label ? 'a'
		---|
		.
		.
		Button ? 'hjk'
)foodelim");
	//	DrawingArea area ''

	w->add_string("list", "1\\2\\3");
	w->add_string("list", "hallo\\test\\3");
	w->add_string("list", "1\\2\\3");
	w->add_string("list", "1\\2\\3");
	w->add_string("list", "1\\2\\3");
	w->add_string("list", "1\\2\\3");

	w->event("button1", [] {
		msg_write("event button1 click");
	});
	w->event("button2", [w] {
		msg_write("event button2 click");
		w->set_string("label", "x");
	});
	w->event_xp("area", "hui:draw", [] (Painter *p) {
		return;
		p->set_color(xhui::Theme::_default.background_low);
		p->set_roundness(8);
		p->draw_rect(p->area());
		p->set_roundness(0);
		float font_size = 50;
		p->set_font_size(font_size);
		vec2 p0 = {20, 20};
		string text = "Test  g";
		auto dims = font::get_text_dimensions(text);
		p->set_color(xhui::Theme::_default.border);
		p->draw_line({p0.x, p0.y + dims.bounding_top_to_line}, {p0.x + dims.bounding_width, p0.y + dims.bounding_top_to_line});
		p->set_fill(false);
		p->draw_rect(dims.bounding_box(p0));
		p->set_fill(true);

		p->set_color(xhui::Theme::_default.text);
		p->draw_str(p0, text);

		//p->draw_str({50, 200}, "Test g\nbla gg");

		p->set_roundness(20);
		p->draw_rect({50, 300, 150, 250});
		((xhui::Painter*)p)->softness = 10;
		p->draw_rect({50, 300, 300, 400});
		((xhui::Painter*)p)->softness = 0;
	});
	w->event("edit", [w] {
		msg_write("edit: " + w->get_string("edit"));
	});
	w->event("spin", [w] {
		msg_write(format("spin: %f", w->get_float("spin")));
	});

	xhui::run();

	return 0;
}

