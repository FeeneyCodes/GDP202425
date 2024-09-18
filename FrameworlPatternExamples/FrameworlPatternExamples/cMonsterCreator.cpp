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


}
