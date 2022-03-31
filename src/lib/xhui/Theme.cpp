#include "Theme.h"
#include "Config.h"
#include "../file/msg.h"

namespace hui {

Theme Theme::_default;

void Theme::load_default() {
	Configuration c;
	c.load("default.theme");
	_default.font_size = c.get_float("font.size", 12);
	_default.font_name = c.get_str("font.name", "Sans");

	_default.spacing = c.get_float("spacing", 8);
	_default.window_margin = c.get_float("window.margin", 8);
	_default.label_margin = c.get_float("label.margin", 8);

	_default.background = color::parse(c.get_str("colors.background", "#000000"));
	_default.background_hover = color::parse(c.get_str("colors.background-hover", "#404040"));
	_default.background_active = color::parse(c.get_str("colors.background-active", "#707070"));
	_default.text = color::parse(c.get_str("colors.text", "#ffffff"));
	_default.text_label = color::parse(c.get_str("colors.text-label", "#ffffff"));
}


}
