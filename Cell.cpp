/******************************
* Independent Project: NAQSHA
* Faizan Muhammad
* Cell.cpp
* Cell Class Implementation
* Date Created: 8th April 2017
*******************************/

#include "Cell.h"
#include <iostream>

using namespace std;
//-----------------------Constructor and Destructor-----------------------------
Cell::Cell(){
	xCoord = 0;
	yCoord = 0;
	for(int i = 0; i < EDGES; i++){
		directions[i].other = nullptr;
	}
	traverseMarker = false;
	pathDistance = -1;
	previousEdge = -1;
}

Cell::~Cell(){
	for(int i = 0; i < EDGES; i++){
		removeRelation(i);
	}
}

//-------------------------Public Functions-------------------------------------
//Takes:   SpacePacket
//Returns: Nothing
//Does:    Assimilates SpacePacket in the cell
void Cell::savePacket(SpacePacket inData){
	data = inData;
	for(int i = 0; i < EDGES; i++){
		setWall(i, data.isWall[i]);
	}
	xCoord = data.xCoord;
	yCoord = data.yCoord;
}

//Takes:   Nothing
//Returns: SpacePacket
//Does:    Returns the SpacePacket of the Cell
SpacePacket Cell::getPacket(){
	return data;
}

//Takes:   Nothing
//Returns: Int
//Does:    Returns the x coordinate of the cell
int Cell::getX(){
	return xCoord;
}

//Takes:   Nothing
//Returns: Int
//Does:    Returns the y coordinate of the cell
int Cell::getY(){
	return yCoord;
}

//Takes:   The edge and the pointer to neigbour
//Returns: Nothing
//Does:    Adds the neighbour and makes the neighbour add it
void Cell::establishRelation(int edge, Cell *neighbour){
	if(neighbour == nullptr){
		return;
	}
	else if(directions[edge].other != neighbour){
		directions[edge].other = neighbour;
		neighbour->establishRelation((edge + (EDGES/2))%EDGES, this);
	}
}

//Takes:   Int
//Returns: Pointer to cell
//Does:    Returns the corresponding neighbour to the given endge
Cell *Cell::getNeighbour(int edge){
	return directions[edge].other;
}

//Takes:   Int
//Returns: Nothing
//Does:    Removes the relation of an edge and makes the neighbour remove too
void Cell::removeRelation(int edge){
	if(directions[edge].other != nullptr){
		Cell *neighbour = directions[edge].other;
		directions[edge].other = nullptr;
		neighbour->removeRelation((edge + (EDGES/2))%EDGES);
	}
}

//Takes:   Edge as int
//Returns: bool 
//Does:    true if wall at edge
bool Cell::isWall(int edge){
	return directions[edge].wall;
}

//Takes:   Nothing
//Returns: Nothing
//Does:    Prints the edges with neighbours of the cell
void Cell::printNeighbours(){
	for(int i = 0; i < EDGES; i++){
		if(directions[i].other != nullptr){
			cout << i;
			cout << " ";
		}
	}
	cout << endl;
}

//Takes:   bool 
//Returns: Nothing
//Does:    Sets the traverseMarker
void Cell::setTraverse(bool traverse){
	traverseMarker = traverse;
}

//Takes:   Nothing
//Returns: bool
//Does:    Returns the traverseMarker
bool Cell::getTraverse(){
	return traverseMarker;
}

//Takes:   int
//Returns: Nothing
//Does:    Sets path distance
void Cell::setDistance(int distance){
	pathDistance = distance;
}

//Takes:   Nothing
//Returns: int
//Does:    Returns the path distance
int Cell::getDistance(){
	return pathDistance;
}

//Takes:   int
//Returns: Nothing
//Does:    Sets the previous edge
void Cell::setPrevEdge(int edge){
	previousEdge = edge;
}

//Takes:   Nothing
//Returns: int
//Does:    Returns the previous edge
int Cell::getPrevEdge(){
	return previousEdge;
}
//-----------------------------Helper Functions---------------------------------
//Takes:   int and bool
//Returns: Nothing
//Does:    Sets the given edge's wall status
void Cell::setWall(int edge, bool isWall){
	directions[edge].wall = isWall;
}
