CXX = g++-5 
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla -L/usr/X11R6/lib 
EXEC = biquadris
OBJECTS = blind.o block.o cell.o decorator.o force.o heavy.o iblock.o jblock.o lblock.o level.o level0.o level1.o level2.o level3.o level4.o main.o normal.o oblock.o player.o sblock.o tblock.o window.o zblock.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

