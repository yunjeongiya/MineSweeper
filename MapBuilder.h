#pragma once
#include "Map.h"
#include "Cell.h"
#include <vector>
using std::vector;
class MapBuilder
{
private:
	int row;
	int col;
	int size;
	int mine;
	vector<vector<Cell*>> cells;
	vector<int> mineIndexVec;
public:
	MapBuilder(int row, int col, int level);
	MapBuilder(int row, int col, int level, vector<int> mineIndexVec);
	~MapBuilder() noexcept;
	void makeMineIndexVec();
	vector<vector<int>> buildMineMap();
	Cell* checkCell(vector<vector<int>> mineMap, int i, int j);
	Map buildGameMap();
};