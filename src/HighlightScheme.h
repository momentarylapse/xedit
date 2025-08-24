/*
 * HighlightScheme.h
 *
 *  Created on: 06.06.2013
 *      Author: michi
 */

#pragma once

#include <lib/image/color.h>
#include <lib/syntaxhighlight/BaseParser.h>

class DocumentEditor;


struct HighlightContext {
	color fg, bg;
	bool set_bg;
	bool bold, italic;
	HighlightContext();
	HighlightContext(const color &_fg, const color &_bg, bool _set_bg, bool _bold, bool _italic);
};

class HighlightScheme {
public:
	string name;
	color bg;
	HighlightContext context[(int)MarkupType::NUM_TYPES];
	bool is_default, changed;
	HighlightScheme();
	HighlightScheme *copy(const string &name);

	static void init();
	static HighlightScheme *get(const string &name);
	static Array<HighlightScheme*> get_all();
	static HighlightScheme *default_scheme;
};


