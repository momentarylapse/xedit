#pragma once

#include <lib/xhui/Window.h>
#include <lib/pattern/Observable.h>

namespace codeedit {
	class CodeEditor;
}

class DocumentSwitcher;

class EditorWindow : public obs::Node<xhui::Window> {
public:
	EditorWindow();

	void on_key_up(int key) override;

	codeedit::CodeEditor* create_document_editor();

	shared_array<codeedit::CodeEditor> document_editors;
	codeedit::CodeEditor* active_editor = nullptr;
	void set_active(codeedit::CodeEditor* editor);

	void update_title();

	DocumentSwitcher* switcher = nullptr;
};

