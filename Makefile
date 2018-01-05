CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -g
OBJECTS = main.o readconsole.o score.o window.o block.o board.o display.o game.o level.o position.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris
$EXEC : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -lXpm -lncurses
-include ${DEPENDS}
.PHONY: clean
clean :
	rm ${OBJECTS} ${EXEC}
