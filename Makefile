CXX = g++
CXXFLAGS = -Wall -MMD
OBJECTS = Card.o Command.o ComputerPlayer.o Deck.o Game.o HumanPlayer.o Player.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}