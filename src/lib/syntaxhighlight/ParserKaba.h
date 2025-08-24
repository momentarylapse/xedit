/*
 * ParserKaba.h
 *
 *  Created on: 06.06.2013
 *      Author: michi
 */

#pragma once

#include "BaseParser.h"

class ParserKaba : public Parser {
public:
	ParserKaba();

	Array<Label> find_labels(const string &text, int offset) override;
	Array<Markup> create_markup(const string &text, int offset) override;

	//owned<kaba::Context> context;
};

