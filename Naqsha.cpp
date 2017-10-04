/******************************
* Independent Project: NAQSHA
* Faizan Muhammad
* Naqsha.cpp
* Naqsha Class Implementation
* Date Created: 8th April 2017
*******************************/
#include "Naqsha.h"
#include <iostream>

using namespace std;
//------------------------Constructor and Destructor----------------------------
Naqsha::Naqsha(){
		minX = 0;
		minY = 0;
		maxX = 0;
		maxY = 0;
}

Naqsha::~Naqsha(){
	Cell *temp = coordTree.getMaxX();
	//Keep deleting till tree is empty
	while(temp != nullptr){
		coordTree.deleteNode(temp->getX(), temp->getY());
		delete temp;
		temp = coordTree.getMaxX();
	}
}

//----------------------------Public Functions----------------------------------
//Takes:   SpacePacket to add
//Returns: Nothing
//Does:    Creates new cell for the packet and adds an entry in the tree
void Naqsha::addInfo(SpacePacket inData){
	//Checking if already exists
	Cell *checkTemp  = coordTree.findData(inData.xCoord, inData.yCoord);
	if(checkTemp != nullptr){
		delete checkTemp;
	}

	//Creating new cell
	Cell *newCell = new Cell;

	//Entering New Cell, Overwrites Old Node if present
	coordTree.insertNode(inData.xCoord, inData.yCoord, newCell);

	//Initializing New Cell
	newCell->savePacket(inData);

	//Connecting with neighbours
	connectNeighbours(newCell);

}

//Takes:   Coordinates to remove
//Returns: Nothing
//Does:    Removes the cell specified by the coordinates if it exists
void Naqsha::removeInfo(int x, int y){
	//Checking if it exists
	Cell *checkTemp  = coordTree.findData(x, y);
	if(checkTemp != nullptr){
		//Deleting
		delete checkTemp;
		coordTree.deleteNode(x, y);
	}
}

//Takes:   Coordinates to check
//Returns: true or false
//Does:    Checks to see if given coordinates exist
bool Naqsha::checkExists(int x, int y){
	return coordTree.isPresent(x, y);
}

//Takes:   Coordinates whose packet is needed
//Returns: SpacePacket
//Does:    Finds and returns the packet, if not found returns a packet with name
//		   NULL.
SpacePacket Naqsha::getInfo(int x, int y){
	//Checking if it exists
	Cell *checkTemp  = coordTree.findData(x, y);
	if(checkTemp != nullptr){
		return checkTemp->getPacket();
	}
	else{
		SpacePacket empty;
		empty.name = "NULL";
		return empty;
	}
}

//Takes:   The coordinates from and to
//Returns: Path of edges to choose, if path exists
//Does:    Finds a possible path recursively
string Naqsha::getAPath(int xFrom, int yFrom, int xTo, int yTo){
		Cell *current = coordTree.findData(xFrom, yFrom);
		Cell *destination = coordTree.findData(xTo, yTo);

		if(current == nullptr or destination == nullptr){
			return "location_unknown";
		}

		clearMarkers(current);
		string path = getACellPath(current, destination);
		if (path == ""){
			return "no_known_path";
		}
		else{
			return path;
		}
}

//Takes:   The coordinates from and to
//Returns: Path of edges to choose, if path exists
//Does:    Finds shortest possible path by DFS
string Naqsha::getShortestPath(int xFrom, int yFrom, int xTo, int yTo){
		Cell *current = coordTree.findData(xFrom, yFrom);
		Cell *destination = coordTree.findData(xTo, yTo);

		if(current == nullptr or destination == nullptr){
			return "location_unknown";
		}

		clearMarkers(current);
		runDFS(current, 0, -1);
		string path = extractPath(destination);
		clearMarkers(current);

		if(path != "no_known_path"){
			return path + "-DONE-";
		}
		else{
			return path;
		}
}

//Takes:   Nothing
//Returns: Nothing
//Does:    Prints the map
void Naqsha::print(){
	updateMinMax();
	int width = maxX - minX + 1;
	int height = maxY - minY + 1;

	width = width*2 + 1;
	height = height*2 + 1;

	char **textMap = makeTextArray(width, height);
	fillWalls(textMap, width, height);
	printText(textMap, width, height);
	destroyTextArray(textMap, width);
}

