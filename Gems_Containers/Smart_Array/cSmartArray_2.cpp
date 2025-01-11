#include "cSmartArray_2.h"

cSmartArray_2::cSmartArray_2()
{
	// Set starting capacity
	this->m_capacity = cSmartArray_2::STARTING_CAPACITY;

	// Allocate the array
	this->m_pTheData = new std::string[this->m_capacity];
}

cSmartArray_2::~cSmartArray_2()
{
}

unsigned int cSmartArray_2::getSize(void)
{
	return this->m_currentEndIndex;
}

unsigned int cSmartArray_2::getCapacity(void)
{
	return this->m_capacity;
}

// "push_back" 
void cSmartArray_2::appendToEnd(std::string theValue)
{
	// Is there enough room for this value?
	// (i.e. what's the capacity)

	if (this->m_currentEndIndex >= this->m_capacity)
	{
		// Resize
		unsigned int newCapacity = this->m_capacity * 2;

		this->m_resizeArray(newCapacity);

	}
	// At this point, the array IS large enough

	this->m_pTheData[this->m_currentEndIndex] = theValue;

	this->m_currentEndIndex++;

	return;
}

// cout << myVector[17]
std::string cSmartArray_2::getAtIndex(unsigned int index)
{
	// TODO: What to do if the index is out of range?
	// (maybe nothing?)

	return this->m_pTheData[index];
}

// myVector[17] = "Ted"
void cSmartArray_2::overwriteAtIndex(unsigned int index, std::string theValue)
{
	this->m_pTheData[this->m_currentEndIndex] = theValue;
	return;
}


void cSmartArray_2::m_resizeArray(unsigned int newCapacity)
{
	// 1. Allocate a new array of the needed size;
	// 2. Copy the data from the old array to the new array
	// 3. Delete the old data (array) (or I get a memory leak)
	// 4. Point the array to the new location

	// 1. Allocate a new array of the needed size;
	std::string* pNEWData = new std::string[newCapacity];

	// 2. Copy the data from the old array to the new array
	for (unsigned int index = 0; index != this->m_capacity; index++)
	{
		pNEWData[index] = this->m_pTheData[index];
	}

	// 3. Delete the old data (array) (or I get a memory leak)
	delete [] this->m_pTheData;

	// 4. Point the array to the new location
	this->m_pTheData = pNEWData;

	// Update this new capacity
	this->m_capacity = newCapacity;

	return;
}