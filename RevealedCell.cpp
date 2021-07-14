#include "RevealedCell.h"
#include <sstream>
using std::stringstream;

bool RevealedCell::isDiscoverable()
{
    return false;
}

string RevealedCell::showCell()
{
    stringstream ss;
    ss << " " << adjacentMines;
    return ss.str();
}

void RevealedCell::callUpdateVeiw(const MapView& mapView)
{
    mapView.updateView(this);
}