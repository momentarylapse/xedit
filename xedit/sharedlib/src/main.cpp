#include "EditorWindow.h"
#include <lib/codeeditor/CodeEditor.h>
#include <lib/syntaxhighlight/Theme.h>
#include <lib/syntaxhighlight/BaseParser.h>
#include <lib/os/msg.h>
#include <lib/xhui/xhui.h>
#include <lib/kaba/kaba.h>
#include <lib/kabaexport/KabaExporter.h>
#include <lib/kaba/Context.h>

#include "lib/os/msg.h"

namespace kaba {
	class Context;
	extern Context *_secret_lib_context_;
}

bool app_init() {
	try {
		xhui::init({}, "xhui");
	} catch (Exception &e) {
		msg_error(e.message());
		return false;
	}

	syntaxhighlight::init();
	syntaxhighlight::default_theme = syntaxhighlight::get_theme("dark2");
	InitParser();
	return true;
}

void app_run(const Array<string>& args) {
	auto w = new EditorWindow();

	for (const auto& a: args)
		w->open_document(a);
	if (args.num == 0)
		w->create_document_editor();

	xhui::fly(w);

	xhui::run();
}

extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::Exporter* e) {
	// restore/duplicate global state
	kaba::default_context = e->ctx;
	kaba::_secret_lib_context_ = e->secret_lib_context;
	kaba::common_types = *e->x_common_types;

	e->package_info("xedit", "0.1");

	e->link_func("run", &app_run);

	if (!app_init())
		msg_error("failed to initialize...");
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}

