// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by:	Denny Hung Liang

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"


template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:

	using BinaryTree<ItemType>::rootPtr;

	//TESTING
	int(*compareID) (void* argu1, void* argu2, void *argu3);


	BinaryNode<ItemType>* _insert2(BinaryNode<ItemType> *nodePtr, BinaryNode<ItemType>* newNode);
	////////////

	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType> *nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType> * _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

	///////////
	BinaryNode<ItemType>* findSecNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
	///////////

	//search for leftmost node
	BinaryNode<ItemType>* findSmallest(BinaryNode<ItemType>* treePtr) const;
	//search for rightmost node
	BinaryNode<ItemType>* findLargest(BinaryNode<ItemType>* treePtr) const;

	// print within range
	void _printRange(void visit(ItemType&), BinaryNode<ItemType>* nodePtr, ItemType &lowLimit, ItemType &highLimit, bool &isSuccess) const;

	BinaryNode<ItemType>  *_remove2(BinaryNode<ItemType> *nodePtr, const ItemType target, bool & success);

public:
	//TEST
	BinarySearchTree(int(*cmp) (void* argu1, void* argu2, void* argu3)){ compareID = cmp; }
	//////////
	bool insert2(const ItemType *newEntry);

	////////
	// bool getSecondaryEntries(const ItemType & target, BinaryNode<ItemType>* secKey) const;
	///////////

	// insert a node at the correct location
	bool insert(const ItemType *newEntry);
	// remove a node if found
	bool remove(const ItemType *anEntry);

	// find a target node
	//bool getEntry(const ItemType &target, ItemType &returnedItem) const;
	// print within range

	//bool printRange(void visit(ItemType&), ItemType & lowLimit, ItemType & highLimit) const;
	// get largest item

	bool getLargest(ItemType &returnedItem) const;
	// get smallest item
	bool getSmallest(ItemType &returnedItem) const;

	//
	bool remove2(const ItemType *anEntry);

};


///////////////////////// public function definitions ///////////////////////////
//*************************************************************************
// Public Insert
//*************************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::insert2(const ItemType *newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(*newEntry);
	rootPtr = _insert2(rootPtr, newNodePtr);
	//count++;
	return true;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType *newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(*newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	//count++;
	return true;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType *target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, *target, isSuccessful);
	/*
	if (isSuccessful)
	count--;
	*/
	return isSuccessful;

}

//*************************************************************************

//*************************************************************************
//returns true if entry is found; returns item by reference.
//returns false if not found
/*
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
BinaryNode<ItemType>* isFound = findNode(rootPtr, anEntry);
if (isFound){
returnedItem = isFound->getItem();
return true;
}
return false;
}
*/
//*************************************************************************

//*************************************************************************
/*
template<class ItemType>
bool BinarySearchTree<ItemType>::getSecondaryEntries(const ItemType& anEntry, BinaryNode<ItemType>* secKey) const
{
BinaryNode<ItemType>* isFound = findSecNode(rootPtr, anEntry);
if (isFound){
//returnedItem = isFound->getItem();
secKey = isFound;
return true;
}
return false;
}
*/
//*************************************************************************

//*************************************************************************
/*
template<class ItemType>
//bool BinarySearchTree<ItemType>::printRange(void visit(ItemType&), ItemType & lowLimit, ItemType & highLimit) const
{
bool isSuccessful = false;
_printRange(visit, rootPtr, lowLimit, highLimit, isSuccessful);
return isSuccessful;
}
*/
//*************************************************************************

//*************************************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::getLargest(ItemType & returnedItem) const
{
	BinaryNode<ItemType>* largest = findLargest(rootPtr);
	if (largest){
		returnedItem = largest->getItem();
		return true;
	}
	return false;
}

//*************************************************************************

//*************************************************************************

