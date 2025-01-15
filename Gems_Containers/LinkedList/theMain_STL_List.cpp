//#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

void RemoveFirstInstanceOfName(std::string theName, std::list< std::string >& listLastNames)
{
	for (std::list< std::string >::iterator itName = listLastNames.begin();
		itName != listLastNames.end(); itName++)
	{
		if (*itName == theName)
		{
			// Remove it
			listLastNames.erase(itName);
		}
	}

}

bool isALessThanB(std::string& A, std::string& B)
{
	if (A < B)
	{
		return true;
	}
	return false;
}

int main_STL()
{
	std::fstream lastNameFile("US_LastNames.txt");

	// Container (smart array)
	std::list< std::string > listLastNames;

	std::string nextName;
	while (lastNameFile >> nextName)	// //SMITH   
	{
		// Add it
		//vecLastNames.push_back(nextName);
//		listLastNames.insert(listLastNames.begin(), nextName);
		listLastNames.insert(listLastNames.end(), nextName);

		//if (rand() % 9 > 3)
		//{
		//	listLastNames.insert(listLastNames.end(), "DAVIS");
		//}

		float discardThis;
		lastNameFile >> discardThis >> discardThis >> discardThis; // 1.006  1.006      1
	}

	for (std::list< std::string >::iterator itName = listLastNames.begin();
		 itName != listLastNames.end(); itName++)
	{
		std::cout << *itName << std::endl;
	}

	std::cout << "*****************************" << std::endl;

//	RemoveFirstInstanceOfName("DAVIS", listLastNames);

//	std::remove(listLastNames.begin(), listLastNames.end(), "DAVIS");

//	listLastNames.sort();		// Less Than  operator <

	listLastNames.sort(isALessThanB);		

	for (std::list< std::string >::iterator itName = listLastNames.begin();
		 itName != listLastNames.end(); itName++)
	{
		std::cout << *itName << std::endl;
	}

//	std::sort(listLastNames.begin(), listLastNames.end());



	//for (unsigned int index = 0; index != listLastNames.size(); index++)
	//{
	//	std::cout << listLastNames[index] << std::endl;

	//}

	//// Keep adding
	//unsigned int count = 0;
	//while (count < 3'000'000)
	//{
	//	vecLastNames.push_back("Hey!");
	//	count++;
	//}

	//vecLastNames.clear();
	//vecLastNames = std::vector< std::string >();


	return 0;
}
