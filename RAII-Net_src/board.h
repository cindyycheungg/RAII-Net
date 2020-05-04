#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "cell.h"
#include "textdisplay.h"
#include <memory>

using namespace std;

class Board
{
	public:
	void init();
	bool checkOccupied(int x, int y);
	bool checkPlayer(int x, int y);
	void notify();
	void move(string player, int x, int y, string symbol);
	bool checkFW(int x, int y, string player);
	void setFireWall(int x, int y, string player);
	~Board();
	string checkName(int x, int y);
	friend ostream &operator<<(ostream &out, const Board &b);
	private:
	vector<vector<cell>> board;
	unique_ptr<TextDisplay> td; 	

};

#endif
