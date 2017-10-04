/******************************
* Independent Project: NAQSHA
* Faizan Muhammad
* Cell.h
* Cell Class Definition
* Date Created: 8th April 2017
*******************************/

#include "SpacePacket.h"

class Cell{
	public:
		Cell();
		~Cell();
		
		void savePacket(SpacePacket inData);
		SpacePacket getPacket();
		int getX();
		int getY();
		void establishRelation(int edge, Cell *neighbour);
		Cell *getNeighbour(int edge);
		void removeRelation(int edge);
		bool isWall(int edge);
		void printNeighbours();

		void setTraverse(bool traverse);
		bool getTraverse();

		void setDistance(int distance);
		int getDistance();

		void setPrevEdge(int edge);
		int getPrevEdge();

	private:
		struct Relation{
			bool wall;
			bool doorway;
			bool window;
			
			Cell *other;
		};

		int xCoord;
		int yCoord;

		//For Path Finding
		bool traverseMarker;
		int pathDistance;
		int previousEdge;

		SpacePacket data;
		static const int EDGES = 4;
		Relation directions[EDGES];

		void setWall(int edge, bool isWall);

};
