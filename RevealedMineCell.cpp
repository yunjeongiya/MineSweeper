#include "RevealedMineCell.h"

string RevealedMineCell::showCell()
{
	return " *";
}

void RevealedMineCell::callUpdateVeiw(const MapView& mapView)
{
	mapView.updateView(this);
}