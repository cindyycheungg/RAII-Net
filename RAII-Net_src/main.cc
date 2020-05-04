#include "player.h"
#include "board.h"
#include "cell.h"
#include "textdisplay.h"
#include "ability.h"
#include "piece.h"
#include <sstream>
#include <fstream>
#include"Graphicdisplay.h" 
#include <iostream>
#include "window.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdlib>
#include <string>
#include <unistd.h>
using namespace std;

void initAbility(char s, Ability* t) {
    if(s == 'L') {
      *t = Ability("Link Boost");
    }
    if(s == 'F') {
      *t = Ability("FireWall");
    }
    if(s == 'D') {
      *t = Ability("download");
    }
    if(s == 'S') {
      *t = Ability("scan");
    }
    if(s == 'P') {
      *t = Ability("Polarize");
    }
}





void initPiece(Piece* c, char a, char b, bool player1, int& order, int order2) {
    if(a == 'V') {
      *c = Piece(order2, "Virus",int(b - 48), player1);
    }
    if(a == 'D') {
      *c = Piece(order2, "Data", int(b - 48) , player1);
    }
    order++;
}




int main(int argc, char* argv[]) {
 //cout << "newMain" << endl;
  Board b;
  GraphicsDisplay G;
  bool A1 = 0;
  bool A2 = 0;
  bool P1 = 0;
    bool P2 = 0;
    bool needGraphic = 0;
    int AccLp1 = 0;
    //LFDSP
    int AccFp1 = 0;
    int AccDp1 = 0;
    int AccSp1 = 0;
    int AccPp1 = 0;
   int AccLp2 = 0;
   int AccFp2 = 0;
   int AccDp2 = 0;
   int AccSp2 = 0;
   int AccPp2 = 0;
   Player p1;
   Player p2;
   Piece p1L1;
   Piece p1L2;
   Piece p1L3;
   Piece p1L4 ;
   Piece p1L5 ;
   Piece p1L6 ;
    Piece p1L7 ;
    Piece p1L8 ;
    Piece p2L1 ;
    Piece p2L2 ;
    Piece p2L3 ;
    Piece p2L4 ;
    Piece p2L5 ;
    Piece p2L6 ;
    Piece p2L7 ;
    Piece p2L8 ;
    Ability p1A1;
    Ability p1A2;
    Ability p1A3;
    Ability p1A4;
    Ability p1A5;
    Ability p2A1;
    Ability p2A2;
    Ability p2A3;
    Ability p2A4;
    Ability p2A5;
    vector<Ability*> AbilitySetPlayer1;
    vector<Ability*> AbilitySetPlayer2;
    map<string, Piece*> PieceSetPlayer1;
    map<string, Piece*> PieceSetPlayer2;
    for(int i = 1; i < argc; i++) {
	 if((string)argv[i] == "-graphics") {
	   needGraphic = 1;
	   G = GraphicsDisplay("true");
	 }
	 if((string)argv[i] == "-ability1") {
	   string order = (string) argv[i+1];
	   for(int i = 0 ; i < (int)order.size(); i++) {
	     if(order[i] == 'L') AccLp1++;
	     if(order[i] == 'F') AccFp1++;
	     if(order[i] == 'D') AccDp1++;
	     if(order[i] == 'S') AccSp1++;
	     if(order[i] == 'P') AccPp1++;
	   }
	   if(AccLp1 > 2 || AccFp1 > 2|| AccDp1 > 2 || AccSp1 > 2 || AccPp1 > 2) {
	     cerr << "too much same ability" << endl;
	     exit(1);
	   }
	   initAbility(order[0], &p1A1);
	   initAbility(order[1], &p1A2);
	   initAbility(order[2], &p1A3);
	   initAbility(order[3], &p1A4);
	   initAbility(order[4], &p1A5);
	   A1 = 1;
            
	 }
	 if((string) argv[i] == "-ability2") {
	   string order = (string) argv[i+1];
	   for(int i = 0 ; i < (int)order.size(); i++) {
	     if(order[i] == 'L') AccLp2++;
	     if(order[i] == 'F') AccFp2++;
	     if(order[i] == 'D') AccDp2++;
	     if(order[i] == 'S') AccSp2++;
	     if(order[i] == 'P') AccPp2++;
	   }
	   if(AccLp2 > 2 || AccFp2 > 2|| AccDp2 > 2 || AccSp2 > 2 ||  AccPp2 > 2) {
	     cerr << "too much same ability" << endl;
	     exit(1);
	   }
	   initAbility(order[0], &p2A1);
	   initAbility(order[1], &p2A2);
	   initAbility(order[2], &p2A3);
	   initAbility(order[3], &p2A4);
	   initAbility(order[4], &p2A5);
            A2 = 1;
	 }
	 if((string) argv[i] == "-link1") {
	   string order = (string) argv[i+1];
	   int orderf = 1;
	   initPiece(&p1L1, order[0], order[1], 1, orderf, orderf);
	   initPiece(&p1L2, order[2], order[3], 1, orderf, orderf);
	   initPiece(&p1L3, order[4], order[5], 1, orderf, orderf);
	   initPiece(&p1L4, order[6], order[7], 1, orderf, orderf);
	   initPiece(&p1L5, order[8], order[9], 1, orderf, orderf);
	   initPiece(&p1L6, order[10], order[11], 1, orderf, orderf);
	   initPiece(&p1L7, order[12], order[13], 1, orderf, orderf);
	   initPiece(&p1L8, order[14], order[15], 1, orderf, orderf);
            P1 = 1;
	 }
	 if((string) argv[i] == "-link2") {
	   string order = (string) argv[i+1];
	   int orderf = 1;
	   initPiece(&p2L1, order[0], order[1], 0, orderf, orderf);
	   initPiece(&p2L2, order[2], order[3], 0, orderf, orderf);
	   initPiece(&p2L3, order[4], order[5], 0, orderf, orderf);
	   initPiece(&p2L4, order[6], order[7], 0, orderf, orderf);
	   initPiece(&p2L5, order[8], order[9], 0, orderf, orderf);
	   initPiece(&p2L6, order[10], order[11], 0, orderf, orderf);
	   initPiece(&p2L7, order[12], order[13], 0, orderf, orderf);
	   initPiece(&p2L8, order[14], order[15], 0, orderf, orderf);
	   P2 = 1;
	 }
	 if((string) argv[i] == "-graphics") {
	   needGraphic = 1;
	 }
    }
    
    if(A1 == 0) {
      initAbility('L', &p1A1);
      initAbility('F', &p1A2);
      initAbility('D', &p1A3);
      initAbility('S', &p1A4);
      initAbility('P', &p1A5);
      A1 = 1;
    }
    if(A2 == 0) {
      initAbility('L', &p2A1);
      initAbility('F', &p2A2);
      initAbility('D', &p2A3);
      initAbility('S', &p2A4);
      initAbility('P', &p2A5);
      A2 = 1;
    }
    if(P1 == 0) {
      //V1V2V3V4D1D2D3D4
      int orderf = 1;
            initPiece(&p1L1, 'V', '1', 1, orderf, orderf);
            initPiece(&p1L2, 'V', '2', 1, orderf, orderf);
            initPiece(&p1L3, 'V', '3', 1, orderf, orderf);
            initPiece(&p1L4, 'V', '4', 1, orderf, orderf);
            initPiece(&p1L5, 'D', '1', 1, orderf, orderf);
            initPiece(&p1L6, 'D', '2', 1, orderf, orderf);
            initPiece(&p1L7, 'D', '3', 1, orderf, orderf);
            initPiece(&p1L8, 'D', '4', 1, orderf, orderf);
            P1 = 1;
    }
    if(P2 == 0) {
               //V1V2V3V4D1D2D3D4
      int orderf = 1;
      initPiece(&p2L1, 'V', '1', 0, orderf, orderf);
      initPiece(&p2L2, 'V', '2', 0, orderf, orderf);
      initPiece(&p2L3, 'V', '3', 0, orderf, orderf);
      initPiece(&p2L4, 'V', '4', 0, orderf, orderf);
               initPiece(&p2L5, 'D', '1', 0, orderf, orderf);
               initPiece(&p2L6, 'D', '2', 0, orderf, orderf);
               initPiece(&p2L7, 'D', '3', 0, orderf, orderf);
               initPiece(&p2L8, 'D', '4', 0, orderf, orderf);
               P2 = 1;
    }
    if(A1) {
      AbilitySetPlayer1.emplace_back(&p1A1);
      AbilitySetPlayer1.emplace_back(&p1A2);
      AbilitySetPlayer1.emplace_back(&p1A3);
      AbilitySetPlayer1.emplace_back(&p1A4);
      AbilitySetPlayer1.emplace_back(&p1A5);
    }
    if(A2) {
      AbilitySetPlayer2.emplace_back(&p2A1);
      AbilitySetPlayer2.emplace_back(&p2A2);
      AbilitySetPlayer2.emplace_back(&p2A3);
      AbilitySetPlayer2.emplace_back(&p2A4);
      AbilitySetPlayer2.emplace_back(&p2A5);
    }
    if(P1) {
      PieceSetPlayer1.insert({"a", &p1L1});
      PieceSetPlayer1.insert({"b", &p1L2});
      PieceSetPlayer1.insert({"c", &p1L3});
      PieceSetPlayer1.insert({"d", &p1L4});
      PieceSetPlayer1.insert({"e", &p1L5});
      PieceSetPlayer1.insert({"f", &p1L6});
      PieceSetPlayer1.insert({"g", &p1L7});
      PieceSetPlayer1.insert({"h", &p1L8});
    }
    if(P2) {
      PieceSetPlayer2.insert({"A", &p2L1});
      PieceSetPlayer2.insert({"B", &p2L2});
      PieceSetPlayer2.insert({"C", &p2L3});
      PieceSetPlayer2.insert({"D", &p2L4});
      PieceSetPlayer2.insert({"E", &p2L5});
      PieceSetPlayer2.insert({"F", &p2L6});
      PieceSetPlayer2.insert({"G", &p2L7});
      PieceSetPlayer2.insert({"H", &p2L8});
    }
    b.init();
    
    //	std::cout << "reach up to the graphic" << std::endl;
    
    
    if(needGraphic) {
      //std::cout << "reach the graphic" << std::endl;
      
      G.notify(&b);
      //        std::cout << "done" << std::endl;
    }
    // G = GraphicDisplay("true");
    // unique_ptr<Board>p1b(&b);
    // unique_ptr<Board>p2b(&b);
    p1 = Player(AbilitySetPlayer1, 1, &p2, PieceSetPlayer1,&b);
    p2 = Player(AbilitySetPlayer2, 0, &p1, PieceSetPlayer2,&b);
    string cmd = "";
    bool player1Turn = 1;
    int abilityUsed1 = 0;
    int abilityUsed2 = 0;
    try {
      while (true){
	      if(cin.eof()) return 1;
	  cin >> cmd;
	 // std::cout << cin.fail() << std:: endl << std::endl;
	 if(cmd != "ability" && abilityUsed1 && !player1Turn) abilityUsed1 = 0;
	 if(cmd != "ability" && abilityUsed2 && player1Turn) abilityUsed2 = 0;
	if(cmd == "move") {
		//cout << "new main " << endl;
	  string PieceName;
	  string Direction;
	  cin >> PieceName;
	  cin >> Direction;
	  if(player1Turn) {
	    try{
	      p1.movePiece(Direction, PieceName);
	    } catch(...) {
                           continue;
	    }
	    player1Turn = 0;
	  } else {
	    try{
	      p2.movePiece(Direction, PieceName);
	    } catch(...) {
	      continue;
	    }
	    player1Turn = 1;
	  }
	  
	}
	if(cmd == "board") {
	  //	       G.notify(&b);
	  if(player1Turn) {
	    p1.PrintThisRound();
	    cout << b;
	    p2.PrintOtherRound();
	    //     player1Turn = 0;
	  } else {
	    p1.PrintOtherRound();
	    cout << b;
	    p2.PrintThisRound();
	    //       player1Turn = 1;
	  }
	}
	if(cmd == "abilities") {
	  if(player1Turn) {
	    p1.showAbility();
	    //         player1Turn = 0;
	  } else {
	    p2.showAbility();
	    //       player1Turn = 1;
	  }
	}
	if(cmd == "ability") {
	  int ID;
	  cin >> ID;
	  if(player1Turn) {
      abilityUsed2 = 0;
      if(abilityUsed1 == 1) {
	cout << "you can only use 1 ability per turn -_-#" << endl;
	continue;
      }
      if(AbilitySetPlayer1[ID - 1]->getName() == "FireWall") {
	int a;
	int b;
	cin >> a;
	cin >> b;
	if(p1.useAbility(ID, "none", a, b) == 1) abilityUsed1++;
	//         player1Turn = 0;
      } else {
	string name ;
	cin >> name;
	if(p1.useAbility(ID, name, -1, -1) == 1) abilityUsed1++;
	//       player1Turn = 0;
      }
      
	  } else {
	    abilityUsed1 = 0;
	    if(abilityUsed2 == 1) {
	      cout << "you can only use 1 ability per turn -_-#" << endl;
	      continue;
	    }
	    if(AbilitySetPlayer2[ID - 1]->getName() == "FireWall") {
	      int a;
	      int b;
	      cin >> a;
	      cin >> b;
	      if(p2.useAbility(ID, "none", a, b)) abilityUsed2++;
	      //   player1Turn = 1;
	    } else {
	      string name ;
	      cin >> name;
	      if(p2.useAbility(ID, name, -1, -1)) abilityUsed2++;
	      //  player1Turn = 1;
	    }
	    
	  }
	}
	if(cmd == "quit") {
	  break;
	}
	if(cmd == "sequence") {
	  string fileName;
	  cin >> fileName;
	  ifstream ifs (fileName);
	  bool needquit = 0;
	  while(ifs>>cmd) {
		  if(cmd != "ability" && abilityUsed1 && !player1Turn) abilityUsed1 = 0;
         if(cmd != "ability" && abilityUsed2 && player1Turn) abilityUsed2 = 0;
	    if(cmd == "move") {
	      string PieceName;
	      string Direction;
	      ifs >> PieceName;
	      ifs >> Direction;
	      if(player1Turn) {
		try{
		  p1.movePiece(Direction, PieceName);
		} catch(...) {
		  continue;
                }
		player1Turn = 0;
	      } else {
		try{
                  p2.movePiece(Direction, PieceName);
		} catch(...) {
		  continue;
		}
		player1Turn = 1;
	      }
	      
	    }
	    if(cmd == "board") {
	      if(player1Turn) {
		p1.PrintThisRound();
		cout << b;
		p2.PrintOtherRound();
		//                            player1Turn = 0;
	      } else {
		p1.PrintOtherRound();
		cout << b;
		p2.PrintThisRound();
		//                          player1Turn = 1;
	      }
	    }
	    if(cmd == "abilities") {
	      if(player1Turn) {
		p1.showAbility();
		//                        player1Turn = 0;
	      } else {
		p2.showAbility();
		//                      player1Turn = 1;
	      }
	    }
	    if(cmd == "ability") {

	//cout << "get here" << endl;

	      int ID;


	      ifs >> ID;
	      if(player1Turn) {
		abilityUsed2 = 0;
		if(abilityUsed1 == 1) {
		  cout << "you can only use 1 ability per turn -_-#" << endl;
		  continue;
		}

	//cout << "get here before []" << endl;

		if(AbilitySetPlayer1[ID - 1]->getName() == "FireWall") {

//	 cout << "get here in [] F" << endl;
		  int a;
		  int b;
		  ifs >> a;
		  ifs >> b;
		  if(p1.useAbility(ID, "none", a, b) == 1) abilityUsed1++;
                  //         player1Turn = 0;
		} else {
		  string name ;
		  ifs >> name;
		  if(p1.useAbility(ID, name, -1, -1) == 1) abilityUsed1++;
		  //       player1Turn = 0;
		}
		
	      } else {
		abilityUsed1 = 0;
		if(abilityUsed2 == 1) {
		  cout << "you can only use 1 ability per turn -_-#" << endl;
		  continue;
		}
		if(AbilitySetPlayer2[ID - 1]->getName() == "FireWall") {
		  int a;
		  int b;
		  ifs >> a;
		  ifs >> b;
		  if(p2.useAbility(ID, "none", a, b)) abilityUsed2++;
		  //   player1Turn = 1;
		} else {
		  string name ;
		  ifs >> name;
		  if(p2.useAbility(ID, name, -1, -1)) abilityUsed2++;
		  //  player1Turn = 1;
		}
		
	      }
	    }
	    if(cmd == "quit") {
	      needquit = 1;
	      break;
	    }
	    if(needGraphic) {
	      G.notify(&b);
	    }
	    string score1 = p1.isFull();
	    string score2 = p2.isFull();
	    if(score1 == "notEnd" && score2 == "notEnd") continue;
	    if(score1 == "lose") {
	      cout << "player1 lose, game over" << endl;
	      break;
	    }
	    if(score1 == "win") {
	      cout << "player1 win, game over" << endl;
	      break;
	    }
	    if(score2 == "lose") {
	      cout << "player2 lose, game over" << endl;
	      break;
	    }
	    if(score2 == "win") {
	      cout << "player2 win, game over" << endl;
	      break;
	    }
	  //  cmd = "";
	  }
	  if(needquit) break;
	}
	if(needGraphic) {
	  G.notify(&b);
	}
	string score1 = p1.isFull();
	string score2 = p2.isFull();
	if(score1 == "notEnd" && score2 == "notEnd") continue;
	if(score1 == "lose") {
	  cout << "player1 lose, game over" << endl;
	  break;
	}
	if(score1 == "win") {
	  cout << "player1 win, game over" << endl;
	  break;
	}
	if(score2 == "lose") {
	  cout << "player2 lose, game over" << endl;
	  break;
	}
	if(score2 == "win") {
	  cout << "player2 win, game over" << endl;
	  break;
	}
	//cmd = "";
	//if(cin.eof()) break;
      }
    } catch (ios::failure &) {}  // Any I/O failure quits
}
