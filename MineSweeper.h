#pragma once
class MineSweeper
{
public:
	void start();
	void chooseGame();
	void playNewGame();
	void saveMenu();
	void showHelp();
	int chooseMenu(int longestMenu, int menuCount);
};