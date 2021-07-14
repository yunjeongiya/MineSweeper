#include "Map.h"
#include "MineCell.h"
#include "UnRevealedCell.h"
#include "MineSweeperCommons.h"
#include <vector>
#include <queue>
#include <utility>
using std::make_pair;

Map::Map(vector<vector<Cell*>> cells, int row, int col, int mine)
	:cells(cells), row(row), col(col), mine(mine) {}

Map::~Map() noexcept
{
	vector<vector<Cell*>>::iterator vec;
	vector<Cell*>::iterator it;
	for (vec = cells.begin(); vec != cells.end(); ++vec)
		for (it = (*vec).begin(); it != (*vec).end(); ++it)
		{
			if (*it != nullptr)
			{
				delete* it;
				*it = nullptr;
			}
		}
}

void Map::callShowMap(const MapView& mapView)
{
	mapView.showMap(cells);
}

void Map::revealCell(POS pos, const MapView& mapView) //BFS
{
	selectOrder.push(pos);
	cells[pos.first][pos.second]->reveal(this, mapView);
}

void Map::revealAllCell(const MapView& mapView)
{
	vector<vector<Cell*>>::iterator vec;
	vector<Cell*>::iterator it;
	for (vec = cells.begin(); vec != cells.end(); ++vec)
		for (it = (*vec).begin(); it != (*vec).end(); ++it)
			(**it).onDiscover(this, mapView);
}

vector<Cell*> Map::getAdjacentDiscoverableCells(Cell* cell)
{
	vector<Cell*> adjacentCells;
	int direction[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (int direction_i = 0; direction_i < 8; direction_i++)
	{
		POS currentPosition = cell->getPosition();
		int x = currentPosition.first + direction[direction_i][0];
		int y = currentPosition.second + direction[direction_i][1];
		if (x >= 0 && x < row && y >= 0 && y < col)
			if (cells[x][y]->isDiscoverable()) adjacentCells.push_back(cells[x][y]);
	}
	return adjacentCells;
}

void Map::setCell(POS pos, Cell* alter)
{
	cells[pos.first][pos.second] = alter;
}

int Map::getCellToReveal(MapView& mapView)
{
	POS revealPOS = mapView.moveCursorOnMap(cells);
	if (revealPOS == make_pair(-1, -1))
		return -1;
	else
	{
		revealCell(revealPOS, mapView);
		if (revealedCount >= row * col - mine)
		{
			mapView.showGameClear();
			isOver = true;
		}
		if (isOver)
			return 1;
		return 0;
	}
}

void Map::addRevealedCount(int count)
{
	revealedCount += count;
}

void Map::setisOver(bool isOver)
{
	this->isOver = isOver;
}

void Map::rePlay(Map& copyMap, MapView& mapView)
{
	system("cls");
	copyMap.callShowMap(mapView);
	queue<POS> selectOrderCopy = selectOrder;
	int count = 0;
	while (!selectOrderCopy.empty())
	{
		mapView.showReplayCount(count);
		Sleep(1000);
		count++;
		POS revealPOS = selectOrder.front();
		selectOrderCopy.pop();
		selectOrder.pop();
		copyMap.revealCell(revealPOS, mapView);
		if (copyMap.getRevealedCount() >= row * col - mine)
		{
			mapView.showReplayCount(count);
			mapView.showGameClear();
		}
	}
}

int Map::getRevealedCount() {return revealedCount; }