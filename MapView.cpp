#include "MapView.h"
#include "MineCell.h"
#include "UnRevealedCell.h"
#include "RevealedCell.h"
#include "RevealedMineCell.h"
#include "Cell.h"
#include "Map.h"
#include <iostream>
#include <utility>
using std::cout;
using std::make_pair;
using std::endl;
using std::cout;

MapView::MapView(int row, int col, int level)
	:row(row), col(col), size(row* col), mine(size* (static_cast<float>(level) / 10)), cursorX(startX), cursorY(startY) {}

void MapView::updateView(RevealedCell* cell) const
{
	gotoxy(2 + (cell->getPosition().second) * 2, startY + cell->getPosition().first);
	cout << "\b\b" << *cell;
}

void MapView::updateView(UnRevealedCell* cell) const
{
	gotoxy(2 + (cell->getPosition().second) * 2, startY + cell->getPosition().first);
	cout << "\b\b" << *cell;
}

void MapView::updateView(MineCell* cell) const
{
	gotoxy(2 + (cell->getPosition().second) * 2, startY + cell->getPosition().first);
	cout << "\b\b" << *cell;
}

void MapView::updateView(RevealedMineCell* cell) const
{
	gotoxy(2 + (cell->getPosition().second) * 2, startY + cell->getPosition().first);
	cout << "\b\b" << *cell;
}

void MapView::showMap(vector<vector<Cell*>> cells) const
{
	cout << " 202010655 이윤정" << endl << endl;
	cout << " 이동 : 화살표\t선택 : ENTER\t일시정지 : ESC" << endl;
	cout << endl << " 맵 크기: " << col << "×" << row << '\t'
		<< " 지뢰 수: " << mine << endl;

	vector<vector<Cell*>>::iterator vec;
	vector<Cell*>::iterator it;
	for (vec = cells.begin(); vec != cells.end(); ++vec)
		for (it = (*vec).begin(); it != (*vec).end(); ++it)
			(**it).callUpdateVeiw(*this);
}

void MapView::showGameOver() const
{
	gotoxy(1, startY + row + 1);
	cout << "Game Over!" << endl << endl << endl;
	system("pause");
}

void MapView::showGameClear() const
{
	gotoxy(1, startY + row + 1);
	cout << "Game Clear!" << endl << endl << endl;
	system("pause");
}

void MapView::showReplayCount(int count) const
{
	gotoxy(1, startY + row + 2);
	if (!count)
		cout << "\t[REPLAY]";
	else
		cout << "\t[REPLAY :" << count << "번째 선택]";
}

POS MapView::moveCursorOnMap(vector<vector<Cell*>> cells)
{
	const int UP = 72;
	const int DOWN = 80;
	const int LEFT = 75;
	const int RIGHT = 77;
	const int ESC = 27;
	const int ENTER = 13;

	int keycode;
	gotoxy(cursorX, cursorY);
	cout << "□";
	while (true)
	{
		Cell* currentCell = cells[cursorY - startY][(cursorX - startX) / 2];
		while (true)
		{
			if (_kbhit())
			{
				keycode = _getch();
				if (keycode == 224)
				{
					keycode = _getch();
					switch (keycode)
					{
					case LEFT:
						if (cursorX > startX) cursorX -= 2;
						break;
					case RIGHT:
						if (cursorX < 2 * col + (startX - 2)) cursorX += 2;
						break;
					case UP:
						if (cursorY > startY) cursorY--;
						break;
					case DOWN:
						if (cursorY < row + (startY - 1)) cursorY++;
						break;
					}
				}
				else if (keycode == ENTER) break;
				else if (keycode == ESC)
					return make_pair(-1, -1);
				cout << "\b\b" << *currentCell;

				currentCell = cells[cursorY - startY][(cursorX - startX) / 2];
				gotoxy(cursorX, cursorY);
				cout << "□";
			}
		}
		return make_pair(cursorY - startY, (cursorX - startX) / 2);
	}
}