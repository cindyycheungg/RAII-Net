#ifndef player_hpp
#define player_hpp




#include <iostream>
#include "ability.h"
#include <string>
#include <sstream>
#include "board.h"
#include <vector>
#include <map>
#include "piece.h"
#include <list>
#include <memory>

class Player {
    std::vector<Ability*> abilitySet;
    bool isplayer1 = 1;
    int numOfData;//downloaded
    int numOfVirus;//downloaded
    int numOfAbilities;//abilities left
    Player* otherPlayer = nullptr;
    std::map<std::string, Piece*> pieceSet;
    Board* theBoard;
public:
    Player(std::vector<Ability*> s, bool isplayer1, Player* otherPlayer, std::map<std::string, Piece*>, Board* theBoard);
    Player();
    Player& operator=(Player&& p);
    void movePiece(std::string direction, std::string PieceName);
    std::string isFull();
    bool useAbility(int ID, std::string PieceName, int x, int y);
    void showAbility();
    Piece* getPiece(int x, int y);
    void update(int data, int virus, int ability);
    Piece* getPieceWithName(std::string name);
    void PrintThisRound();
    void PrintOtherRound();
};


#endif /* player_hpp */
