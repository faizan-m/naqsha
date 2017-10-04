/******************************
* Independent Project: NAQSHA
* Faizan Muhammad
* SpacePacket.h
* SpacePacket Struct Definition
* Date Created: 8th April 2017
*******************************/

#ifndef SPACEPACKET_H
#define SPACEPACKET_H

#include <string>

struct SpacePacket{
	//Necessary Items
	static const int EDGES = 4;
	std::string name;
	int xCoord;
	int yCoord;
	bool isWall[4];
	
	//Add whatever else about the Cell's space
};

#endif