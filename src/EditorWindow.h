#pragma once

#include <lib/xhui/Window.h>
#include <lib/pattern/Observable.h>

class DocumentEditor;

class EditorWindow : public obs::Node<xhui::Window> {
public:
	EditorWindow();

	DocumentEditor* create_document_editor();

	owned_array<DocumentEditor> document_editors;
	DocumentEditor* active_editor = nullptr;
	void set_active(DocumentEditor* editor);

	void update_title();
};

