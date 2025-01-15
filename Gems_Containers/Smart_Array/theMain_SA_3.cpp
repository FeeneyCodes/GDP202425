#include "cSmartArray_3.h"
#include <string>
#include <iostream>
#include <fstream>

int main_SA_3()
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

	lastNameFile.close();


	//unsigned int count = 0;
	//while (count < 30'000'000)
	//{
	//	vecLastNames.appendToEnd("Hey!");
	//	count++;
	//}

	//	for (unsigned int index = 0; index != vecLastNames.size(); index++)
	//for (unsigned int index = 0;
	//	index < vecLastNames.getSize();
	//	index++)
	//{
	//	//		std::cout << vecLastNames[index] << std::endl;
	//	std::cout << vecLastNames.getAtIndex(index) << std::endl;
	//}

	// *****************************************

	class cNinja
	{
	public:
		std::string lastName;
		float health;
		int age;
	};


	cSmartArray_3<cNinja> vecNinjas;

	lastNameFile.open("USCen/US_LastNames.txt", std::ifstream::in);


	while (lastNameFile >> nextName)	// //SMITH   
	{
		// Add it
		//vecLastNames.push_back(nextName);
		cNinja newNinja;	
		newNinja.lastName = nextName;
		vecNinjas.appendToEnd(newNinja);

		float discardThis;
		lastNameFile >> discardThis >> discardThis >> discardThis; // 1.006  1.006      1
	}

	unsigned int count = 0;
	while (count < 30'000'000)
	{
		cNinja newNinja;
		newNinja.lastName = "Hey!";

		vecNinjas.appendToEnd(newNinja);
		count++;
	}

	//	for (unsigned int index = 0; index != vecLastNames.size(); index++)
	for (unsigned int index = 0;
		index < vecNinjas.getSize();
		index++)
	{
		//		std::cout << vecLastNames[index] << std::endl;
		std::cout << vecNinjas.getAtIndex(index).lastName << std::endl;
	}


	return 0;
}