//----------------------------Helper Functions----------------------------------
//Takes:   The cell that needs neighbours connected
//Returns: Nothing
//Does:    Attempts to connect the cell with neighbours
void Naqsha::connectNeighbours(Cell *newCell){
	int xCoord = newCell->getX();
	int yCoord = newCell->getY();

	//Establishing Relations up. right, down, left
	//If neighbour doesn't exist, nullptr is sent as neighbour
	newCell->establishRelation(0, coordTree.findData(xCoord, yCoord + 1));
	newCell->establishRelation(1, coordTree.findData(xCoord + 1, yCoord));
	newCell->establishRelation(2, coordTree.findData(xCoord, yCoord - 1));
	newCell->establishRelation(3, coordTree.findData(xCoord - 1, yCoord));
}

//Takes:   Pointers to Cells
//Returns: Nothing
//Does:    Returns path in terms of edges
string Naqsha::getACellPath(Cell *current, Cell *destination){
	//If doesn't exist or already traversed
	if(current == nullptr or destination == nullptr or current->getTraverse()){
			return "";
	} 

	//If reached
	if(current == destination){
		return "-DONE-";
	}

	//Recursively Checking All edges
	for(int i = 0; i < EDGES; i++){
		if(!current->isWall(i)){
			Cell *neighbour = current->getNeighbour(i);
			current->setTraverse(true);
			string path = getACellPath(neighbour, destination);
			current->setTraverse(false);
			if(path != ""){
				return "-" + to_string(i) + "-" + path;
			}
		}
	}

	return "";
}

//Takes:   Pointer to Cell
//Returns: Nothing
//Does:    Clears all markers for pathfinding in the cell connected to given
void Naqsha::clearMarkers(Cell *current){
	if(current == nullptr){
		return;
	}

	if(current->getTraverse()){
		current->setTraverse(false);
		current->setDistance(-1);
		current->setPrevEdge(-1);

		for(int i = 0; i < EDGES; i++){
			clearMarkers(current->getNeighbour(i));
		}
	}
}

//Takes:   Pointer to Cell
//Returns: Nothing
//Does:    Runs a DFS and updates markers to all Cells connected to current
void Naqsha::runDFS(Cell *current, int distSoFar, int prevEdge){
	if(current == nullptr){
		return;
	}

	//Already been here
	if(current->getTraverse()){
		//Is the new path shorter?
		if(distSoFar < current->getDistance()){
			current->setDistance(distSoFar);
			current->setPrevEdge(prevEdge);
		}
		else{
			//No need to check edges again
			return;
		}
	}
	else{
		//First Time
		current->setTraverse(true);
		current->setDistance(distSoFar);
		current->setPrevEdge(prevEdge);
	}

	//Check out all edges
	for(int i = 0; i < EDGES; i++){
		if(!current->isWall(i)){
			runDFS(current->getNeighbour(i), distSoFar + 1, i);
		}
	}

}

//Takes:   Pointer to Cell
//Returns: Nothing
//Does:    Extracts path by moving backwards
string Naqsha::extractPath(Cell *destination){
	//If it is 0, we are there
	if(destination->getDistance() == 0){
		return "";
	}

	//If it is -1 there is no path
	if(destination->getDistance() == -1){
		return "no_known_path";
	}

	int edge = destination->getPrevEdge();
	int relativeEdge = (edge + EDGES/2)%EDGES;
	Cell *next = destination->getNeighbour(relativeEdge);

	return extractPath(next) + "-" + to_string(edge) + "-";
}


//Takes:   Nothing
//Returns: Nothing
//Does:    Updates the min and max values of x and y
void Naqsha::updateMinMax(){
	Cell *temp = coordTree.getMaxX();
	maxX = temp->getX();

	temp = coordTree.getMinX();
	minX = temp->getX();

	temp = coordTree.getMaxY();
	maxY = temp->getY();

	temp = coordTree.getMinY();
	minY = temp->getY();
}

