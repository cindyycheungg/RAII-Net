#ifndef CELL_H
#define CELL_H

#include <string>
using namespace std;

// cell class that is used to keep track of which locations are occupied on the board
class cell
{
	public:

	// sets a firewall on the cell
	void setFirewall(string player);

	

	// cell constructor
	cell(int x, int y, string symbol, bool occupied, bool player);
	
	// check firewall
	bool checkFW(string player);

	// checkPlayer
	bool checkPlayer();

	// checkOccupied
	bool checkOccupied();

	// update the player and the piece
	void update(string player, string piece);

	~cell();
	
	// geName
	string getName();

	// clears the cell information
	void clear();

	private:
	int x;
	int y;
	bool isOccupied;
	bool whichPlayer;
	string whichPiece;
	bool playerOneFirewall;
	bool playerTwoFirewall;
};

#endif
