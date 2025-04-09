#include <lib/os/file.h>

#include "lib/xhui/xhui.h"
#include "lib/xhui/controls/MultilineEdit.h"
#include "lib/os/msg.h"
#include "lib/os/filesystem.h"

int xhui_main(const Array<string>& args) {

	try {
		xhui::init({""}, "xhui");
	} catch (Exception &e) {
		msg_error(e.message());
		return 1;
	}

//	auto w = new xhui::Window("test", 800,600, xhui::Flags::OWN_DECORATION);
	auto w = new xhui::Window("test", 800,600);
	w->from_source(R"foodelim(
Window test 'test' padding=0
	MultilineEdit edit '' focusframe=no font=monospace fontsize=15
)foodelim");

	w->set_string("edit", os::fs::read_text("xmake.conf"));
	auto edit = (xhui::MultilineEdit*)w->get_control("edit");
	edit->add_markup({5, 20, xhui::FontFlags::Bold, Red});
	edit->add_markup({30, 40, xhui::FontFlags::Bold, Green});

	w->focus("edit");

	xhui::run();

	return 0;
}

