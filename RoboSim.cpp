/******************************
* Independent Project: NAQSHA
* Faizan Muhammad
* RoboSim.cpp
* Naqsha Class Testing
* Date Created: 8th April 2017
*******************************/

#include "Naqsha.h"
#include "SpacePacket.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

const int WIDTH = 10;
const int HEIGHT = 10;

using namespace std;

//Reads the map from file
void readFromFile(string filename, char textMap[][HEIGHT*2 + 1]);
//Creates SpacePackets from the map
void fillBoxes(char textMap[][HEIGHT*2 + 1], SpacePacket boxes[][HEIGHT]);
//Prints text map from array
void displayTextMap(char textMap[][HEIGHT*2 + 1]);

int main(){
	Naqsha map;
	char textMap[WIDTH*2 + 1][HEIGHT*2 + 1];
	SpacePacket boxes[WIDTH][HEIGHT];
	
	cout << "Enter Map File Name: ";
	string filename;
	cin >> filename;

	readFromFile(filename, textMap);
	cout << "The Map Read From File: \n";
	displayTextMap(textMap);

	fillBoxes(textMap, boxes);

	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			map.addInfo(boxes[i][j]);
		}
	}

	cout << "The Map in Naqsha: \n";
	map.print();

	bool stop = false;

	while(!stop){
		int xFrom;
		int yFrom;
		int xTo;
		int yTo;

		cout << "Enter xFrom: ";
		cin >> xFrom;
		cout << "Enter yFrom: ";
		cin >> yFrom;
		cout << "Enter xTo: ";
		cin >> xTo;
		cout << "Enter yTo: ";
		cin >> yTo;

		cout << "0 - UP, 1 - RIGHT, 2 - DOWN, 3 - LEFT \n";
		cout << "One path to take     : ";
		cout << map.getAPath(xFrom, yFrom, xTo, yTo);
		cout << endl;

		cout << "Shortest path to take: ";
		cout << map.getShortestPath(xFrom, yFrom, xTo, yTo);
		cout << endl;

		cout << "Continue? (y to continue): ";
		string ans;
		cin >> ans;
		if(ans != "y"){
			stop = true;
		}
	}
}

//Takes:   filename and ref to array
//Returns: Nothing
//Does:    Reads the text into array
void readFromFile(string filename, char textMap[][HEIGHT*2 + 1]){
	ifstream fileRead;
	fileRead.open(filename.c_str());
	if(!fileRead.is_open()){
		cerr << "File Not Read!\n";
		exit(1);
	}

	for(int i = 0; i < HEIGHT*2 + 1; i++){
		string line;
		getline(fileRead, line, '\n');
		for(int j = 0; j < WIDTH*2 + 1; j++){
			textMap[j][i] = line[j];
		}
	}
}

//Takes:   ref to text array and array of SpacePackets
//Returns: Nothing
//Does:    Fills the boxes with data based on array
void fillBoxes(char textMap[][HEIGHT*2 + 1], SpacePacket boxes[][HEIGHT]){
	int a = 0;
	int b = 0;

	for(int x = 1; x < WIDTH*2 + 1; x = x + 2){
		for(int y = HEIGHT*2 - 1; y > 0; y = y - 2){
			boxes[b][a].xCoord = b;
			boxes[b][a].yCoord = a;

			//Checking Walls
			//Top
			if(textMap[x][y - 1] == '-'){
				boxes[b][a].isWall[0] = true;
			}
			else{
				boxes[b][a].isWall[0] = false;
			}

			//Right
			if(textMap[x + 1][y] == '|'){
				boxes[b][a].isWall[1] = true;
			}
			else{
				boxes[b][a].isWall[1] = false;
			}

			//Bottom
			if(textMap[x][y + 1] == '-'){
				boxes[b][a].isWall[2] = true;
			}
			else{
				boxes[b][a].isWall[2] = false;
			}

			//Left
			if(textMap[x- 1][y] == '|'){
				boxes[b][a].isWall[3] = true;
			}
			else{
				boxes[b][a].isWall[3] = false;
			}

			a = a + 1;
		}
		b = b + 1;
		a  = 0;
	}
}

//Takes:   array of text
//Returns: Nothing
//Does:    Prints the array to screen
void displayTextMap(char textMap[][HEIGHT*2 + 1]){
	for(int y = 0; y < HEIGHT*2 + 1; y++){
		for(int x = 0; x < WIDTH*2 + 1; x++){
			cout << textMap[x][y];
		}
		cout << endl;
	}
}

