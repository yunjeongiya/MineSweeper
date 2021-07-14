#include "MineSweeperCommons.h"
#include "MineSweeper.h"
#include "Map.h"
#include "MapBuilder.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

void MineSweeper::start()
{
	setCursorView(0);
	while (true)
	{
		system("cls");
		cout << " 202010655 이윤정" << endl;
		cout << "\n <MineSweeper>\n\n 1.PLAY\n 2.HELP\n 3.EXIT\n";
		switch (chooseMenu(8, 3))
		{
		case 1:
			chooseGame();
			break;
		case 2:
			system("cls");
			cout << " 202010655 이윤정" << endl;
			showHelp();
			system("pause");
			break;
		case 3:
			system("cls");
			cout << " 202010655 이윤정" << endl;
			cout << "프로그램을 종료합니다." << endl;
			return;
		}
	}
}

void MineSweeper::chooseGame(void)
{
	system("cls");
	cout << " 202010655 이윤정" << endl;
	cout << "\n <PLAY>\n\n 1.NewGame\n 2.Continue\n";
	switch (chooseMenu(12, 2))
	{
	case -1:
		break;
	case 1:
		playNewGame();
		break;
	case 2:
		system("cls");
		cout << " 202010655 이윤정" << endl;
		cout << "\n <Continue>\n\n";
		cout << chooseMenu(12, 2);
		break;
	}
}

void MineSweeper::playNewGame()
{
	system("cls");
	cout << " 202010655 이윤정" << endl;
	cout << "\n <NewGame>\n\n";
	gotoxy(0, 6);
	int col, row;
	setCursorView(1);
	cout << "\n* 지뢰찾기 맵의 가로, 세로 값을 입력해주세요.";
	gotoxy(0, 4);
	cout << " 가로: ";
	cin >> col;
	cout << " 세로: ";
	cin >> row;
	setCursorView(0);
	system("cls");
	cout << " 202010655 이윤정" << endl;
	cout << "\n <NewGame>\n\n 1.하 (지뢰 수 10%)\n 2.중 (지뢰 수 20%)\n 3.상 (지뢰 수 30%)\n";
	int level = chooseMenu(20, 3);
	if (level == -1) return;
	MapBuilder builder(row, col, level);
	Map map = builder.buildGameMap();
	MapView mapView(row, col, level);
	while (true)
	{
		system("cls");
		map.callShowMap(mapView);
		int flag = map.getCellToReveal(mapView);
		if (flag == -1)
		{
			system("cls");
			cout << " 202010655 이윤정" << endl;
			cout << "\n <PAUSED>\n\n 1.Save\n 2.Continue\n 3.Exit\n ";
			int continueFlag = chooseMenu(13, 3);
			if (continueFlag == 1)
				saveMenu();
			else if (continueFlag == 3)
				break;
		}
		else if (flag == 1)
		{
			Map copyMap = builder.buildGameMap();
			map.rePlay(copyMap, mapView);
			break;
		}
	}
}

void MineSweeper::saveMenu()
{
	system("cls");
	cout << " 202010655 이윤정" << endl;
	cout << "\n <SAVE>\n\n";
	gotoxy(0, 3);
	string saveName;
	setCursorView(1);
	cout << "\n* 저장 파일 이름 : ";
	cin >> saveName;
	/*if (makeSaveFile(saveName))
		cout << "성공적으로 저장되었습니다." << endl;
	else*/
	setCursorView(0);
		cout << "저장에 실패했습니다." << endl;
	system("pause");
}

void MineSweeper::showHelp()
{
	cout << "\n <HELP>\n\n 화살표 키로 커서를 이동한 후, 엔터를 입력하면 칸을 선택할 수 있습니다." << endl << endl
		<< " 지뢰를 선택하면 게임이 종료되고, 지뢰가 아니라면 해당 칸 주변의 지뢰 개수가 보여집니다." << endl << endl
		<< " 주변에 지뢰가 하나도 없다면, 주변에 지뢰가 있는 칸이 열릴때까지 8방향 자동펼침이 이뤄집니다." << endl << endl
		<< " 지뢰를 제외한 모든 칸을 열었다면, 승리입니다." << endl << endl
		<< " 게임이 끝난 뒤에는 선택한 내역이 다시 리플레이 됩니다." << endl << endl
		<< " 게임 도중 일시정지하거나, 게임내역을 저장 혹은 그만두고 싶다면 ESC 키를 입력해주세요." << endl << endl
		<< " 저장한 게임은 나중에 이어하실 수 있습니다." << endl << endl;
}

int MineSweeper::chooseMenu(int longestMenu, int menuCount)
{
	const int UP = 72;
	const int DOWN = 80;
	const int ESC = 27;
	const int ENTER = 13;

	int x = longestMenu, startY = 4, y = startY;
	cout << "\n* 화살표 키로 메뉴를 선택하고 엔터 키를 누르십시오. (뒤로 가려면 ESC를 누르십시오) ";
	gotoxy(x, y);
	printf("<");
	while (1)
	{
		int ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
			case UP:
				if (y > startY) y--;
				break;
			case DOWN:
				if (y < menuCount + startY - 1) y++;
				break;
			}
		}
		else if (ch == ENTER) break;
		else if (ch == ESC)
		{
			system("cls");
			return -1;
		}

		cout << "\b ";
		gotoxy(x, y);
		cout << "<";
	}
	system("cls");
	return y - (startY - 1);
}