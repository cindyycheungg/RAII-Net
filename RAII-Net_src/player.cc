#include "player.h"
#include "ability.h"
#include <utility>
/*class Player {
    std::vector<ability> ;
    bool isplayer1 = 1;
    int numOfData;
    int numOfVirus;
    int numOfAbilities;
    Player* otherPlayer = nullptr;
    map<std:string, Piece*>;
    Board* theBoard = nullptr;
public:
    void setUp();
    void movePiece(std::string direction, std::string PieceName);
    std::string isFull();
    void useAbility(int ID, std::string PieceName);
    void showAbility();
};*/
using namespace std;

Player:: Player() {
    //abilitySet = vector<Ability*>;
    isplayer1 = 0;
    numOfData = 0;
    numOfVirus = 0;
    numOfAbilities = 0;
    otherPlayer = nullptr;
    //pieceSet = map<string, Piece*>;
    theBoard = nullptr;
}

Player& Player:: operator=(Player&& p) {
    swap(this->abilitySet, p.abilitySet);
    swap(this->otherPlayer, p.otherPlayer);
    swap(this->theBoard, p.theBoard);
    swap(this->pieceSet, p.pieceSet);
    this->numOfAbilities = p.numOfAbilities;
    this->numOfVirus = p.numOfVirus;
    this->numOfData = p.numOfData;
    this->isplayer1 = p.isplayer1;
    return *this;
}

void Player:: update(int data, int virus, int ability) {
    numOfData += data;
    numOfVirus += virus;
    numOfAbilities += ability;
}



Piece* Player:: getPiece(int x1, int y) {
    for(auto const& x : pieceSet) {
        if(x.second->getX() == x1 && x.second->getY() == y) {
            return x.second;
        }
    }
    return nullptr; // not found
}


Piece* Player:: getPieceWithName(string name) {
     for(auto const& x : pieceSet) {
         if(x.first == name) {
             return x.second;
         }
     }
    return nullptr;
}


// Player::Player(std::vector<std::string abilityName> abilityNameSet, Player* otherPlayer, std::vector<std::string PieceName> PieceNameSet, Board* thBoard);
Player::Player(std::vector<Ability*> s, bool isplayer1, Player* otherPlayer, std::map<std::string, Piece*> m, Board* theBoard){
    abilitySet = s;
    this->isplayer1 = isplayer1;
    numOfAbilities = 5;
    numOfData = 0;
    numOfVirus = 0;
    this->otherPlayer = otherPlayer;
    this->theBoard = theBoard;
    pieceSet = m;
}



//   in the main function loop, each time that need to make a move, check if the game can be ended with using isFull(), check
// each player
string Player:: isFull() {
    if(numOfVirus == 4) {
        return "lose";
    }else if( numOfData == 4) {
        return "win";
    }
    return "notEnd";
}




