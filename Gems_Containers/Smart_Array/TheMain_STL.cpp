#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//SMITH          1.006  1.006      1
//JOHNSON        0.810  1.816      2
//WILLIAMS       0.699  2.515      3
//JONES          0.621  3.136      4
//BROWN          0.621  3.757      5
//DAVIS          0.480  4.237      6

std::vector< std::string > removeFEENEYs(std::vector< std::string > vecLastNames)
{
	std::vector< std::string > vecLastNamesNEW;
	for (std::string name : vecLastNames)
	{
		if (name != "FEENEY")
		{
			vecLastNamesNEW.push_back(name);
		}
	}
//	return vecLastNamesNEW;

	for (std::vector< std::string >::iterator itName = vecLastNames.begin();
		 itName != vecLastNames.end(); itName++ )
	{
		if (*itName == "FEENEY")
		{
			vecLastNames.erase(itName);
		}
	}
	return vecLastNames;
}


int main_STL()
{
	std::fstream lastNameFile("USCen/US_LastNames.txt");

	// Container (smart array)
	std::vector< std::string > vecLastNames;
	
	std::string nextName;
	while (lastNameFile >> nextName)	// //SMITH   
	{
		// Add it
		vecLastNames.push_back(nextName);
		
		float discardThis;
		lastNameFile >> discardThis >> discardThis >> discardThis; // 1.006  1.006      1
	}

	for (std::vector< std::string >::iterator itName = vecLastNames.begin();
		itName != vecLastNames.end(); itName++)
	{
		std::cout << *itName << std::endl;
	}

	for (unsigned int index = 0; index != vecLastNames.size(); index++)
	{
		std::cout << vecLastNames[index] << std::endl;

		std::cout << vecLastNames.operator[](index) << std::endl;

		std::cout << vecLastNames.at(index) << std::endl;
	}

//	std::cout << vecLastNames[100'000] << std::endl;

	vecLastNames = removeFEENEYs(vecLastNames);

	// Keep adding
	unsigned int count = 0;
	while ( count < 3'000'000 )
	{
		vecLastNames.push_back("Hey!");
		count++;
	}

	vecLastNames.clear();
	vecLastNames = std::vector< std::string >();


	return 0;
}
