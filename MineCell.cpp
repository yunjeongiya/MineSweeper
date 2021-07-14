#include "MineCell.h"
#include "RevealedMineCell.h"
#include "Map.h"

string MineCell::showCell()
{
	return "■";
}

bool MineCell::isDiscoverable()
{
	return false;
}

void MineCell::callUpdateVeiw(const MapView& mapView)
{
	mapView.updateView(this);
}

void MineCell::reveal(Map* map, const MapView& mapView)
{
	map->revealAllCell(mapView);
	mapView.showGameOver();
	map->setisOver(true);
}

void MineCell::onDiscover(Map* map, const MapView& mapView)
{
    RevealedMineCell* newRevealedMineCell = new RevealedMineCell(this->pos.first, this->pos.second);
    map->setCell(this->pos, newRevealedMineCell);
    mapView.updateView(newRevealedMineCell);
	delete this;
}