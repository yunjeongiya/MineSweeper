#pragma once
#include "Cell.h"
class MineCell :
    public Cell
{
public:
    MineCell(int i, int j) : Cell(i, j) {};
    virtual string showCell() override;
    virtual bool isDiscoverable() override;
    virtual void callUpdateVeiw(const MapView& mapView) override;
    virtual void reveal(Map* map, const MapView& mapView) override;
    virtual void onDiscover(Map* map, const MapView& mapView) override;
};