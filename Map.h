#pragma once
#include "MineSweeperCommons.h"
#include "MapView.h"
#include "Cell.h"
#include <vector>
#include <queue>

using std::queue;
using std::vector;

class Map
{
private:
	bool isOver = false;
	int row;
	int col;
	int mine;
	int revealedCount = 0;
	queue<POS> selectOrder;
	vector<vector<Cell*>> cells;
public:
	Map(vector<vector<Cell*>> cells, int row, int col, int mine);
	~Map() noexcept;
	void callShowMap(const MapView& mapView);
	void revealCell(POS pos, const MapView& mapView);
	void revealAllCell(const MapView& mapView);
	vector<Cell*> getAdjacentDiscoverableCells(Cell* cell);
	void setCell(POS pos, Cell* alter);
	int getCellToReveal(MapView& mapView);
	void addRevealedCount(int count);
	void setisOver(bool isOver);
	void rePlay(Map& copyMap, MapView& mapView);
	int getRevealedCount();
};