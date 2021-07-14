#include "Cell.h"
#include "Map.h"
#include <utility>
using std::make_pair;

Cell::Cell(int i, int j) : pos(make_pair(i, j)) {}

POS Cell::getPosition()
{
	return pos;
}

bool Cell::isAdjacentMinesZero()
{
	return false;
}

void Cell::onDiscover(Map* map, const MapView& mapView) {}

void Cell::reveal(Map* map, const MapView& mapView) {}

ostream& operator<<(ostream& out, Cell& cell)
{
	out << cell.showCell();
	return out;
}