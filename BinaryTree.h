// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Denny Hung Liang

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "CellPhone.h"
#include "Queue.h"
#include "Stack.h"
#include <iomanip>

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree);
	virtual ~BinaryTree() { destroyTree(rootPtr); }
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const	{ return count == 0; }
	int size() const	    { return count; }
	void clear()			{ destroyTree(rootPtr); rootPtr = 0; count = 0; }

	void preOrder(void visit(ItemType &)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType &)) const  { _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType &)) const{ _postorder(visit, rootPtr); }
	void iter_preOrder(void visit(ItemType &)) const { _iter_preorder(visit, rootPtr); }
	void iter_inOrder(void visit(ItemType &)) const  { _iter_inorder(visit, rootPtr); }
	void iter_postOrder(void visit(ItemType &)) const{ _iter_postorder(visit, rootPtr); }
	void printTree(void visit(ItemType &)) const{ _printTree(visit, rootPtr); }

	void breadthFirst(void visit(ItemType &)) const{ _breadthFirst(visit, rootPtr); }

	void printKey(void visit(ItemType &), ItemType & key) const{ _printKey(visit, rootPtr, key); }

	// abstract functions to be implemented by derived class

	virtual bool insert2(const ItemType *newData) = 0;
	virtual bool insert(const ItemType *newData) = 0;
	virtual bool remove(const ItemType *data) = 0;

	//virtual bool getEntry(const ItemType &anEntry, ItemType &returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iter_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iter_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iter_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _breadthFirst(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _printTree(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int indent = 0, int lineNum = 1) const;
	void _printKey(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, ItemType& key) const;
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
template<class ItemType>
BinaryTree<ItemType>::BinaryTree(const BinaryTree<ItemType> & tree)
{
	rootPtr = copyTree(tree.rootPtr);
	count = tree.count;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;

	if (nodePtr)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem(), NULL, NULL);
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	}

	return newNodePtr;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}

//*************************************************************************

//*************************************************************************

//root-left-right
template<class ItemType>
void BinaryTree<ItemType>::_iter_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Stack<BinaryNode<ItemType>*> *stack = new Stack<BinaryNode<ItemType>*>();
	BinaryNode<ItemType>* currentPtr = nodePtr;
	bool done = false;

	if (currentPtr != 0)
		stack->push(currentPtr);

	while (!done)
	{
		if (!stack->isEmpty())
		{
			stack->pop(currentPtr);
			visit(currentPtr->getItem());
			if (currentPtr->getRightPtr() != 0)
				stack->push(currentPtr->getRightPtr());
			if (currentPtr->getLeftPtr() != 0)
				stack->push(currentPtr->getLeftPtr());
		}
		else
			done = true;
	}
	delete stack;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
void BinaryTree<ItemType>::_iter_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Stack<BinaryNode<ItemType>*> *stack = new Stack<BinaryNode<ItemType>*>();
	BinaryNode<ItemType>* currentPtr = nodePtr;
	bool done = false;

	while (!done)
	{
		if (currentPtr != 0)
		{
			stack->push(currentPtr);
			currentPtr = currentPtr->getLeftPtr();
		}
		else
		{
			if (!stack->isEmpty())
			{
				stack->pop(currentPtr);
				visit(currentPtr->getItem());
				currentPtr = currentPtr->getRightPtr();
			}
			else
				done = true;
		}
	}
	delete stack;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
void BinaryTree<ItemType>::_iter_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Stack<BinaryNode<ItemType>*> *stack = new Stack<BinaryNode<ItemType>*>();
	BinaryNode<ItemType>* currentPtr = nodePtr;
	ItemType tempItem;
	BinaryNode<ItemType>* tempNode = new BinaryNode<ItemType>(tempItem);

	do
	{

		while (currentPtr != 0)
		{
			if (currentPtr->getRightPtr() != 0)
				stack->push(currentPtr->getRightPtr());
			stack->push(currentPtr);
			currentPtr = currentPtr->getLeftPtr();
		}
		stack->pop(currentPtr);
		stack->getTop(tempNode);
		if (currentPtr->getRightPtr() != 0 && tempNode->getItem() == currentPtr->getRightPtr()->getItem())
		{
			stack->pop(tempNode);
			stack->push(currentPtr);
			currentPtr = currentPtr->getRightPtr();
		}
		else
		{
			visit(currentPtr->getItem());
			currentPtr = 0;
		}

	} while (!stack->isEmpty());

	delete stack;
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
void BinaryTree<ItemType>::_breadthFirst(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Queue<BinaryNode<ItemType>*> *breadthFirstQueue = new Queue<BinaryNode<ItemType>*>();
	ItemType anItem;
	BinaryNode<ItemType> *tempNode = new BinaryNode<ItemType>(anItem);

	if (nodePtr == 0)
		return;

	breadthFirstQueue->enqueue(nodePtr);
	while (!breadthFirstQueue->isEmpty())
	{
		breadthFirstQueue->dequeue(tempNode);
		visit(tempNode->getItem());
		if (tempNode->getLeftPtr() != 0)
			breadthFirstQueue->enqueue(tempNode->getLeftPtr());
		if (tempNode->getRightPtr() != 0)
			breadthFirstQueue->enqueue(tempNode->getRightPtr());
	}
	delete breadthFirstQueue;
}

//*************************************************************************

//*************************************************************************
/*
template<class ItemType>
void BinaryTree<ItemType>::_printIndented(void visit(ItemType &, int count), BinaryNode<ItemType>* nodePtr, int height) const
{
if (nodePtr != 0){
if (nodePtr->getRightPtr() != 0)
_printIndented(visit, nodePtr->getRightPtr(), height + 1);
visit(nodePtr->getItem(), height);
if (nodePtr->getLeftPtr() != 0)
_printIndented(visit, nodePtr->getLeftPtr(), height + 1);
}
}
*/
/*
template<class ItemType>
void BinaryTree<ItemType>::_printIndented(BinaryNode<ItemType>* nodePtr,int indent, int LineNum) const
{
if (nodePtr != 0)
{
_printIndented( nodePtr->getRightPtr(), indent + 10, LineNum+1);
cout << setw(indent) << " " << LineNum << "." ;
ItemType temp = nodePtr->getItem();
cout << temp.getID() << " " << temp.getName();
cout << endl;
cout << endl;
_printIndented(nodePtr->getLeftPtr(), indent + 10, LineNum+1);
}
}
*/
template <class ItemType>
void BinaryTree<ItemType>::_printTree(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int indent, int lineNum) const
{
	if (nodePtr != 0)
	{
		_printTree(visit, nodePtr->getRightPtr(), indent + 7, lineNum + 1);
		ItemType item = nodePtr->getItem();
		cout << setw(indent) << " " << lineNum << ".";
		visit(item);
		cout << endl;
		_printTree(visit, nodePtr->getLeftPtr(), indent + 7, lineNum + 1);
	}
}
//*************************************************************************

//*************************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_printKey(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, ItemType & key) const
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(key);

	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();

		if (!(nodePtr->getItem() != newNodePtr->getItem()))
			visit(item);

		_printKey(visit, nodePtr->getRightPtr(), key);
		_printKey(visit, nodePtr->getLeftPtr(), key);
	}
}

//*************************************************************************

//*************************************************************************

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	destroyTree(rootPtr);
	rootPtr = copyTree(sourceTree.rootPtr);
	count = sourceTree.count;
	return *(this);
}


#endif