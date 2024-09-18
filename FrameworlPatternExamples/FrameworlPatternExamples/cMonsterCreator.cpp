#include "cMonsterCreator.h"

#include <fstream>
#include <string>
#include <iostream>

cMonsterCreator::cMonsterCreator()
{
}

cMonsterCreator::~cMonsterCreator()
{
}


bool cMonsterCreator::LoadNames(
	std::string lastnameFileName,
	std::string boysFileName,
	std::string girlsFileName)
{

	struct sLastName
	{
		std::string name;
		float col_1;
		float col_2;
		int col_3;
	};


	{
		// **************************************************************
		// LAST NAMES:
		std::ifstream lastNameFileStream(lastnameFileName);
		if (lastNameFileStream.is_open() == false)
		{
			// Didn't open the file
			return false;
		}

		// Load the last names. 
		// It's in this format:
		//	SMITH    1.006     1.006    1

		std::string name;
		while (lastNameFileStream >> name)
		{

			float discardThis;
			lastNameFileStream >> discardThis >> discardThis >> discardThis;

			// Add to the array
//			lastNames[numberOfNamesInArray] = name;
//			numberOfNamesInArray++;
//			std::cout << name << " ";

			// std::vector<std::string> vecLastNames;
			this->m_vecLastNames.push_back(name);
		}

		//sLastName currentLine;
		//while (lastNameFileStream >> currentLine.name)
		//{

		//	lastNameFileStream 
		//		>> currentLine.col_1 
		//		>> currentLine.col_2 
		//		>> currentLine.col_3;
		//	std::cout << name << " ";
		//}
		lastNameFileStream.close();
		// **************************************************************
	}

	{
		// **************************************************************
		// BOY's NAMES:
		std::ifstream boysNamesFileStream(boysFileName);
		if (boysNamesFileStream.is_open() == false)
		{
			// Didn't open the file
			return false;
		}

		// Load the last names. 
		// It's in this format:
		//	SMITH    1.006     1.006    1

		std::string name;
		while (boysNamesFileStream >> name)
		{

			float discardThis;
			boysNamesFileStream >> discardThis >> discardThis >> discardThis;

			this->m_vecBoysNames.push_back(name);
//			std::cout << name << " ";
		}


		boysNamesFileStream.close();
		// **************************************************************
	}

	{
		// **************************************************************
		// GIRLS NAMES:
		std::ifstream girlsNamesFileStream(girlsFileName);
		if (girlsNamesFileStream.is_open() == false)
		{
			// Didn't open the file
			return false;
		}

		// Load the last names. 
		// It's in this format:
		//	SMITH    1.006     1.006    1

		std::string name;
		while (girlsNamesFileStream >> name)
		{

			float discardThis;
			girlsNamesFileStream >> discardThis >> discardThis >> discardThis;

			this->m_vecGirlsNames.push_back(name);
//			std::cout << name << " ";
		}


		girlsNamesFileStream.close();
		// **************************************************************
	}

	// Everything went OK
	return true;
}


cMonster cMonsterCreator::CreateMonster(void)
{
//	std::vector<std::string> m_vecLastNames;
//	std::vector<std::string> m_vecBoysNames;
//	std::vector<std::string> m_vecGirlsNames;

	cMonster newMonster;
	newMonster.health = 100;
	newMonster.location.x = 0.0f;
	newMonster.location.y = 0.0f;
	newMonster.location.z = 0.0f;

	// TODO: Pick a random first and last name
	// Some thoughts:
	// - for the boys and girls, you could:
	//   - Choose between boy or girl, then pick a random entry, or
	//   - Combine both vectors into one "generic name" vector and 
	//     pick from that combinied vector
	// - rand() is only up to 32,000, and since the last name 
	//   file is 88,000+, it won't actually pick a random name
	//   from this list; like it'll miss some.
	//   (this is where the C++ 11 random library is helpful)
	//   Although you could also add a bunch of rand() values, then 
	//   pick a number between those. 
	//   int x = rand() + rand() + rand()
	//		(would give you a number between 0 and 96,000, etc.
	//   (it's a hack, but hey, we're picking monster names...)
	// Note that using the C++ 11 random is very "heavy" in that
	// the intialization takes space and time, so doing this every call
	// would be WAY slower than calling rand().
	// You could avoid this by initializing the c++ 11 random ONCE
	// and keeping it around between calls if you like. 

	// Boy or girl list
	if (rand() % 2)		// Modulus
	{
		size_t index = rand() % this->m_vecBoysNames.size();
		newMonster.firstName = this->m_vecBoysNames[index];
	}
	else
	{
		size_t index = rand() % this->m_vecGirlsNames.size();
		newMonster.firstName = this->m_vecGirlsNames[index];
	}
	// Last name
	size_t index = rand() % this->m_vecLastNames.size();
	newMonster.lastName = this->m_vecLastNames[index];

	newMonster.name = newMonster.firstName + " " + newMonster.lastName;

	return newMonster;
}



// chatGPT's hot take on this
// give me some c++ code that will give a random item from std::vector<std::string> m_vecLastNames;
//
//std::string getRandomLastName(const std::vector<std::string>& m_vecLastNames) {
//	if (m_vecLastNames.empty()) {
//		return ""; // Return an empty string if the vector is empty
//	}
//
//	// Create a random number generator
//	std::random_device rd;  // Obtain a random number from hardware
//	std::mt19937 eng(rd()); // Seed the generator
//	std::uniform_int_distribution<> distr(0, m_vecLastNames.size() - 1); // Define the range
//
//	// Generate a random index
//	int randomIndex = distr(eng);
//	return m_vecLastNames[randomIndex]; // Return the random last name
//}
