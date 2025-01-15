#pragma once

#include <string>

class cSmartArray
{
public:
	cSmartArray();
	~cSmartArray();

	unsigned int getSize(void);
	unsigned int getCapacity(void);

	// 
	void appendToEnd(std::string theValue);		// "push_back"
	std::string getAtIndex(unsigned int index);	// cout << myVector[17]
//	bool getAtIndex(unsigned index, std::string &theValue);

	void overwriteAtIndex(unsigned int index, std::string theValue);	// myVector[17] = "Ted"

private:

	std::string m_theData[9'000];		// STACK
	unsigned int m_currentEndIndex = 0;
};