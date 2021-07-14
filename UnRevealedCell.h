#pragma once
#include "SafeCell.h"
#include <string>
using std::string;
class UnRevealedCell :
    public SafeCell
{
public:
    UnRevealedCell(int i, int j, int adjacentMines) : SafeCell(i, j, adjacentMines) {};
    virtual bool isDiscoverable() override;
    virtual void onDiscover(Map* map, const MapView& mapView) override;
    virtual bool isAdjacentMinesZero() override;
    virtual string showCell() override;
    virtual void callUpdateVeiw(const MapView& mapView) override;
    virtual void reveal(Map* map, const MapView& mapView) override;
};