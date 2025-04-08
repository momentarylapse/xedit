#include "lib/xhui/xhui.h"
#include "lib/xhui/controls/MultilineEdit.h"
#include "lib/os/msg.h"

int xhui_main(const Array<string>& args) {

	try {
		xhui::init({""}, "xhui");
	} catch (Exception &e) {
		msg_error(e.message());
		return 1;
	}

	auto w = new xhui::Window("test", 600,400);//1024, 768);
	w->from_source(R"foodelim(
Window test 'test' padding=0
	MultilineEdit edit ''
)foodelim");
	//	DrawingArea area ''

	xhui::run();

	return 0;
}

