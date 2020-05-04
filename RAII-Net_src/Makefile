CXX = g++
CXXFLAGS = -std=c++14 -Wall
OBJECTS = main.o board.o piece.o player.o textdisplay.o cell.o ability.o Graphicdisplay.o window.o
EXEC = RAIInet

${EXEC}: main.o board.o piece.o player.o textdisplay.o cell.o ability.o Graphicdisplay.o window.o
	${CXX} ${CXXFLAGS} ${OBJECTS}  -lX11  -o ${EXEC}

board.o: board.cc board.h

window.o: window.cc window.h

Graphicdisplay.o: Graphicdisplay.cc Graphicdisplay.h

pieces.o: piece.cc piece.h 

player.o: player.cc player.h

textdisplay.o: textdisplay.cc textdisplay.h

cell.o: cell.cc cell.h 

ability: ability.cc ability.h

main.o: main.cc board.h piece.h player.h ability.h Graphicdisplay.h window.h

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