// get smallest item
template<class ItemType>
bool BinarySearchTree<ItemType>::getSmallest(ItemType & returnedItem) const
{
	BinaryNode<ItemType>* smallest = findSmallest(rootPtr);
	if (smallest){
		returnedItem = smallest->getItem();
		return true;
	}
	return false;
}

//////////////////////////// private functions ////////////////////////////////////////////
//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	else if (nodePtr->getItem() > newNodePtr->getItem())
	{
		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
	}
	else
	{
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
	}
	return nodePtr;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert2(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	else if (!(nodePtr->getItem() <= newNodePtr->getItem()))
	{
		nodePtr->setLeftPtr(_insert2(nodePtr->getLeftPtr(), newNodePtr));
	}
	else
	{
		nodePtr->setRightPtr(_insert2(nodePtr->getRightPtr(), newNodePtr));
	}
	return nodePtr;
}
/////////////////////
//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	const ItemType target,
	bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)
	{
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	}
	else if (nodePtr->getItem() < target)
	{
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	}
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;

}
//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::_remove2(BinaryNode<ItemType> *nodePtr,
	const ItemType target,
	bool & success)
{
	// ItemType item = nodePtr->getItem();
	// cout << item.getID();

	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}

	if (!(nodePtr->getItem() <= target)) //compares names
	{
		//cout << "1";
		nodePtr->setLeftPtr(_remove2(nodePtr->getLeftPtr(), target, success));

	}
	else if (!(nodePtr->getItem() >= target))
	{
		//cout << "2";
		nodePtr->setRightPtr(_remove2(nodePtr->getRightPtr(), target, success));
	}
	else
	{
		// cout << "3";

		while (!(nodePtr->getItem() == target))
		{
			if (!(nodePtr->getItem() != target))
				nodePtr = nodePtr->getRightPtr();
			else
				nodePtr = nodePtr->getLeftPtr();
		}

		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::remove2(const ItemType *target)
{
	bool isSuccessful = false;
	rootPtr = _remove2(rootPtr, *target, isSuccessful);
	/*
	if (isSuccessful)
	cout << "SUC";
	else
	cout << "FAIL";
	//count--;
	*/

	return isSuccessful;

}
//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target) const
{
	if (nodePtr == 0)
		return 0;
	else if (nodePtr->getItem() == target)
		return nodePtr;
	else if (nodePtr->getItem() > target)
		return findNode(nodePtr->getLeftPtr(), target);
	else
		return findNode(nodePtr->getRightPtr(), target);
}
//*************************************************************************

//*************************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSecNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target) const
{
	if (nodePtr == 0)
		return 0;
	else if (nodePtr->getItem() - target)
		return nodePtr;
	else if (nodePtr->getItem() + target)
		return findSecNode(nodePtr->getLeftPtr(), target);
	else
		return findSecNode(nodePtr->getRightPtr(), target);
}


//*************************************************************************

//*************************************************************************

template<class ItemType>
void BinarySearchTree<ItemType>::_printRange(void visit(ItemType &), BinaryNode<ItemType>* nodePtr,
	ItemType &lowLimit, ItemType &highLimit, bool &isSuccess) const
{
	if (nodePtr == 0)
		return;
	if (nodePtr->getItem() > lowLimit)
		_printRange(visit, nodePtr->getLeftPtr(), lowLimit, highLimit, isSuccess);

	if (nodePtr->getItem() >= lowLimit && nodePtr->getItem() <= highLimit){
		visit(nodePtr->getItem());
		isSuccess = true;
	}
	if (nodePtr->getItem() < highLimit)
		_printRange(visit, nodePtr->getRightPtr(), lowLimit, highLimit, isSuccess);
}

//*************************************************************************

//*************************************************************************

template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLargest(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr->getRightPtr() == 0)
		return nodePtr;
	return findLargest(nodePtr->getRightPtr());
}

//*************************************************************************

//*************************************************************************

template <class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSmallest(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr->getLeftPtr() == 0)
		return nodePtr;
	return findSmallest(nodePtr->getLeftPtr());
}

#endif