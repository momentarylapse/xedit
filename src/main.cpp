#include "EditorWindow.h"
#include "DocumentEditor.h"
#include "lib/os/msg.h"
#include "lib/xhui/xhui.h"


int xhui_main(const Array<string>& args) {
	try {
		xhui::init({""}, "xhui");
	} catch (Exception &e) {
		msg_error(e.message());
		return 1;
	}

	auto w = new EditorWindow();
	if (args.num >= 2) {
		for (int i=1; i<args.num; i++) {
			auto e = w->create_document_editor();
			e->load(args[i]);
		}
	} else {
		auto e = w->create_document_editor();
	}

	xhui::run();

	return 0;
}

