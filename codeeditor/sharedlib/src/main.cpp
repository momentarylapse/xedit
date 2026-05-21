#include <lib/base/base.h>
#include <lib/codeeditor/_kaba_export.h>
#include <lib/syntaxhighlight/Theme.h>
#include <lib/syntaxhighlight/BaseParser.h>
#include <lib/kaba/kaba.h>

bool init_stuff() {
	syntaxhighlight::init();
	syntaxhighlight::default_theme = syntaxhighlight::get_theme("dark2");
	InitParser();
	return true;
}

extern "C" {
__attribute__ ((visibility ("default")))
void export_symbols(kaba::IExporter* e) {
	kaba::make_context_public(e); // work-around until we can purely use kapi
	init_stuff();
	
	export_package_codeeditor(e);
}
}

// required for linking the shared library!
namespace os::app {
int main(const Array<string>&) {
	return 0;
}
}

