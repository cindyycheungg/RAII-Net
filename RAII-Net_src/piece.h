#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
class Piece{
	std::string name; 
	int x; 
	int y; 
	int level; 
	bool data; 
	int prev_x; 
	int prev_y; 
	bool isReveal; 
	bool isAlive; 
	//Board* isBoard; 
	bool boosted; 
	std::string type; 

public: 
	Piece(int order,string type, int level,  bool  player1); 
	Piece();
	Piece& operator=(Piece &&other); 
	void updateCoords(int xCoords, int yCoords); 
	void aliveSetter(); 
	bool aliveGetter(); 
	int getX(); 
	int getY(); 
	void revealSetter(); 
	bool revealGetter(); 
	bool isData(); 
	void convertType(); 
	void setBoosted(); 
	bool isBoosted(); 
	std::string getName(); 
  int getLevel();
  std::string printType();
};

#endif 
