/******************************
* Independent Project: NAQSHA
* Faizan Muhammad
* testKDTree.cpp
* KDTree Class Testing
* Date Created: 8th April 2017
*******************************/
#include "KDTree.h"
#include "Cell.h"
#include <iostream>
#include <stdlib.h>
#include "SpacePacket.h"

using namespace std;

void randomInserter(KDTree<Cell> &tree);
void deleter(KDTree<Cell> &tree);

int main(){
	KDTree<Cell> tree;
	for(int i = 0; i < 50; i++){
		randomInserter(tree);
		deleter(tree);
	}
	
}

void randomInserter(KDTree<Cell> &tree){
	int x = (rand() % 100) - 50;
	int y = (rand() % 100) - 50;

	Cell *temp = new Cell;
	SpacePacket tempData;
	tempData.xCoord = x;
	tempData.yCoord = y;

	temp->savePacket(tempData);

	tree.insertNode(x, y, temp);

	tree.print();
	cout << "Size = " << tree.size();
	cout << " Min X = " << tree.getMinX()->getX();
	cout << " Max X = " << tree.getMaxX()->getX();
	cout << " Min Y = " << tree.getMinY()->getY();
	cout << " Max Y = " << tree.getMaxY()->getY();
	if(tree.isPresent(x, y)){
		cout << " Found!\n";
	}
	else{
		cout << " Not Found!\n";
		exit(1);
	}
}

void deleter(KDTree<Cell> &tree){
	int x,y;
	cout << "X to Delete: ";
	cin >> x;
	cout << "Y to Delete: ";
	cin >> y;
	if(tree.deleteNode(x, y)){
		cout << "Deleted!\n";
	}
	else{
		cout << "Not Found!\n";
	}
}