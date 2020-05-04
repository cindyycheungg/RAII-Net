#include "piece.h"
#include <iostream>
#include <string>
using namespace std; 

Piece::Piece(){
	name = "No name";  
	x = 0; 
	y = 0;
	level = 0;  
	data = false;
	prev_x = 0;  
	prev_y = 0; 
	isReveal = false; 
	isAlive = true; 
	//isBoard = nullptr; 
	boosted = false; 
	type = "No type";
}

Piece& Piece::operator=(Piece &&other){
	//swap(this->isBoard, other.isBoard);
	swap(this->name, other.name); 
	this->x = other.x; 
	this->y = other.y; 
	this->level = other.level; 
	this->data = other.data;
	this->prev_x = other.prev_x; 
	this->prev_y = other.prev_y;
	this->isReveal = other.isReveal; 
	this->isAlive = other.isAlive;
	this->boosted = other.boosted; 
	swap(this->type, other.type);
	return *this; 
}

Piece::Piece(int order, string type, int level, bool player1){
	this->level = level; 
	this->type = type; 
	if(type == "Data") data = true;
	else data = false;
	bool isPlayer1 = player1;
	isReveal = false; 
	isAlive = true; 
//	isBoard = nullptr; 
	boosted = false;  
	if(isPlayer1){
		if(order == 1){
			x = 0; 
			y = 1; 
			name = "a";
			prev_x = x; 
			prev_y = y; 
		}
		else if(order == 2){
			x = 1; 
			y = 1;
			name = "b"; 
			prev_x = x; 
			prev_y = y; 
		}
		else if(order == 3){
			x = 2; 
			y = 1;
			name = "c"; 
			prev_x = x; 
			prev_y = y; 
		}
		else if(order == 4){
			x = 3; 
			y = 2; 
			name = "d"; 
			prev_x = x; 
			prev_y = y; 
		}
		else if(order == 5){
			x = 4; 
			y = 2; 
			name = "e";
			prev_x = x; 
			prev_y = y;  
		}
		else if(order == 6){
			x = 5; 
			y = 1; 
			name = "f";
			prev_x = x; 
			prev_y = y;  
		}
		else if(order == 7){
			x = 6; 
			y = 1; 
			name = "g";
			prev_x = x; 
			prev_y = y; 
		}
		else{
			x = 7; 
			y = 1; 
			name = "h"; 
			prev_x = x; 
			prev_y = y; 
		}
	}
	else{
		if(order == 1){
			x = 0; 
			y = 8;
			name = "A";
			prev_x = x; 
			prev_y = y; 
		}
		else if(order == 2){
			x = 1; 
			y = 8; 
			name = "B";
			prev_x = x; 
			prev_y = y;
		}
		else if(order == 3){
			x = 2; 
			y = 8; 
			name = "C";
			prev_x = x; 
			prev_y = y;
		}
		else if(order == 4){
			x = 3; 
			y = 7; 
			name = "D";
			prev_x = x; 
			prev_y = y;
		}
		else if (order == 5){
			x = 4; 
			y = 7; 
			name = "E";
			prev_x = x; 
			prev_y = y;
		}
		else if (order == 6){
			x = 5; 
			y = 8; 
			name = "F";
			prev_x = x; 
			prev_y = y;
		}
		else if (order == 7){
			x = 6; 
			y = 8; 
			name = "G";
			prev_x = x; 
			prev_y = y;
		}
		else{
			x = 7; 
			y = 8;
			name = "H";
			prev_x = x; 
			prev_y = y;
		}
	}
}

void Piece::updateCoords(int xCoords, int yCoords){
	x = xCoords; 
	y = yCoords; 
}

void Piece::aliveSetter(){
	isAlive = false; 
}

bool Piece::aliveGetter(){
	return isAlive; 
}

int Piece::getX(){
	return x; 
}

int Piece::getY(){
	return y; 
} 

void Piece::revealSetter(){
	isReveal = true; 
}

bool Piece::revealGetter(){
	return isReveal;
}
	
bool Piece::isData(){
	return data;  
}
	
void Piece::convertType(){
	data = !data; 
} 

void Piece::setBoosted(){
	boosted = true; 
} 
			
bool Piece::isBoosted(){
	return boosted; 
}

string Piece::getName(){
	return name; 
}

int Piece::getLevel(){
	return level; 
}

string Piece::printType(){
	string s;
	if(data){
    	s = "D";
  }
  	else{
    	s = "V";
    }
  return s; 
}
