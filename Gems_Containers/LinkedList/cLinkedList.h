#pragma once

#include <string>

class cLinkedList
{
public:
	cLinkedList();
	~cLinkedList();

	// This inserts BEFORE the current node
	void insertAtCurrent(std::string value);
	std::string getAtCurrent(void);
	bool deleteAtCurrent(void);

	void insertAtStart(std::string value);
	void insertAtEnd(std::string value);

	// What would this be? 
	// Is a bubble sort OK? 
	// Is it worth doing something fancy? 
	// How much memory does it take, etc. 
	void SortAscending(void);

	void moveToStart(void);	// HEAD
	void moveToEnd(void);	// TAIL

	bool moveNext(void);
	bool movePrior(void);

private:

	struct sNode
	{
		sNode()
		{
			this->pPrior = NULL;
			this->pNext = NULL;
		}
		std::string theData;
		sNode* pPrior;
		sNode* pNext;
	};

	sNode* pCurrentNode = NULL; // *****

	// Optional things:
	sNode* pHeadNode = NULL;
	sNode* pTailNode = NULL;


	// TODO:
	unsigned int m_numberOfNodes = 0;
};