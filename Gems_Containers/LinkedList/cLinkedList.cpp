#include "cLinkedList.h"

cLinkedList::cLinkedList()
{
	this->pCurrentNode = this->pHeadNode;

}

cLinkedList::~cLinkedList()
{
}


void cLinkedList::insertAtCurrent(std::string value)
{
	sNode* pNewNode = new sNode();
	pNewNode->theData = value;

	// Place this node at the current node
	
	// Is there a node before the current node?
	if (this->pCurrentNode->pPrior != NULL)
	{
		// YES there is a prior node
		// update the pointers for this node

		// Prior node now points to THIS new node
		this->pCurrentNode->pPrior->pNext = pNewNode;

		// THIS node points to prior
		pNewNode->pPrior = this->pCurrentNode->pPrior;
	}


	// Is there a node AFTER the current node?
	if (this->pCurrentNode->pNext != NULL)
	{
		// Yes there is a next node
		this->pCurrentNode->pNext->pPrior = pNewNode;
		//
		pNewNode->pNext = this->pCurrentNode->pNext;
	}

	this->pCurrentNode = pNewNode;

	return;
}

std::string cLinkedList::getAtCurrent(void)
{
	return this->pCurrentNode->theData;
}


void cLinkedList::moveNext(void)
{
	// TODO: Check if this is already at the end...
	// ...i.e. is the next node a NULL
	this->pCurrentNode = this->pCurrentNode->pNext;
	return;
}

void cLinkedList::movePrior(void)
{
	// TODO: Check if this is at the start
	// ...i.e. the prior node is already NULL
	this->pCurrentNode = this->pCurrentNode->pPrior;
	return;
}
