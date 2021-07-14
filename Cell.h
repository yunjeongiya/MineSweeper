#pragma once
class Map;
#include "MapView.h"
#include <iostream>
#include <string>
using std::string;
using std::ostream;

class Cell
{
protected:
	POS pos;
public:
	Cell(int i, int j);
	friend ostream& operator<< (ostream& out, Cell& cell);
	POS getPosition();
	virtual string showCell() = 0;
	virtual bool isDiscoverable() = 0;
	virtual bool isAdjacentMinesZero();
	virtual void onDiscover(Map* map, const MapView& mapView);
	virtual void reveal(Map* map, const MapView& mapView);
	virtual void callUpdateVeiw(const MapView& mapView) = 0;
};