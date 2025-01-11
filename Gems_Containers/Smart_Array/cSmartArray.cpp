#include "cSmartArray.h"

cSmartArray::cSmartArray()
{
}

cSmartArray::~cSmartArray()
{
}

unsigned int cSmartArray::getSize(void)
{
	return this->m_currentEndIndex;
}

unsigned int cSmartArray::getCapacity(void)
{
	// HACK:
	return 9'000;
}

// "push_back" 
void cSmartArray::appendToEnd(std::string theValue)
{

	this->m_theData[this->m_currentEndIndex] = theValue;

	this->m_currentEndIndex++;

	return;
}

// cout << myVector[17]
std::string cSmartArray::getAtIndex(unsigned int index)
{
	if (index >= this->m_currentEndIndex)
	{
		return "BAD PROGRAMMER!";	/// HUH????
	}
	return this->m_theData[index];
}

// myVector[17] = "Ted"
void cSmartArray::overwriteAtIndex(unsigned int index, std::string theValue)
{
	this->m_theData[this->m_currentEndIndex] = theValue;
	return;
}
