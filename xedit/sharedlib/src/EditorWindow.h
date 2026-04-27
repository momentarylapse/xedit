#pragma once

#include <lib/xhui/Window.h>
#include <lib/pattern/Observable.h>

namespace codeedit {
	class CodeEditor;
}

class DocumentSwitcher;
class Path;

class EditorWindow : public obs::Node<xhui::Window> {
public:
	EditorWindow();

	void on_key_up(int key) override;

	codeedit::CodeEditor* create_document_editor();
	codeedit::CodeEditor* open_document(const Path& filename);

	shared_array<codeedit::CodeEditor> document_editors;
	codeedit::CodeEditor* active_editor = nullptr;
	void set_active(codeedit::CodeEditor* editor);
	void close_document(codeedit::CodeEditor* editor);

	void update_title();

	DocumentSwitcher* switcher = nullptr;

	struct Message {
		enum class Type {
			INFO,
			WARNING,
			ERROR
		};
		Type type;
		string message;
	};
	Array<Message> messages;
	void add_message(Message::Type type, const string& message);
	void info(const string& message);
	void error(const string& message);
};

