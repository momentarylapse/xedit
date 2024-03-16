#include "MultilineEdit.h"

namespace hui {

MultilineEdit::MultilineEdit(const string &_id, const string &t) : Edit(_id, t) {
	expand_y = true;
	multiline = true;
}

}
