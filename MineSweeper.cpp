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
		cout << " 202010655 ������" << endl;
		cout << "\n <MineSweeper>\n\n 1.PLAY\n 2.HELP\n 3.EXIT\n";
		switch (chooseMenu(8, 3))
		{
		case 1:
			chooseGame();
			break;
		case 2:
			system("cls");
			cout << " 202010655 ������" << endl;
			showHelp();
			system("pause");
			break;
		case 3:
			system("cls");
			cout << " 202010655 ������" << endl;
			cout << "���α׷��� �����մϴ�." << endl;
			return;
		}
	}
}

void MineSweeper::chooseGame(void)
{
	system("cls");
	cout << " 202010655 ������" << endl;
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
		cout << " 202010655 ������" << endl;
		cout << "\n <Continue>\n\n";
		cout << chooseMenu(12, 2);
		break;
	}
}

void MineSweeper::playNewGame()
{
	system("cls");
	cout << " 202010655 ������" << endl;
	cout << "\n <NewGame>\n\n";
	gotoxy(0, 6);
	int col, row;
	setCursorView(1);
	cout << "\n* ����ã�� ���� ����, ���� ���� �Է����ּ���.";
	gotoxy(0, 4);
	cout << " ����: ";
	cin >> col;
	cout << " ����: ";
	cin >> row;
	setCursorView(0);
	system("cls");
	cout << " 202010655 ������" << endl;
	cout << "\n <NewGame>\n\n 1.�� (���� �� 10%)\n 2.�� (���� �� 20%)\n 3.�� (���� �� 30%)\n";
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
			cout << " 202010655 ������" << endl;
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
	cout << " 202010655 ������" << endl;
	cout << "\n <SAVE>\n\n";
	gotoxy(0, 3);
	string saveName;
	setCursorView(1);
	cout << "\n* ���� ���� �̸� : ";
	cin >> saveName;
	/*if (makeSaveFile(saveName))
		cout << "���������� ����Ǿ����ϴ�." << endl;
	else*/
	setCursorView(0);
		cout << "���忡 �����߽��ϴ�." << endl;
	system("pause");
}

void MineSweeper::showHelp()
{
	cout << "\n <HELP>\n\n ȭ��ǥ Ű�� Ŀ���� �̵��� ��, ���͸� �Է��ϸ� ĭ�� ������ �� �ֽ��ϴ�." << endl << endl
		<< " ���ڸ� �����ϸ� ������ ����ǰ�, ���ڰ� �ƴ϶�� �ش� ĭ �ֺ��� ���� ������ �������ϴ�." << endl << endl
		<< " �ֺ��� ���ڰ� �ϳ��� ���ٸ�, �ֺ��� ���ڰ� �ִ� ĭ�� ���������� 8���� �ڵ���ħ�� �̷����ϴ�." << endl << endl
		<< " ���ڸ� ������ ��� ĭ�� �����ٸ�, �¸��Դϴ�." << endl << endl
		<< " ������ ���� �ڿ��� ������ ������ �ٽ� ���÷��� �˴ϴ�." << endl << endl
		<< " ���� ���� �Ͻ������ϰų�, ���ӳ����� ���� Ȥ�� �׸��ΰ� �ʹٸ� ESC Ű�� �Է����ּ���." << endl << endl
		<< " ������ ������ ���߿� �̾��Ͻ� �� �ֽ��ϴ�." << endl << endl;
}

int MineSweeper::chooseMenu(int longestMenu, int menuCount)
{
	const int UP = 72;
	const int DOWN = 80;
	const int ESC = 27;
	const int ENTER = 13;

	int x = longestMenu, startY = 4, y = startY;
	cout << "\n* ȭ��ǥ Ű�� �޴��� �����ϰ� ���� Ű�� �����ʽÿ�. (�ڷ� ������ ESC�� �����ʽÿ�) ";
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