// up down left right for direction
// all cout is changed from throw, cause it is a void function, we donot want to use throw to makeit
// complex
void Player:: movePiece(std::string direction, std::string PieceName) {
    if(direction != "up" && direction != "right" && direction != "left" && direction != "down") {
        cout << "wrong direction" << endl;
        throw("error");
        return;
    }
    //firstly, try to find the piece
    Piece* temp = nullptr;
    int x = -1;
    int y = -1;// x, y to record the coordinates of the piece
    int s = -1;
    int t = -1;
    temp = getPieceWithName(PieceName);
    if(temp == nullptr) {
        cout << "wrong piece name" << endl;
         throw("error");
        return;
    }
    else {
        if(temp->aliveGetter() == 0) {
            cout << "the link is already be downloaded" << endl;
             throw("error");
            return;
        }
        x = temp->getX();
        y = temp->getY();
    }
   
    //if it is player 1, then direction with right order, if it's player 2, direction with opposite order
    if(isplayer1) {

 //	cout << "is player 1" << endl;


        int toadd = 1;
        if(temp->isBoosted()) toadd = 2;
        if(direction == "up"){
            s = y + toadd;
            t = x;
        }
        if(direction == "left") {
            s = y;
            t = x + toadd;
        }
        if(direction == "right") {
            s = y;
            t = x - toadd;
        }
        if(direction == "down") {
            s = y - toadd;
            t = x;
        }
        if((t == 3 && s == 1) || (t == 4 && s == 1)) { // ove to the own server pots? come on
            cout << "you can not move a link on top of your own server ports." << endl;
             throw("error");
             return;
        }
        if(t > 7 || s >= 9 || t < 0 || s <= 0) {  // try to move out of the range
            cout << "want to move out of the edge" << endl;
             throw("error");
            return;
        }
        if( (t == 3 && s == 8 ) || (t == 4 && s == 8) ) {  // entered the server pots of player2
            if(temp->isBoosted()) {
                cout << "boosted data cannot get into the server pot" << endl;
                 throw("error");
                return;
            }
	     if(theBoard->checkFW(x, y, "player1")){
                     theBoard->setFireWall(x, y, "player1");
             } else if(theBoard->checkFW(x, y, "player2")){
                     theBoard->setFireWall(x, y, "player2");



             } else {
          theBoard->move("clear", x, y, ".");}
          temp->aliveSetter();  // will be downloaded, of course not alive
          temp->revealSetter();
          if(temp->isData()) {
          otherPlayer->update(1, 0, 0); // update the download information, player2 download the data
        } else {
           otherPlayer->update(0, 1, 0); // player2 download the virus
        }
            return;
    }

  // cout << "s: " << s << "t: " << t << endl;

        // then check the board
        if(theBoard->checkOccupied(t, s)) { // the case we may need to battle


//	cout << "occupied " << endl;

//	cout << "s: " << s << "t: " << t << endl;
            if(theBoard->checkPlayer(t, s)) {// checkPlayer(x, y) i hope it will return true if it is player1

//	cout << "own cell" << endl;

                cout << "try to step on your own link" << endl;
                 throw("error");
                return;
            } else {    // battle !!!!!!!
                Piece* tempPiece = nullptr;
                tempPiece = otherPlayer->getPiece(t, s);
//                so here we get the piece that we will need to battle
                 int play1Str = temp->getLevel();
                 int play2Str = tempPiece->getLevel();
                if(play1Str >= play2Str) {// player1 battle win
                    temp->updateCoords(t, s);// update player1's x, y
                    tempPiece->aliveSetter();// make player2's piece to be not alive
                    temp->revealSetter();    // afterbattle, it will be revealed
                    tempPiece->revealSetter();
                   // the board update
                    theBoard->move("player1", t, s, PieceName);
		     if(theBoard->checkFW(x, y, "player1")){
                     theBoard->setFireWall(x, y, "player1");
             } else if(theBoard->checkFW(x, y, "player2")){
                     theBoard->setFireWall(x, y, "player2");



             } else {
                    theBoard->move("clear", x, y, ".");}
                    if(tempPiece->isData()) {
                        update(1, 0, 0);
                    } else {
                        update(0, 1, 0);
                    }
                    return;
                } else { // player1 battle lose
                    temp->aliveSetter(); // set player1's piece to be not alive
                    tempPiece->revealSetter();
                    temp->revealSetter();
		     if(theBoard->checkFW(x, y, "player1")){
                     theBoard->setFireWall(x, y, "player1");
             } else if(theBoard->checkFW(x, y, "player2")){
                     theBoard->setFireWall(x, y, "player2");



             } else {
                    theBoard->move("clear", x, y, ".");}// the board update
                    if(temp->isData()) {
                        otherPlayer->update(1, 0, 0);
                    } else {
                        otherPlayer->update(0, 1, 0);
                    }
                    return;
                }
            }
        } else {
            temp->updateCoords(t, s);// without battle , and the valid move, just move
            theBoard->move("player1", t, s, PieceName);
	    if(theBoard->checkFW(x, y, "player2")){
		    theBoard->setFireWall(x, y, "player2");
	    } else    if(theBoard->checkFW(x, y, "player1")){
		    theBoard->setFireWall(x, y, "player1");
	    }

		    else {
            theBoard->move("clear", x, y, ".");}
            if(theBoard->checkFW(t, s, "player2")){
                if(!temp->isData()) {
                    temp->aliveSetter();   // virus meet the firewall, downloaded by the player1 automatically
                    theBoard->move("clear", t, s, ".");
                   theBoard->setFireWall(t, s, "player2");
                    update(0, 1, 0);
                }
                temp->revealSetter();
            }
            return;
        }
        
    } else { //here means it is player2's order, same logic as above
        int toadd = 1;
        if(temp->isBoosted()) toadd = 2;
        if(direction == "up"){
                   s = y - toadd;
                   t = x;
               }
               if(direction == "left") {
                   s = y;
                   t = x - toadd;
               }
               if(direction == "right") {
                   s = y;
                   t = x + toadd;
               }
               if(direction == "down") {
                   s = y + toadd;
                   t = x;
               }
            if((t == 3 && s == 8) || (t == 4 && s == 8)) {
                cout << "you can not move a link on top of your own server ports."  << endl;
                 throw("error");
                return;
            }
        if(t > 7 || s >= 9 || t < 0 || s <= 0) {
            cout << "want to move out of the edge" << endl;
             throw("error");
            return;
        }
        if( (t == 3 && s == 1 ) || (t == 4 && s == 1) ) { // enter the server pot of player1;
            if(temp->isBoosted()) {
                cout << "boosted data cannot get into the server pot" << endl;
                 throw("error");
                return;
            }
	     if(theBoard->checkFW(x, y, "player1")){
                     theBoard->setFireWall(x, y, "player1");
             } else if(theBoard->checkFW(x, y, "player2")){
                     theBoard->setFireWall(x, y, "player2");



             } else {
            theBoard->move("clear", x, y, ".");}
            temp->aliveSetter();  // will be downloaded, of course not alive
            temp->revealSetter();
        if(temp->isData()) {
            otherPlayer->update(1, 0, 0); // update the download information, player2 download the data
                } else {
                otherPlayer->update(0, 1, 0); // player2 download the virus
                }
            return;
        }
        if(theBoard->checkOccupied(t, s)) {
            if(!theBoard->checkPlayer(t, s)) { //same , i hope it will return false if it's player 2
                cout << "try to step on your own link" << endl;
                 throw("error");
                return;
            } else {
                Piece* tempPiece = nullptr;
                tempPiece = otherPlayer->getPiece(t, s);
//                so here again we get the pieces that need to battle
                int play2Str = temp->getLevel();
                int play1Str = tempPiece->getLevel();
            if(play2Str >= play1Str) { // play2 wins the battle
                //temp->move(direction);// move player2's piece
                temp->updateCoords(t, s);
        tempPiece->aliveSetter();// make player1's piece to be not alive
                temp->revealSetter();
                tempPiece->revealSetter();
                theBoard->move("player2", t, s, PieceName);// the board update
		 if(theBoard->checkFW(x, y, "player1")){
                     theBoard->setFireWall(x, y, "player1");
             } else if(theBoard->checkFW(x, y, "player2")){
                     theBoard->setFireWall(x, y, "player2");



             } else {
                theBoard->move("clear", x, y, ".");
	     }
                if(tempPiece->isData()) {
                    update(1, 0, 0); // update the download information
                } else {
                update(0, 1, 0);
            }
                return;
            } else { // player2 battle lose
                temp->aliveSetter(); // set player2's piece to be not alive
                tempPiece->revealSetter();
                temp->revealSetter();
		 if(theBoard->checkFW(x, y, "player1")){
                     theBoard->setFireWall(x, y, "player1");
             } else if(theBoard->checkFW(x, y, "player2")){
                     theBoard->setFireWall(x, y, "player2");



             } else {
                theBoard->move("clear", x, y, ".");}// the board update
                if(temp->isData()) {
                    otherPlayer->update(1, 0, 0); // update the download information
                } else {
                    otherPlayer->update(0, 1, 0);
                }
                return;
            }
        }
            }
        else {
           // temp->move(direction);// without battle , and the valid move, just move
            temp->updateCoords(t, s);
            theBoard->move("player2", t, s, PieceName);
	     if(theBoard->checkFW(x, y, "player1")){
		     theBoard->setFireWall(x, y, "player1");
	     } else if(theBoard->checkFW(x, y, "player2")){
		     theBoard->setFireWall(x, y, "player2");
	     
	     
	     
	     } else {
            theBoard->move("clear", x, y, ".");}
            if(theBoard->checkFW(t, s, "player1")){
                if(!temp->isData()) {
                    temp->aliveSetter();
                    theBoard->move("clear", t, s, ".");
		    theBoard->setFireWall(t, s, "player1");
                    update(0, 1, 0);
                }
                temp->revealSetter();
            }
                return;
            }
    }
}



