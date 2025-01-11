#pragma once

//#include <string>

template <class T>
class cSmartArray_3
{
public:
	cSmartArray_3()
	{
		// Set starting capacity
		this->m_capacity = cSmartArray_3::STARTING_CAPACITY;

		// Allocate the array
		this->m_pTheData = new T[this->m_capacity];
	}

	~cSmartArray_3()
	{
	}

	unsigned int getSize(void)
	{
		return this->m_currentEndIndex;
	}

	unsigned int getCapacity(void)
	{
		return this->m_capacity;
	}

	// 
	void appendToEnd(T theValue)		// "push_back"
	{
		// Is there enough room for this value?
		// (i.e. what's the capacity)

		if (this->m_currentEndIndex >= this->m_capacity)
		{
			// Resize
			unsigned int newCapacity = this->m_capacity * 2;	// Double it

			this->m_resizeArray(newCapacity);

		}
		// At this point, the array IS large enough

		this->m_pTheData[this->m_currentEndIndex] = theValue;

		this->m_currentEndIndex++;

		return;
	}

	T getAtIndex(unsigned int index)	// cout << myVector[17]
	{
		// TODO: What to do if the index is out of range?
		// (maybe nothing?)

		return this->m_pTheData[index];
	}

//	bool getAtIndex(unsigned index, std::string &theValue);

	void overwriteAtIndex(unsigned int index, T theValue)	// myVector[17] = "Ted"
	{
		this->m_pTheData[this->m_currentEndIndex] = theValue;
		return;
	}

private:
	unsigned int m_currentEndIndex = 0;

	const unsigned int STARTING_CAPACITY = 10;
	unsigned int m_capacity = STARTING_CAPACITY;

//	std::string m_theData[9'000];
	T* m_pTheData = nullptr;	// = new std::string[STARTING_CAPACITY];

	void m_resizeArray(unsigned int newCapacity)
	{
		// 1. Allocate a new array of the needed size;
		// 2. Copy the data from the old array to the new array
		// 3. Delete the old data (array) (or I get a memory leak)
		// 4. Point the array to the new location

		// 1. Allocate a new array of the needed size;
		T* pNEWData = new T[newCapacity];

		// 2. Copy the data from the old array to the new array
		for (unsigned int index = 0; index != this->m_capacity; index++)
		{
			pNEWData[index] = this->m_pTheData[index];
		}

		// 3. Delete the old data (array) (or I get a memory leak)
		delete[] this->m_pTheData;

		// 4. Point the array to the new location
		this->m_pTheData = pNEWData;

		// Update this new capacity
		this->m_capacity = newCapacity;

		return;
	}

};