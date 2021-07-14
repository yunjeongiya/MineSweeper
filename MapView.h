#pragma once
#include "MineSweeperCommons.h"
class RevealedCell;
class UnRevealedCell;
class MineCell;
class RevealedMineCell;
class Cell;
class Map;

#include <vector>
using std::vector;

class MapView
{
private:
	int row, col;
	int size;
	int mine;
	int startX = 0;
	int startY = 6;
	int cursorX, cursorY;
public:
	MapView(int row, int col, int level);
	void updateView(RevealedCell* cell) const;
	void updateView(UnRevealedCell* cell) const;
	void updateView(MineCell* cell) const;
	void updateView(RevealedMineCell* cell) const;
	void showMap(vector<vector<Cell*>> cells) const;
	void DiscoverAll(Map* map);
	void showGameOver() const;
	void showGameClear() const;
	void showReplayCount(int count) const;
	POS moveCursorOnMap(vector<vector<Cell*>> cells);
};