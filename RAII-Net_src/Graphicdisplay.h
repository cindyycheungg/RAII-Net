#include <cstddef>
#include "ability.h"
#include "piece.h"
#include "player.h"
#include "textdisplay.h"
#include "board.h"
#include "window.h"

#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <fstream>
#include <sstream>

class Xwindow;
class cell;
class GraphicsDisplay {
  
  std::shared_ptr<Xwindow> xw;
  int displaySize = 500;
  int size1 = 8;
  int size2 = 10;
  
 public:
 GraphicsDisplay(std::string s) : xw{std::shared_ptr<Xwindow>(new Xwindow())}, size1{8}, size2{10}{
    if(s != "true") return;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 10; j++) {
	if(j == 0 || j == 9){
	  xw->fillRectangle(i*(displaySize/size1), j*(displaySize/size2), displaySize/size1, displaySize/size2, Xwindow::Blue);
	   xw-> drawString(i*(displaySize/size1) + 15, j*(displaySize/size2) + 30, "River", Xwindow::Cyan);
	  
	} else if(((i == 3 || i == 4) && (j == 1 )) || ((i == 3 || i == 4) && ( j == 8))) {
	  xw->fillRectangle(i*(displaySize/size1), j*(displaySize/size2), displaySize/size1, displaySize/size2, Xwindow::Yellow);
	  xw-> drawBigString(i*(displaySize/size1) + 15, j*(displaySize/size2) + 30, "S", Xwindow::Cyan);
	}
	else {
	  xw->fillRectangle(i*(displaySize/size1), j*(displaySize/size2), displaySize/size1, displaySize/size2, Xwindow::Red);}}
    }
    for(int i = 0 ; i <= 7; i++) {
      xw->drawLine(displaySize/size1*i, 1*(displaySize/size2), displaySize/size1*i, 9*(displaySize/size2));
      
	  }
    for(int i = 0; i <= 9 ; i++) {
      xw->drawLine(0, i*(displaySize/size2),  displaySize/size1*8, i*(displaySize/size2));
	  }
  }
 GraphicsDisplay(): xw{new Xwindow()}, size1{0}, size2{0} {}
  ~GraphicsDisplay() {/*delete xw;*/}
	GraphicsDisplay& operator=(GraphicsDisplay&& m) {
	  std::swap(xw, m.xw);
	  std::swap(size1, m.size1);
	  std::swap(size2, m.size2);
	  std::swap(displaySize, m.displaySize);
		return *this;
	}
        void notify(Board* b) {
	  
		//std::cout << "reach in graphics notify" << std::endl;
	  
	  for(int i = 0; i <= 7; i++) {
	    for(int j = 1; j <= 8; j++) {
	      //std::cout << "inside of the for loop " << std::endl;
	      
	      int r = j*(displaySize/10);
	      int c = i*(displaySize/8);
	      if(b->checkOccupied(i, j) == 0)  xw->fillRectangle(c, r, displaySize/size1, displaySize/size2, Xwindow::Red);	
	      if(b->checkOccupied(i, j) && b->checkPlayer(i, j)) {
		xw->fillRectangle(c, r, displaySize/size1, displaySize/size2, Xwindow::Black);
			xw-> drawBigString(i*(displaySize/size1) + 15, j*(displaySize/size2) + 30, b->checkName(i,j), Xwindow::Cyan);
	      }
	      else if(b->checkOccupied(i, j) && !(b->checkPlayer(i, j))) { 
		xw->fillRectangle(c, r, displaySize/size1, displaySize/size2, Xwindow::White);
			 xw-> drawBigString(i*(displaySize/size1) + 15, j*(displaySize/size2) + 30, b->checkName(i,j), Xwindow::Cyan);
	      }
	      else if(b->checkFW(i, j, "player1")) {
		xw->fillRectangle(c, r, displaySize/size1, displaySize/size2, Xwindow::Brown);
	      }
	      else if(b->checkFW(i, j, "player2")) {
		xw->fillRectangle(c, r, displaySize/size1, displaySize/size2, Xwindow::Orange);
	      }
	    }	
	    //std::cout << "fine" << std::endl;
	  }
	  for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 10; j++) {
	      if(((i == 3 || i == 4) && (j == 1 )) || ((i == 3 || i == 4) && ( j == 8))) {
		xw->fillRectangle(i*(displaySize/size1), j*(displaySize/size2), displaySize/size1, displaySize/size2, Xwindow::Yellow);
		        xw-> drawBigString(i*(displaySize/size1) + 15, j*(displaySize/size2) + 30, "S", Xwindow::Cyan);
	      }
	      
	    }
	  }
	  for(int i = 0 ; i <= 7; i++) {
            xw->drawLine(displaySize/size1*i, 1*(displaySize/size2), displaySize/size1*i, 9*(displaySize/size2));
	    
          }
          for(int i = 0; i <= 9 ; i++) {
            xw->drawLine(0, i*(displaySize/size2),  displaySize/size1*8, i*(displaySize/size2));
          }
	  //		std::cout << "fine " << std::endl;
	}
	
};

