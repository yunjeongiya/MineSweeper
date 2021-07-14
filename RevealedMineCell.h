#pragma once
#include "MineCell.h"
class RevealedMineCell:
	public MineCell
{
public:
    RevealedMineCell(int i, int j) : MineCell(i, j) {};
    virtual string showCell() override;
    virtual void callUpdateVeiw(const MapView& mapView) override;
};