//Takes:   Width and Height
//Returns: Pointer to 2d array in heap
//Does:    Creates the array and fills with + for corners and O for unknown
char **Naqsha::makeTextArray(int width, int height){
	char **textMap = new char *[width];
	for(int i = 0; i < width; i++){
		textMap[i] = new char [height];
	}

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			textMap[x][y] = 'O';
		}
	}


	for(int x = 0; x < width; x = x + 2){
		for(int y = 0; y < height; y = y + 2){
			textMap[x][y] = '+';
		}
	}

	return textMap;
}

//Takes:   textMap, Width and Height
//Returns: Nothing
//Does:    Fills the Map with walls
void Naqsha::fillWalls(char** textMap, int width, int height){
	for(int x = 1; x < width; x = x + 2){
		for(int y = 1; y < height; y = y + 2){
			textMap[x][y] = ' ';
			int xCoord = minX + (x-1)/2;
			int yCoord = maxY - (y-1)/2;

			SpacePacket current = getInfo(xCoord, yCoord);
			if(current.name == "NULL"){
				break;
			}

			//Wall up
			if(current.isWall[0]){
				textMap[x][y - 1] = '-';
			}
			else{
				textMap[x][y - 1] = ' ';
			}

			//Wall left
			if(current.isWall[1]){
				textMap[x + 1][y] = '|';
			}
			else{
				textMap[x + 1][y] = ' ';
			}

			//Wall down
			if(current.isWall[2]){
				textMap[x][y + 1] = '-';
			}
			else{
				textMap[x][y + 1] = ' ';
			}

			//Wall right
			if(current.isWall[3]){
				textMap[x - 1][y] = '|';
			}
			else{
				textMap[x - 1][y] = ' ';
			}
		}
	}
}

//Takes:   textMap, Width and Height
//Returns: Nothing
//Does:    Prints the textMap to cout
void Naqsha::printText(char** textMap, int width, int height){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			cout << textMap[j][i];
		}
		cout << endl;
	}
}

//Takes:   textMap, Width and Height
//Returns: Nothing
//Does:    Deletes the array
void Naqsha::destroyTextArray(char** textMap, int width){
	for(int i = 0; i < width; i++){
		delete [] textMap[i];
	}

	delete [] textMap;
}


//Uses coordinate system instead of Cell-Relation approach
//Coded for testing only, works for only EDGES = 4
//It is also higher in time complexity and not elegant

//Takes:   The coordinates from and to
//Returns: Path of edges to choose, if path exists
//	 	   Empty String if no path, -DONE- if already there
//Does:    Finds a path recursively
/*string Naqsha::getPath(int xFrom, int yFrom, int xTo, int yTo){
	//cout << "At (" << xFrom << ", " << yFrom << ")\n";
	//Reached
	if(xFrom == xTo and yFrom == yTo){
		return "-DONE-";
	}

	Cell *current = coordTree.findData(xFrom, yFrom);
	if(current == nullptr){
		//cout << "Out of map\n";
		return "";
	}

	if(current->getTraverse()){
		return "";
	}

	//Going Up
	if(!current->isWall(0)){
		//cout << "Going up\n";
		current->setTraverse(true);
		string ans = getPath(xFrom, yFrom + 1, xTo, yTo);
		current->setTraverse(false);
		if(ans != ""){
			return "-0-" + ans;
		}
	}

	//Going Right
	if(!current->isWall(1)){
		//cout << "Going right\n";
		current->setTraverse(true);
		string ans = getPath(xFrom + 1, yFrom, xTo, yTo);
		current->setTraverse(false);
		if(ans != ""){
			return "-1-" + ans;
		}
	}

	//Going Down
	if(!current->isWall(2)){
		//cout << "Going down\n";
		current->setTraverse(true);
		string ans = getPath(xFrom, yFrom - 1, xTo, yTo);
		current->setTraverse(false);
		if(ans != ""){
			return "-2-" + ans;
		}
	}

	//Going Left
	if(!current->isWall(3)){
		//cout << "Going left\n";
		current->setTraverse(true);
		string ans = getPath(xFrom - 1, yFrom, xTo, yTo);
		current->setTraverse(false);
		if(ans != ""){
			return "-3-" + ans;
		}
	}

	//No Path
	return "";
}*/