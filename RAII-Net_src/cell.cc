#include "cell.h"
#include <string>

using namespace std;

// input: integer (indicating which player is setting the firewall)
// output: void
// description: Sets the firewall on the current cell for the given player
void cell::setFirewall(string player){
	if(player == "player1"){
		playerOneFirewall = true;
	}
	else{
		playerTwoFirewall = true;
	}
}


// player 1 is true and player 2 is false

// cell constructor
cell::cell(int x, int y, string Piece, bool occupied, bool player):x{x}, y{y}, isOccupied{occupied}, whichPlayer{player}, whichPiece{Piece}, playerOneFirewall{false}, playerTwoFirewall{false}{}


// deconstructor
cell::~cell(){}

//get NAme
string cell::getName(){
	return whichPiece;
}

// checkOccupied
// input: void
// output: boolean
// description: returns true if the current cell is occupied false otherwise
bool cell::checkOccupied(){
	return isOccupied;
}

// checkPlayer
// input : void
// output: boolean
// description: return true/false depending on which player is currently occupying the cell
bool cell::checkPlayer(){
	return whichPlayer;
}	


//update
// input: string player, string piece
// output: void
// description: sets the current cell to have that player and that piece
void cell::update(string player, string piece){
	whichPiece = piece;
	isOccupied = true;
	if(player == "player1"){
		whichPlayer = true;
	}
	else{
		whichPlayer = false;
	}

	
}	


void cell::clear(){
	isOccupied = false;
	whichPiece = ".";
}

bool cell::checkFW(string player){
	if(player == "player1"){
		return playerOneFirewall;
	}
	else{
		return playerTwoFirewall;
	}
	
}
