###########################################################################
##                      Makefile for Proj2 (Naqsha)                      ##
###########################################################################

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -std=c++11 -g3

RoboSim: Naqsha.o SpacePacket.o RoboSim.cpp
	${CXX} ${LDFLAGS} -o RoboSim Naqsha.o Cell.o RoboSim.cpp

testKDTree: KDTree.o Cell.o SpacePacket.o testKDTree.cpp
	${CXX} ${LDFLAGS} -o testKDTree Cell.o testKDTree.cpp

testCellRelation: Cell.o SpacePacket.o testCellRelation.cpp
	${CXX} ${LDFLAGS} -o testCellRelation Cell.o testCellRelation.cpp

KDTree.o: KDTree.h 

Cell.o: Cell.cpp Cell.h SpacePacket.o

Naqsha.o: Cell.o KDTree.o SpacePacket.o Naqsha.h Naqsha.cpp

SpacePacket.o: SpacePacket.h

provide: 
		provide comp15 proj2ind Makefile README KDTree.h Cell.h Cell.cpp \
				SpacePacket.h Naqsha.h Naqsha.cpp RoboSim.cpp testKDTree.cpp \
				testCellRelation.cpp allWalls.txt noWalls.txt maze.txt \
				hugeMaze.txt
clean:
	rm *.o