#pragma once

#include <string>

class cLinkedList
{
public:
	cLinkedList();
	~cLinkedList();

	void insertAtStart(std::string value);
	void insertAtEnd(std::string value);

	void insertAtCurrent(std::string value);
	std::string getAtCurrent(void);
	void deleteAtCurrent(void);

	void moveToStart(void);	// HEAD
	void moveToEnd(void);	// TAIL

	void moveNext(void);
	void movePrior(void);

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

	sNode* pHeadNode = NULL;
	sNode* pCurrentNode = NULL; // *****

	// TODO:
	unsigned int m_numberOfNodes = 0;
};