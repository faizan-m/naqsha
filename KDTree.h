/*******************************************************
* Independent Project: NAQSHA
* Faizan Muhammad
* KDTree.h
* KDTree Class Definition and Templated Implementation
* Date Created: 8th April 2017
*******************************************************/
#include <iostream>
#include <stdexcept>

using namespace std;

template <class Data> 
class KDTree {
	public:
		//Constructor and Destructor
		KDTree();
		~KDTree();

		//Public Functions
		void insertNode(int x, int y, Data *netLocation);
		Data *findData(int x, int y);
		bool isPresent(int x, int y);
		bool deleteNode(int x, int y);
		int size();
		bool isEmpty();
		void clear();

		Data *getMaxX();
		Data *getMaxY();

		Data *getMinX();
		Data *getMinY();

		void print();

	private:
		struct KDNode{
			int xCoord;
			int yCoord;

			Data *netLocation;

			KDNode *left;
			KDNode *right;
		};
		
		KDNode *root;

		//Helper Functions
		KDNode newNode(int x, int y, Data *netLocation);
		KDNode *recClear(KDNode *root);
		KDNode *recInsert(KDNode *value, char dimension, KDNode *root);
		KDNode *recFind(int x, int y, char dimension, KDNode *root);
		int recSize(KDNode *root);
		KDNode *recDelete(int x, int y, char dimension, KDNode *root, 
															   bool &isDeleted);
		void recPrint(KDNode *root);
		KDNode *recGetMaxX(KDNode *root, char dimension);
		KDNode *recGetMaxY(KDNode *root, char dimension);
		KDNode *recGetMinX(KDNode *root, char dimension);
		KDNode *recGetMinY(KDNode *root, char dimension);

		void emptyThrower();
};

/*******************************************************************************
*****-----------------------------FUNCTIONS----------------------------------***
*******************************************************************************/

//Constructor and Destructor
template <class Data>
KDTree<Data>::KDTree(){
	root = nullptr;
}

template <class Data>
KDTree<Data>::~KDTree(){
	clear();
}

//------------------------------Public Functions--------------------------------
//Takes:   xy coordinates and Data pointer
//Does:    Creates a node in tree and inserts it
//Returns: Nothing
template <class Data>
void KDTree<Data>::insertNode(int x, int y, Data *netLocation){
	KDNode *temp = new KDNode;
	temp->xCoord = x;
	temp->yCoord = y;
	temp->netLocation = netLocation;
	temp->left = nullptr;
	temp->right = nullptr;
	root = recInsert(temp, 'x', root);
}

//Takes:   xy coordinates
//Does:    Tries to find the corresponding node and extracts pointer
//Returns: Pointer to Data if found, nullptr if not
template <class Data>
Data *KDTree<Data>::findData(int x, int y){
	KDNode *temp = recFind(x, y, 'x', root);
	if (temp == nullptr){
		return nullptr;
	}
	else{
		return temp->netLocation;
	}
}

//Takes:   xy coordinates
//Does:    Checks to see if given coordinates are present
//Returns: true or false 
template <class Data>
bool KDTree<Data>::isPresent(int x, int y){
	KDNode *temp = recFind(x, y, 'x', root);
	return(temp != nullptr);
}

//Takes:   xy coordinates
//Does:    Tries to delete corresponding node
//Returns: true if deleted, false if not
template <class Data>
bool KDTree<Data>::deleteNode(int x, int y){
	bool isDone = false;
	root = recDelete(x, y, 'x', root, isDone);
	return isDone;
}

//Takes:   Nothing
//Does:    Finds size
//Returns: int value of size
template <class Data>
int KDTree<Data>::size(){
	return recSize(root);
}

//Takes:   Nothing
//Does:    Checks if tree is empty
//Returns: Nothing
template <class Data>
bool KDTree<Data>::isEmpty(){
	return (root == nullptr);
}

//Takes:   Nothing
//Does:    Clears entire tree
//Returns: Nothing
template <class Data>
void KDTree<Data>::clear(){
	root = recClear(root);
}

