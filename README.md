********************************************************************************
# NAQSHA Readme
********************************************************************************

Time Spent: 25 Hours

*************
Purpose
*************

The purpose of this project was to develop the Naqsha Class. Naqsha stores and
consolidates information about a map, consideration location and walls.

It uses a KDTree as a reference from the coordinates to the Cell locations. It
interfaces using the SpacePacket structure to send in and return data about the
Cell. For paths it returns a string of edges to choose from the start point to
the end point.

***********************
Acknowledgements
***********************

* Delorie.com
	ASCII Mazes for maze.txt and hugeMaze.txt
	http://www.delorie.com/game-room/mazes/genmaze.cgi

* Erica Schwartz, Julie Jiang and Winnona DeSombre
	For all the Guidance and Help!

************
Files:
************

* KDTree.h:
	KDTree Class Implementation. KDTree that can save 2D coordinates with a 
	pointer to a any datatype.

* Cell.h, Cell.cpp:
	Cell Class Implementation. Defines a unit on the map. Contains the Relation
	structure that points to other cells around. Has a constant EDGES number of
	edges, currently at 4.

* SpacePacket.h:
	A simple struct that allows communication to and fro Naqsha.

* Naqsha.h, Naqsha.cpp:
	Naqsha Class Implementation. The target class of the project. Contains and
	consolidates info about the map sent through space packets. Can provide 
	shortest path between places if known.

* RoboSim.cpp
	RoboSim Implementation. Reads in a text map from a given file. Converts it 
	in SpacePackets and sends them to Naqsha. Then provides an interface to 
	Naqsha to find paths.

* maze.txt, hugeMaze.txt, noWalls.txt, allWalls.txt
	Sample maps for testing through RoboSim.

* testCellRelation.cpp
	Testing of Cells and Relations. Creates a grid of cells and connects them 
	up. Prints the neighbours of each cell. Also tests the capability of the
	tree to hold Cell data.

* testKDTree.cpp
	Testing of KDTree. Gives an interface for insertion and deletion from KDTree
	so all cases can be tested by terminal. Every iteration adds a random 
	element in the tree and asks for x, y for deletion.

* Makefile
	Makefile for the project. With instructions to build all programs.

* README
	Guide to the completed NAQSHA project.

*************************************
Data Structures and Algorithms:
*************************************

* KDTree:
	KDTree structure is an extension of the concept of BSTrees. While BSTrees
	are based on a single value that is used to decide a new node's location, 
	this particular KDTrees uses 2. As a result, this structure allows for the
	coordinates to be referenced to the Cell pointers in a way that makes it 
	really efficient to store, retrieve and delete coordinates. 

	The algorithms used in implementation are similar to typical BSTree ones
	except that they consider the dimension at every level as the dimension 
	alternates at every level.

* Cell:
	A Cell represent a vertex if you cosider the map to be a graph. The edges
	are represented by Relations inside the Cell. This graph based approach is
	very flexible and allows for a lot of relevant potential algorithms to 
	traverse through them.

* Recursive Search: 
	This search returns a path by recursively going through all Cells until
	detination is reached. The path is not guaranteed to be the shortest.

* Depth First Search:
	This search runs a Depth First Search considering the distances into account
	as well. It updates the markers in the Cell containing distance and previous
	edge for shortest paths. Once the DFS has run. A path extractor is used from
	the destination to extract the path.

***********************
Testing Strategy
***********************

KDTree was tested by the testKDTree.cpp and its modifications.

Cell was tested by testCellRelation.cpp and its modifications.

Naqsha was tested by RoboSim.cpp. The maps it was tested with are also included.


*******************
Future Plans
*******************

* Use Polar (Radius, Angle) instead of Cartesian (x, y) Coordinates

* Find Hameltonian Paths/Circuits from a given starting point

* Test and optimize for edges > 4 and variable edges per Cell

* Add option for consideration of windows, doorways etc.

