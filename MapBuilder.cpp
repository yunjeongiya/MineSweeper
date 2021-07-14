#include "MapBuilder.h"
#include "RevealedCell.h"
#include "UnRevealedCell.h"
#include "MineCell.h"

MapBuilder::MapBuilder(int row, int col, int level)
	:row(row), col(col), size(row* col), mine(size* (static_cast<float>(level) / 10))
{
	cells.resize(row, vector<Cell*>(col));
	makeMineIndexVec();
}

MapBuilder::MapBuilder(int row, int col, int level, vector<int> mineIndexVec) //저장했던 텍스트파일에서 mineIndexVec 넣기
	:row(row), col(col), size(row* col), mine(size* (static_cast<float>(level) / 10)), mineIndexVec(mineIndexVec)
{
	cells.resize(row, vector<Cell*>(col));
}

MapBuilder::~MapBuilder() noexcept
{
	//vector<vector<Cell*>>::iterator vec;
	//vector<Cell*>::iterator it;
	//for (vec = cells.begin(); vec != cells.end(); ++vec)
	//	for (it = (*vec).begin(); it != (*vec).end(); ++it)
	//	{
	//		if (*it != nullptr)
	//		{
	//			delete* it;
	//			*it = nullptr;
	//		}
	//	}
}

void MapBuilder::makeMineIndexVec()
{
	mineIndexVec.resize(size);
	for (size_t i = 0; i < size; i++)
		mineIndexVec[i] = i;

	for (size_t i = 0; i < size; i++)
	{
		int x = rand() % size, y = rand() % size, tmp;
		if (x != y)
		{
			tmp = mineIndexVec[x];
			mineIndexVec[x] = mineIndexVec[y];
			mineIndexVec[y] = tmp;
		}
	}
	mineIndexVec.resize(mine);
}

vector<vector<int>> MapBuilder::buildMineMap()
{
	vector<vector<int>> mineMap(row, vector<int>(col));
	for (auto it = mineIndexVec.begin(); it != mineIndexVec.end(); ++it)
	{
		size_t mineIndex = *it;
		mineMap[mineIndex / col][mineIndex % col] = 1;
	}
	return mineMap;
}

Cell* MapBuilder::checkCell(vector<vector<int>> mineMap, int i, int j)
{
	int direction[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	if (mineMap[i][j]) return new MineCell(i, j);
	int adjacentMines = 0;
	for (int direction_i = 0; direction_i < 8; direction_i++)
	{
		int x = i + direction[direction_i][0];
		int y = j + direction[direction_i][1];
		if (x >= 0 && x < row && y >= 0 && y < col)
			if (mineMap[x][y]) adjacentMines++;
	}
	return new UnRevealedCell(i, j, adjacentMines);
}

Map MapBuilder::buildGameMap()
{
	vector<vector<int>> mineMap = buildMineMap();

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			cells[i][j] = checkCell(mineMap, i, j);

	return Map(cells, row, col, mine);
}