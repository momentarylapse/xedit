#include "EditorWindow.h"
#include <lib/codeeditor/CodeEditor.h>
#include <lib/syntaxhighlight/Theme.h>
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

	syntaxhighlight::init();
	syntaxhighlight::default_theme = syntaxhighlight::get_theme("dark2");
	InitParser();

	kaba::init();

	auto w = new EditorWindow();
	if (args.num >= 2) {
		for (int i=1; i<args.num; i++)
			w->open_document(args[1]);
	} else {
		w->create_document_editor();
	}
	xhui::fly(w);

	xhui::run();

	return 0;
}
}

