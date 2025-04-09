#pragma once

#include <lib/os/path.h>
#include <lib/pattern/Observable.h>

namespace xhui {
class MultilineEdit;
}

class DocumentEditor : public obs::Node<VirtualBase> {
public:
	explicit DocumentEditor(xhui::MultilineEdit* edit);

	void load(const Path& filename);
	string title() const;

	Path filename;
	xhui::MultilineEdit* edit;
};