//Takes:   Nothing
//Does:    Prints entire tree
//Returns: Nothing
template <class Data>
void KDTree<Data>::print(){
	recPrint(root);
	cout << "\n";
}

//Takes:   Nothing
//Does:    Finds max x coordinate
//Returns: Max x coordinate's pointer
template <class Data>
Data *KDTree<Data>::getMaxX(){
	KDNode *temp = recGetMaxX(root, 'x');
	if(temp == nullptr){
		return nullptr;
	}
	else{
		return temp->netLocation;
	}	
}

//Takes:   Nothing
//Does:    Finds max y coordinate
//Returns: Max y coordinate's pointer
template <class Data>
Data *KDTree<Data>::getMaxY(){
	KDNode *temp = recGetMaxY(root, 'x');
	if(temp == nullptr){
		return nullptr;
	}
	else{
		return temp->netLocation;
	}	
}

//Takes:   Nothing
//Does:    Finds min x coordinate
//Returns: Min x coordinate's pointer
template <class Data>
Data *KDTree<Data>::getMinX(){
	KDNode *temp = recGetMinX(root, 'x');
	if(temp == nullptr){
		return nullptr;
	}
	else{
		return temp->netLocation;
	}
}

//Takes:   Nothing
//Does:    Finds min y coordinate
//Returns: Min y coordinate's pointer
template <class Data>
Data *KDTree<Data>::getMinY(){
	KDNode *temp = recGetMinY(root, 'x');
	if(temp == nullptr){
		return nullptr;
	}
	else{
		return temp->netLocation;
	}
}

		
//-----------------------------Helper Functions---------------------------------
//Takes:   xy coordinates and pointer to Data
//Does:    Creates a node
//Returns: Returns the node with values
template <class Data>
typename KDTree<Data>::KDNode KDTree<Data>::newNode(int x, int y, 
															 Data *netLocation){
	KDNode temp;
	temp.xCoord = x;
	temp.yCoord = y;
	temp.netLocation = netLocation;
	temp.left = nullptr;
	temp.right = nullptr;

	return temp;
}

//Takes:   root to start from
//Does:    Clears the tree down the root
//Returns: nullptr
template <class Data>
typename KDTree<Data>::KDNode *KDTree<Data>::recClear(KDNode *root){
	if (root == nullptr){
		return nullptr;
	}

	root->left = recClear(root->left);
	root->right = recClear(root->right);

	delete root;
	return nullptr;
}

//Takes:   Node to insert, dimension to consider and the root
//Does:    Inserts Node
//Returns: Pointer to updated tree
template <class Data>
typename KDTree<Data>::KDNode *KDTree<Data>::recInsert(KDNode *value, 
												  char dimension, KDNode *root){
	//Empty Case
	if(root == nullptr){
		return value;
	}

	//Repetition causes update
	if(root->xCoord == value->xCoord and root->yCoord == value->yCoord){
		root->netLocation = value->netLocation;
		delete value;
		return root;
	}


	//Traversing
	if(dimension == 'x'){
		if(value->xCoord >= root->xCoord){
			//Going Right
			root->right = recInsert(value, 'y', root->right);
		}
		else{
			//Going Left
			root->left = recInsert(value, 'y', root->left);
		}
	}
	else{
		if(value->yCoord >= root->yCoord){
			//Going Right
			root->right = recInsert(value, 'x', root->right);
		}
		else{
			//Going Left
			root->left = recInsert(value, 'x', root->left);
		}
	}

	return root;
}

//Takes:   xy coordinates, dimension to consider, root pointer
//Does:    Finds the requested node
//Returns: The node if found, nullptr otherwise
template <class Data>
typename KDTree<Data>::KDNode *KDTree<Data>::recFind(int x, int y, 
												  char dimension, KDNode *root){
	//Empty Case
	if(root == nullptr){
		return nullptr;
	}

	//If Found
	if(root->xCoord == x and root->yCoord == y){
		return root;
	}

	//Traversing
	if(dimension == 'x'){
		if(x >= root->xCoord){
			//Going Right
			return recFind(x, y, 'y', root->right);
		}
		else{
			//Going Left
			return recFind(x, y, 'y', root->left);
		}
	}
	else{
		if(y >= root->yCoord){
			//Going Right
			return recFind(x, y, 'x', root->right);
		}
		else{
			//Going Left
			return recFind(x, y, 'x', root->left);
		}
	}

	return nullptr;
}

