#pragma once
#include "Cell.h"
class SafeCell :
    public Cell
{
protected:
    int adjacentMines;
public:
    SafeCell(int i, int j, int adjacentMines);
};