bool Player:: useAbility(int ID, std::string PieceName, int x, int y) {
    // here is to use the ability, so first check the ability ID, and then
    // id it's link , we only use the piece name,
    // if it is FW, we will need the coordiates
    if(numOfAbilities <= 0) {
        cout << "no anility letf" << endl;
       // throw("error");
        return 0;
    }
    Ability* temp = nullptr;
    if(ID <= 0 || ID > 5) { // ID should be {1, 2, 3, 4, 5}
        cout << "wrong ability ID" << endl;
        // throw("error");
        return 0;
    }
    temp = abilitySet[ID - 1];
    if(!(temp->canUse())) {
        cout << "ability already used" << endl;
        // throw("error");
        return 0;
    }
    if(temp->getName() == "Link Boost") {
        Piece* tempPiece = nullptr;
       tempPiece = getPieceWithName(PieceName);
        if(tempPiece == nullptr) {
            cout << "wrong piece name" << endl;
        //     throw("error");
            return 0;
        }
        if(tempPiece->aliveGetter() == 0) {
            cout << "not alive piece" << endl;
          //  throw("error");
            return 0;
        }
        tempPiece->setBoosted();
        numOfAbilities--;
	temp->useSetter();
        return 1;
    
    }
    if(temp->getName() == "FireWall") {
//	    cout << "x: " << x << "y: " << y << endl;
	 if(x >= 0 && x <= 7 && y > 0 && y < 9) {
            if(!theBoard->checkOccupied(x, y)) {
                if(isplayer1){
                   theBoard->setFireWall(x, y, "player1");//not completed
                } else {
                    theBoard->setFireWall(x, y, "player2");
                }
            } else {
		    cout << "already a link here" << endl;
		    return 0;
	    }
        } else {
            cout << "invalid coordiates" << endl;
          //   throw("error");
            return 0;
        }
	temp->useSetter();
        numOfAbilities--;
        return 1;
    }
    if(temp->getName() == "scan") {
        Piece* tempPiece = nullptr;
        tempPiece = otherPlayer->getPieceWithName(PieceName);
        if(tempPiece == nullptr) {
            cout << "wrong piece name" << endl;
            // throw("error");
            return 0;
        }
        if(tempPiece->aliveGetter() == 0) {
            cout << "not alive piece" << endl;
           // throw("error");
            return 0;
        }
        numOfAbilities--;
	temp->useSetter();
        tempPiece->revealSetter();
        return 1;
    }
    if(temp->getName() == "download") {
        Piece* tempPiece = nullptr;
        tempPiece = otherPlayer->getPieceWithName(PieceName);
        if(tempPiece == nullptr) {
            cout << "wrong piece name" << endl;
            // throw("error");
            return 0;
        }
        if(tempPiece->aliveGetter() == 0) {
            cout << "not alive piece" << endl;
           // throw("error");
            return 0;
        }
        tempPiece->aliveSetter();
        if(tempPiece->isData()) {
            update(1, 0, 0);
        } else {
            update(0, 1, 0);
        }
        numOfAbilities--;
	temp->useSetter();
	theBoard->move("clear", tempPiece->getX(), tempPiece->getY(), ".");
        return 1;
    }
    if(temp->getName() == "Polarize") {
        Piece* tempPiece = nullptr;
              tempPiece = getPieceWithName(PieceName);
               if(tempPiece == nullptr) {
                   cout << "wrong piece name" << endl;
                   // throw("error");
                   return 0;
               }
        if(tempPiece->aliveGetter() == 0) {
            cout << "not alive piece" << endl;
           // throw("error");
            return 0;
        }
        tempPiece->convertType();
        numOfAbilities--;
	temp->useSetter();
        return 1;
        
    }
    return 0;
}




