#include "cLinkedList.h"

cLinkedList::cLinkedList()
{
	this->pCurrentNode = NULL;

	this->pHeadNode = NULL;
	this->pTailNode = NULL;

}

cLinkedList::~cLinkedList()
{
}

bool cLinkedList::deleteAtCurrent(void)
{
	if (this->pCurrentNode == NULL)
	{
		return false;
	}

	sNode* pOldCurrentNode = this->pCurrentNode;


	// Is there a node before this?
	if (pOldCurrentNode->pPrior != NULL)
	{

	}

	// Is there a node after this?
	if (pOldCurrentNode->pNext != NULL)
	{

	}

	// They are both there


	return true;
}


void cLinkedList::insertAtCurrent(std::string value)
{
	sNode* pNewNode = new sNode();
	pNewNode->theData = value;

	// Have we added anything yet? 
	// (i.e. is the current node == NULL?)
	if (this->pCurrentNode == NULL)
	{
		// Yes, so this is the 1st node
		this->pCurrentNode = pNewNode;
		//
		// We could also set these, too:
		this->pHeadNode = this->pCurrentNode;
		this->pTailNode = this->pCurrentNode;
		return;
	}

	// Place this node at the current node
	pNewNode->pNext = this->pCurrentNode;
	pNewNode->pPrior = this->pCurrentNode->pPrior;
	
	this->pCurrentNode->pPrior = pNewNode;

	// Is there a node BEFORE the current node
	if (pNewNode->pPrior != NULL)
	{
		// Yes there is a prior node
		pNewNode->pPrior->pNext = pNewNode;
	}

	this->pCurrentNode = pNewNode;

	// TODO: Update the head and tail nodes, too

	return;
}

std::string cLinkedList::getAtCurrent(void)
{
	return this->pCurrentNode->theData;
}


// 1 GHz --> 1 ns
// 4 GHz --> 0.25 ns

bool cLinkedList::moveNext(void)
{
	// Any nodes?
	if (this->pCurrentNode == NULL)
	{
		// Do nothing. Maybe return error? Throw exception? 
		return false;
	}

	// TODO: Check if this is already at the end...
	if ( this->pCurrentNode->pNext == NULL )
	{
		// Do nothing. Maybe return error? Throw exception? 
		return false;
	}

	// ...i.e. is the next node a NULL
	this->pCurrentNode = this->pCurrentNode->pNext;
	return true;
}

bool cLinkedList::movePrior(void)
{
	// 	// Any nodes?
	if (this->pCurrentNode == NULL)
	{
		// Do nothing. Maybe return error? Throw exception? 
		return false;
	}

	// TODO: Check if this is at the start
	if (this->pCurrentNode->pPrior == NULL)
	{
		// Do nothing. Maybe return error? Throw exception? 
		return false;
	}

	// ...i.e. the prior node is already NULL
	this->pCurrentNode = this->pCurrentNode->pPrior;
	return true;
}

void cLinkedList::moveToStart(void)
{
	while (this->movePrior())
	{
		// Do nothing
	}
	return;
}

void cLinkedList::moveToEnd(void)	// TAIL
{
	while (this->moveNext())
	{
		// do nothing
	}
	return;
}
