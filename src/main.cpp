#include "EditorWindow.h"
#include "DocumentEditor.h"
#include "HighlightScheme.h"
#include <lib/syntaxhighlight/BaseParser.h>
#include <lib/os/msg.h>
#include <lib/xhui/xhui.h>
#include <lib/kaba/kaba.h>


namespace os::app {
int main(const Array<string>& args) {
	try {
		xhui::init(args, "xhui");
	} catch (Exception &e) {
		msg_error(e.message());
		return 1;
	}

	HighlightScheme::init();
	HighlightScheme::default_scheme = HighlightScheme::get("dark2");
	InitParser();

	kaba::init();

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
}

