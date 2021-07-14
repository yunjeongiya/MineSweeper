#include "SafeCell.h"
#include <sstream>

SafeCell::SafeCell(int i, int j, int adjacentMines)
	: Cell(i, j), adjacentMines(adjacentMines) {}