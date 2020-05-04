#include "board.h"
#include "textdisplay.h"
#include "cell.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

void Board::init(){
	td = make_unique<TextDisplay>();
	vector<cell> border;
	for(int x = 0; x < 8; x++){
		border.emplace_back(cell(x, 0, "=", false, false));
	}
	board.emplace_back(border);
	vector<cell> row1;
	vector<cell> row2;
	char curr = 'a';
	for(int x = 0; x < 8; x++){
		if(x == 3 || x == 4){
		
			row1.emplace_back(cell(x, 1, "S", true, true));
			row2.emplace_back(cell(x, 2,string(1, curr), true, true));
		}
		else{
			row1.emplace_back(cell(x, 1, string(1, curr), true, true));
			row2.emplace_back(cell(x, 2, ".", false, false));
		}
		curr++;
	}
	board.emplace_back(row1);
	board.emplace_back(row2);
	for(int y = 3; y < 7; y++){
		vector<cell> row;
		for(int x = 0; x < 8; x++){
			row.emplace_back(cell(x, y, ".", false, false));
		}
		board.emplace_back(row);
	}
	row1.clear();
	row2.clear();
	border.clear();
	curr = 'A';
	for(int x = 0; x < 8; x++){
		if(x == 3 || x == 4 ){
			row1.emplace_back(cell(x, 7, string(1, curr), true, false));
			row2.emplace_back(cell(x, 8, "S", true, false));
		}
		else{
			row1.emplace_back(cell(x, 7, ".", false, false));
			row2.emplace_back(cell(x, 8, string(1, curr), true, false));
		}
		curr++;
	}
	board.emplace_back(row1);
	board.emplace_back(row2);
	for(int x = 0; x < 8; x++){
		border.emplace_back(cell(x, 9, "=", false, false));
	}
	board.emplace_back(border);
	vector<cell>().swap(row1);
	vector<cell>().swap(row2);
	vector<cell>().swap(border);
	
}

bool Board::checkOccupied(int x, int y){
	return board.at(y).at(x).checkOccupied();
}

bool Board::checkPlayer(int x, int y){
	return board.at(y).at(x).checkPlayer();
}


// input: player, x, y, symbol
// output: sets the board and x and y to the symbol which is on the player's side
void Board::move(string player, int x, int y, string symbol){
	if (player == "clear"){
		board.at(y).at(x).clear();
	}

	else{
		board.at(y).at(x).update(player, symbol);
	}
	td->notify(x,y,symbol);
}


// check firewall
// input: int x, int y, string player 
// description: displays whether or not the location has a firewall from the given player
bool Board::checkFW(int x, int y, string player){
	return board.at(y).at(x).checkFW(player);
}

void Board::setFireWall(int x, int y, string player){
	board.at(y).at(x).setFirewall(player);
	if(player == "player1"){
		td->notify(x,y, "m");
	}
	else{
		td->notify(x,y, "w");
	}
}



ostream &operator<<(ostream &out, const Board &b){
	out << *b.td;
	return out;
}

Board::~Board(){
     for(auto &row: board){
	vector<cell>().swap(row);
     }
     vector<vector<cell>>().swap(board);
     td.reset();
}



string Board::checkName(int x, int y){
	return board.at(y).at(x).getName();
}
