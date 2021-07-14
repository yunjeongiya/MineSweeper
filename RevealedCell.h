#pragma once
#include "SafeCell.h"
class RevealedCell :
    public SafeCell
{
public:
    RevealedCell(int i, int j, int adjacentMines) : SafeCell(i, j, adjacentMines) {};
    virtual bool isDiscoverable() override;
    virtual string showCell() override;
    virtual void callUpdateVeiw(const MapView& mapView) override;
};