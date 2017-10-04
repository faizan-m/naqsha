/******************************
* Independent Project: NAQSHA
* Faizan Muhammad
* testCellRelation.h
* Cell Class Testing
* Date Created: 8th April 2017
*******************************/

#include "Cell.h"
#include "KDTree.h"
#include <iostream>

using namespace std;

const int GRIDSIZE = 10;

int main(){
	KDTree<Cell> tree;

	//Testing Constructor
	for(int x = 0; x < GRIDSIZE; x++){
		for(int y = 0; y < GRIDSIZE; y++){
			Cell *temp = new Cell;

			SpacePacket tempData;
			tempData.xCoord = x;
			tempData.yCoord = y;

			temp->savePacket(tempData);

			//Inserting and Connecting
			tree.insertNode(x, y, temp);
			temp->establishRelation(0, tree.findData(x, y + 1));
			temp->establishRelation(1, tree.findData(x + 1, y));
			temp->establishRelation(2, tree.findData(x, y - 1));
			temp->establishRelation(3, tree.findData(x - 1, y));
		}
	}

	//Printing Neighbours and Checking
	for(int x = 0; x < GRIDSIZE; x++){
		for(int y = 0; y < GRIDSIZE; y++){
			cout << x << " " << y << ": ";
			tree.findData(x, y)->printNeighbours();
		}
	}

	//Testing Destructors
	for(int x = 0; x < GRIDSIZE; x++){
		for(int y = 0; y < GRIDSIZE; y++){
			delete tree.findData(x, y);
		}
	}

}