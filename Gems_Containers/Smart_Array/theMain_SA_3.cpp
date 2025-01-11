#include "cSmartArray_3.h"
#include <string>
#include <iostream>
#include <fstream>

int main()
{

	std::fstream lastNameFile("USCen/US_LastNames.txt");

	// Container (smart array)
//	std::vector< std::string > vecLastNames;
	cSmartArray_3<std::string> vecLastNames;

	std::string nextName;
	while (lastNameFile >> nextName)	// //SMITH   
	{
		// Add it
		//vecLastNames.push_back(nextName);
		vecLastNames.appendToEnd(nextName);

		float discardThis;
		lastNameFile >> discardThis >> discardThis >> discardThis; // 1.006  1.006      1
	}

	unsigned int count = 0;
	while (count < 30'000'000)
	{
		vecLastNames.appendToEnd("Hey!");
		count++;
	}

	//	for (unsigned int index = 0; index != vecLastNames.size(); index++)
	for (unsigned int index = 0;
		index < vecLastNames.getSize();
		index++)
	{
		//		std::cout << vecLastNames[index] << std::endl;
		std::cout << vecLastNames.getAtIndex(index) << std::endl;
	}



	return 0;
}