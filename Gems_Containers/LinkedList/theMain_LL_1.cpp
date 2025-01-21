//#include <list>
#include "cLinkedList.h"
#include <string>
#include <fstream>
#include <iostream>

//void RemoveFirstInstanceOfName(std::string theName, std::list< std::string >& listLastNames)
//{
//	for (std::list< std::string >::iterator itName = listLastNames.begin();
//		itName != listLastNames.end(); itName++)
//	{
//		if (*itName == theName)
//		{
//			// Remove it
//			listLastNames.erase(itName);
//		}
//	}
//
//}


int main()
{
	std::fstream lastNameFile("US_LastNames.txt");

	// Container (smart array)
//	std::list< std::string > listLastNames;
	cLinkedList listLastNames;


	std::string nextName;
	while (lastNameFile >> nextName)	//   
	{
		// Add it
		listLastNames.insertAtCurrent(nextName);

		listLastNames.moveToEnd();
		//if (rand() % 9 > 3)
		//{
		//	listLastNames.insert(listLastNames.end(), "DAVIS");
		//}

		float discardThis;
		lastNameFile >> discardThis >> discardThis >> discardThis; // 1.006  1.006      1
	}

	listLastNames.moveToStart();

	//for (std::list< std::string >::iterator itName = listLastNames.begin();
	//	itName != listLastNames.end(); itName++)
	//{
	//	std::cout << *itName << std::endl;
	//}
	do
	{
		std::cout << listLastNames.getAtCurrent() << std::endl;

	} while (listLastNames.moveNext());

	std::cout << "*****************************" << std::endl;

	//	RemoveFirstInstanceOfName("DAVIS", listLastNames);

	//	std::remove(listLastNames.begin(), listLastNames.end(), "DAVIS");

	//	listLastNames.sort();		// Less Than  operator <

	//listLastNames.sort(isALessThanB);

	//for (std::list< std::string >::iterator itName = listLastNames.begin();
	//	itName != listLastNames.end(); itName++)
	//{
	//	std::cout << *itName << std::endl;
	//}

	//	std::sort(listLastNames.begin(), listLastNames.end());




	return 0;
}