//Takes:   root to tree
//Does:    Finds the size of the tree
//Returns: Size of the tree
template <class Data>
int KDTree<Data>::recSize(KDNode *root){
	//Empty Case
	if(root == nullptr){
		return 0;
	}

	return 1 + recSize(root->left) + recSize(root->right);
}

//Takes:   xy coordinates, dimension to consider, root of the tree, and bool ptr
//Does:    Deletes if found and updates the bool ptr
//Returns: Updated tree
template <class Data>
typename KDTree<Data>::KDNode *KDTree<Data>::recDelete(int x, int y, 
									char dimension, KDNode *root, bool &isDone){
	//Empty Case
	if(root == nullptr){
		return nullptr;
	}

	//Finding other dimensions
	char otherDim;
	if(dimension == 'x'){
		otherDim = 'y';
	}
	else{
		otherDim = 'x';
	}

	//If found, then deleting
	if(root->xCoord == x and root->yCoord == y){	
		isDone = true;	
		if(root->right != nullptr){
			//We need to find min in the subtree and replace it in root
			//and delete the original
			KDNode *min;
			if(dimension == 'x'){
				min = recGetMinX(root->right, 'y');
			}
			else{
				min = recGetMinY(root->right, 'x');
			}		
			root->xCoord = min->xCoord;
			root->yCoord = min->yCoord;
			root->netLocation = min->netLocation;
			root->right = recDelete(min->xCoord, min->yCoord, otherDim, 
														   root->right, isDone);
			return root;
		}
		else if (root->left != nullptr){
			//We need to find min in the subtree and replace it but we also
			//need to swap left and right pointers of root
			KDNode *min;
			if(dimension == 'x'){
				min = recGetMinX(root->left, 'y');
			}
			else{
				min = recGetMinY(root->left, 'x');
			}	
			root->xCoord = min->xCoord;
			root->yCoord = min->yCoord;
			root->netLocation = min->netLocation;
			root->right = recDelete(min->xCoord, min->yCoord, otherDim, 
															root->left, isDone);
			root->left = nullptr;
			return root;
		}
		else{
			//We can just delete it
			delete root;
			return nullptr;
		}
	}


	//Traversing
	if(dimension == 'x'){
		if(x >= root->xCoord){
			//Going Right
			root->right = recDelete(x, y, 'y', root->right, isDone);
		}
		else{
			//Going Left
			root->left = recDelete(x, y, 'y', root->left, isDone);
		}
	}
	else{
		if(y >= root->yCoord){
			//Going Right
			root->right =  recDelete(x, y, 'x', root->right, isDone);
		}
		else{
			//Going Left
			root->left = recDelete(x, y, 'x', root->left, isDone);
		}
	}

	return root;
}

//Takes:   root to tree
//Does:    Prints the tree
//Returns: Nothing
template <class Data>
void KDTree<Data>::recPrint(KDNode *root){
	//Empty Case
	cout << "[";
	if(root == nullptr){
		cout << "]";
		return;
	}

	//Processing Left
	recPrint(root->left);

	//Processing Current
	cout << " (" << root->xCoord << ", " << root->yCoord << ") ";

	//Processing Right
	recPrint(root->right);

	cout << "]";
}