// cout the abilities with the ID the name of the ability

void Player:: showAbility() {
    int i = 1;
    for(auto const& v : abilitySet) {
        cout << i << ":" << " " << v->getName() << " ";
        i++;
    }
}

//print the player information;

// so in the main, if it is player1's round, after move,
// player1->PrintMyRound()       ||   player1->PrintOtherRound()
//                                 //
//  the board print              ||   the board print
//                                 //
// player2->PrintOtherRound()    ||   player2->PrintMyRound()
void Player::PrintThisRound() {
    if(isplayer1) {
        cout << "Player 1:" << endl;
    } else {
        cout << "Player 2:" << endl;
    }
    cout << "Downloaded: " << numOfData << "D" <<  ", " << numOfVirus << "V" << endl;
    cout << "Abilities: " << numOfAbilities << endl;
        int acc = 0;
        for(auto const& x : pieceSet) {
            if( acc == 4 ) {
                cout << endl;
            }
            cout << x.first << ": " << x.second->printType() << x.second->getLevel() << " ";
            acc++;
        }
    cout << endl;
}


void Player::PrintOtherRound() {
    if(isplayer1) {
        cout << "Player 1:" << endl;
    } else {
        cout << "Player 2:" << endl;
    }
    cout << "Downloaded: " << numOfData << "D" <<  ", " << numOfVirus << "V" << endl;
    cout << "Abilities: " << numOfAbilities << endl;
     int acc = 0;
            for(auto const& x : pieceSet) {
                if( acc == 4 ) {
                    cout << endl;
                }
                cout << x.first << ": " ;
                if(x.second->revealGetter()) {
                   cout << x.second->printType() << x.second->getLevel() << " ";
                } else {
                    cout << "? " ;
                }
                acc++;
            }
        cout << endl;
}

