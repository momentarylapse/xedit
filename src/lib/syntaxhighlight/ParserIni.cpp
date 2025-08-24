/*
 * ParserIni.cpp
 *
 *  Created on: 2 Oct 2023
 *      Author: michi
 */

#include "ParserIni.h"

ParserIni::ParserIni() : Parser("Ini") {
	macro_begin = "???";
	line_comment_begin = "#";
	multi_comment_begin = "/*";
	multi_comment_end = "*/";
}

#define next_char()	p=g_utf8_next_char(p);pos++
#define set_mark()	sv->mark_word(l, pos0, pos, in_type, p0, p);p0=p;pos0=pos
#define begin_token(t) (string(p, t.num) == t)
#define skip_token_almost(t) p+=(t.num-1);pos+=(t.num-1)
#define skip_token(t) p+=t.num;pos+=t.num


Array<Markup> ParserIni::create_markup_header(const string& line, int offset) {
	return {{offset, offset + line.num, MarkupType::MACRO}};
}

bool is_numeric(const string& s) {
	if (s.num == 0)
		return false;
	for (auto c: s)
		if ((c < '0' or c > '9') and c != '.')
			return false;
	return true;
}

Array<Markup> ParserIni::create_markup_key_value(const string& line, int index0) {
	int num_uchars = line.utf8len();
//	char *p = (char*)line.data;//(const char*)&line[0];
//	char *p0 = p;

	int i0 = line.find("=");
	if (i0 < 0)
		return {};

	Array<Markup> markups;
	markups.add({index0, index0 + i0, MarkupType::SPECIAL});
	string rest = line.sub_ref(i0 + 1, line.num);
	string value = rest.trim();
	i0 += 1;
	if (value.head(1) == "[" and value.tail(1) == "]") {
		auto xx = value.sub_ref(1, value.num - 1).explode(",");
		i0 += 1 + rest.find("[");
		for (auto &x: xx) {
			markups.add({index0 + i0, index0 + i0 + x.num, MarkupType::MODIFIER});
			i0 += x.num + 1;
		}

	} else {
		MarkupType type = MarkupType::MODIFIER;
		if (value == "true" or value == "false")
			type = MarkupType::GLOBAL_VARIABLE;
		else if (is_numeric(value))
			type = MarkupType::NUMBER;
		else if (value.head(1) == "\"" and value.tail(1) == "\"")
			type = MarkupType::STRING;
		markups.add({index0 + i0, index0 + i0 + rest.num, type});
	}
	return markups;
}

Array<Markup> ParserIni::create_markup(const string &text, int offset) {
	return {};
}

#if 0
void ParserIni::CreateTextColors(DocumentEditor *sv, int first_line, int last_line) {
	int num_lines = sv->get_num_lines();
	if (first_line < 0)
		first_line = 0;
	if (last_line < 0)
		last_line = num_lines - 1;

	sv->clear_markings(first_line, last_line);

	for (int l=first_line; l<=last_line; l++) {
		int index0 = sv->line_start(l);
		string s = sv->get_line(l);
		if (s.trim().head(1) == "[")
			CreateTextColorsHeader(sv, l, s);
		else if (s.trim().head(1) == "#")
			sv->mark_word(index0, index0 + s.num, IN_LINE_COMMENT);
		else
			CreateTextColorsKeyValue(sv, l, s);
	}
}
#endif

