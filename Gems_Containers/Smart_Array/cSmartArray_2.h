#pragma once

#include <string>

class cSmartArray_2
{
public:
	cSmartArray_2();
	~cSmartArray_2();

	unsigned int getSize(void);
	unsigned int getCapacity(void);

	// 
	void appendToEnd(std::string theValue);		// "push_back"
	std::string getAtIndex(unsigned int index);	// cout << myVector[17]
//	bool getAtIndex(unsigned index, std::string &theValue);

	void overwriteAtIndex(unsigned int index, std::string theValue);	// myVector[17] = "Ted"

private:
	unsigned int m_currentEndIndex = 0;

	const unsigned int STARTING_CAPACITY = 10;
	unsigned int m_capacity = STARTING_CAPACITY;

//	std::string m_theData[9'000];
	std::string* m_pTheData = NULL;	// = new std::string[STARTING_CAPACITY];

	void m_resizeArray(unsigned int newCapacity);
};