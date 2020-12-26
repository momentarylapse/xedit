#include "Grid.h"
#include "../Painter.h"
#include "../../file/msg.h"

namespace hui {

Grid::Grid(Window *w, const string &_id) : Control(w, _id) {
	ignore_hover = true;
	spacing = 10;
}

void Grid::add(Control *c, int x, int y) {
	children.add({c, x, y});
	nx = max(nx, x+1);
	ny = max(ny, y+1);
}

void Grid::_draw(Painter *p) {
	for (auto &c: children)
		c.control->_draw(p);
}

void Grid::get_grid_min_sizes(Array<int> &w, Array<int> &h) {
	for (auto &c: children) {
		int ww, hh;
		c.control->get_effective_min_size(ww, hh);

		if (c.x >= w.num)
			w.resize(c.x + 1);
		if (c.y >= h.num)
			h.resize(c.y + 1);
		w[c.x] = max(w[c.x], ww);
		h[c.y] = max(h[c.y], hh);
	}
}

void Grid::get_content_min_size(int &_w, int &_h) {
	Array<int> w, h;
	get_grid_min_sizes(w, h);
	_w = spacing * (w.num - 1);
	for (int i=0; i<w.num; i++)
		_w += w[i];
	_h = spacing * (h.num - 1);
	for (int i=0; i<h.num; i++)
		_h += h[i];
}

void Grid::negotiate_area(const rect &available) {
	_area = available;

	Array<int> w, h;
	get_grid_min_sizes(w, h);
	
	int spacing = 10;

	for (auto &c: children) {
		int x0 = _area.x1;
		int y0 = _area.y1;
		for (int i=0; i<c.x; i++)
			x0 += w[i] + spacing;
		for (int i=0; i<c.y; i++)
			y0 += h[i] + spacing;
		c.control->negotiate_area(rect(x0, x0 + w[c.x], y0, y0 + h[c.y]));
	}
}

}