//Takes:   root and dimension to consider
//Does:    Finds the node with max x coordinate
//Returns: Node with max x coordinate
template <class Data>
typename KDTree<Data>::KDNode *KDTree<Data>::recGetMaxX(KDNode *root, 
																char dimension){
	//Empty Case
	if(root == nullptr){
		return nullptr;
	}

	if(dimension == 'x'){
		//We can use this dimension to find direction
		if(root->right == nullptr){
			return root;
		}
		else{
			return recGetMaxX(root->right, 'y');
		}
	}
	else{
		//We can't use this dimension, max can be anywhere
		KDNode *max = root;
		if(root->right != nullptr){
			KDNode *rMax = recGetMaxX(root->right, 'x');
			if(rMax != nullptr){
				if(max->xCoord < rMax->xCoord){
					max = rMax;
				}
			}
		}
		if(root->left != nullptr){
			KDNode *lMax = recGetMaxX(root->left, 'x');
			if(lMax != nullptr){
				if(max->xCoord < lMax->xCoord){
					max = lMax;
				}
			}
		}
		return max;
	}

}

//Takes:   root and dimension to consider
//Does:    Finds the node with max y coordinate
//Returns: Node with max y coordinate
template <class Data>
typename KDTree<Data>::KDNode *KDTree<Data>::recGetMaxY(KDNode *root, 
																char dimension){
	//Empty Case
	if(root == nullptr){
		return nullptr;
	}

	if(dimension == 'y'){
		//We can use this dimension for direction
		if(root->right == nullptr){
			return root;
		}
		else{
			return recGetMaxY(root->right, 'x');
		}
	}
	else{
		//We can't use this dimension, so max can be anywhere
		KDNode *max = root;
		if(root->right != nullptr){
			KDNode *rMax = recGetMaxY(root->right, 'y');
			if(rMax != nullptr){
				if(max->yCoord < rMax->yCoord){
					max = rMax;
				}
			}
		}
		if(root->left != nullptr){
			KDNode *lMax = recGetMaxY(root->left, 'y');
			if(lMax != nullptr){
				if(max->yCoord < lMax->yCoord){
					max = lMax;
				}
			}
		}
		return max;
	}
}

//Takes:   root and dimension to consider
//Does:    Finds the node with min x coordinate
//Returns: Node with min x coordinate
template <class Data>
typename KDTree<Data>::KDNode *KDTree<Data>::recGetMinX(KDNode *root, 
																char dimension){
	//Empty Case
	if(root == nullptr){
		return nullptr;
	}

	if(dimension == 'x'){
		//We can use this dimension for direction
		if(root->left == nullptr){
			return root;
		}
		else{
			return recGetMinX(root->left, 'y');
		}
	}
	else{
		//We can't use this dimension, max can be anywhere
		KDNode *min = root;
		if(root->right != nullptr){
			KDNode *rMin = recGetMinX(root->right, 'y');
			if(rMin != nullptr){
				if(min->xCoord > rMin->xCoord){
					min = rMin;
				}
			}
		}
		if(root->left != nullptr){
			KDNode *lMin= recGetMinX(root->left, 'y');
			if(lMin != nullptr){
				if(min->xCoord > lMin->xCoord){
					min = lMin;
				}
			}
		}
		return min;
	}
}

//Takes:   root and dimension to consider
//Does:    Finds the node with min y coordinate
//Returns: Node with min y coordinate
template <class Data>
typename KDTree<Data>::KDNode *KDTree<Data>::recGetMinY(KDNode *root, 
																char dimension){
	//Empty Case
	if(root == nullptr){
		return nullptr;
	}

	if(dimension == 'y'){
		//We can use this dimension for direction
		if(root->left == nullptr){
			return root;
		}
		else{
			return recGetMinY(root->left, 'x');
		}
	}
	else{
		//We can't use this dimension for direction
		KDNode *min = root;
		if(root->right != nullptr){
			KDNode *rMin = recGetMinY(root->right, 'y');
			if(rMin != nullptr){
				if(min->yCoord > rMin->yCoord){
					min = rMin;
				}
			}
		}
		if(root->left != nullptr){
			KDNode *lMin= recGetMinY(root->left, 'y');
			if(lMin != nullptr){
				if(min->yCoord > lMin->yCoord){
					min = lMin;
				}
			}
		}
		return min;
	}
}

//Takes:   Nothing
//Does:    Throws exception if tree is empty
//Returns: Nothing
template <class Data>
void KDTree<Data>::emptyThrower(){
	if(root == nullptr){
		throw runtime_error("Tree is Empty!");
	}
}