/******************************
* Independent Project: NAQSHA
* Faizan Muhammad
* Naqsha.h
* Naqsha Class Definition
* Date Created: 8th April 2017
*******************************/
#include "KDTree.h"
#include "Cell.h"
#include "SpacePacket.h"
#include <string>


class Naqsha{
	public:
		Naqsha();
		~Naqsha();

		void addInfo(SpacePacket inData);
		void removeInfo(int x, int y);
		bool checkExists(int x, int y);
		SpacePacket getInfo(int x, int y);
		string getAPath(int xFrom, int yFrom, int xTo, int yTo);
		string getShortestPath(int xFrom, int yFrom, int xTo, int yTo);
		void print();

	private:
		static const int EDGES = 4;
		
		KDTree<Cell> coordTree;

		int minX;
		int minY;

		int maxX;
		int maxY;

		void connectNeighbours(Cell *newCell);

		string getACellPath(Cell *current, Cell *destination);

		void clearMarkers(Cell *current);
		void runDFS(Cell *current, int distSoFar, int prevEdge);
		string extractPath(Cell *destination);

		void updateMinMax();
		char **makeTextArray(int width, int height);
		void fillWalls(char** textMap, int width, int height);
		void printText(char** textMap, int width, int height);
		void destroyTextArray(char** textMap, int width);


		//string getPath(int xFrom, int yFrom, int xTo, int yTo);
	
};