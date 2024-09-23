#include "cArena.h"
#include <algorithm>
#include <iostream>

int count = 0;

// Predicate function
// Assumes that it's "less than" or the "<" operator
bool IsYounger(cMonster* pMA, cMonster* pMB)
{
	count++;
	if (pMA->age < pMB->age)
	{
		return true;
	}
	return false;
}

bool byNameAscending(cMonster* pMA, cMonster* pMB)
{
	// Compare last name 
	if (pMA->lastName < pMB->lastName)
	{
		return true;
	}
	if (pMA->lastName == pMB->lastName)
	{
		// Compare last names
		if (pMA->firstName < pMB->firstName)
		{
			return true;
		}
		else
		{
			// Last names are same, 
			return false;
		}
	}
	return false;
}

// For find_if
bool IsThisTED_with_AGE_GT_100(cMonster* pM)
{
	if (pM->firstName != "TED")
	{
		return false;
	}
	// It's ted! 
	if (pM->age >= 100)
	{
		return true;
	}
	return false;
}

// For find_if, more general 
bool byNameAndMinAge(cMonster* pM, std::string firstName, unsigned int minAge)
{
	if (pM->firstName != firstName)
	{
		return false;
	}
	// It's ted! 
	if (pM->age >= (int)minAge)
	{
		return true;
	}
	return false;
}

class cByNameAndMinAge
{
public:
	cByNameAndMinAge(std::string firstName, unsigned int minAge)
	{
		this->m_firstName = firstName;
		this->m_minAge = minAge;
	}

	// For find_if, more general 
	// The comparison "function" for a predicate "class" 
	// ("fuctor")

	//bool operator[] (cMonster* pM)
	//{
	//	if (pM->firstName != "TED")
	//	{
	//		return false;
	//	}
	//	// It's ted! 
	//	if (pM->age >= 100)
	//	{
	//		return true;
	//	}
	//	return false;
	//}

	bool operator()(cMonster* pM)
	{
		if (pM->firstName != this->m_firstName)
		{
			return false;
		}
		// It's ted! 
		if (pM->age >= (int)this->m_minAge)
		{
			return true;
		}
		return false;
	}
private:
	std::string m_firstName;
	unsigned int m_minAge;
};

bool cArena::InitLevel(unsigned int numberOfMonsters, cVector3 arenaSize)
{
	cMonsterCreator* pMC = new cMonsterCreator();

	if (!pMC->LoadNames("USCen/US_LastNames.txt",
		"USCen/dist.male.first.txt",
		"USCen/dist.female.first.txt"))
	{
//		std::cout << "ERROR: Didn't load the census files." << std::endl;
		return false;
	}

	for (unsigned int count = 0; count != numberOfMonsters; count++)
	{
		cMonster* pNewMonster = pMC->CreateMonster();

		//TODO: Place the monsters somewhere in the arena

		this->m_vec_pTheMonsters.push_back(pNewMonster);
	}

	this->m_vec_pTheMonsters[5]->lastName = this->m_vec_pTheMonsters[15]->lastName;

	// Sort the monsters by Age. Youngest first.
	// 	std::vector<cMonster*> m_vec_pTheMonsters;
	std::sort(this->m_vec_pTheMonsters.begin(),
		this->m_vec_pTheMonsters.end(),
		byNameAscending);

	std::sort(this->m_vec_pTheMonsters.begin(),
		this->m_vec_pTheMonsters.end(),
		// Lambda expression
		 [] (cMonster* pMA, cMonster* pMB)
			{
				if (pMA->age < pMB->age)
				{
					return true;
				}
				return false;
			}
		);

	this->m_vec_pTheMonsters[7]->firstName = "TED";
	this->m_vec_pTheMonsters[7]->age = 250;




			// Find "ted" who's at least 100
	std::vector<cMonster*>::iterator itTed100 =
		std::find_if(
			this->m_vec_pTheMonsters.begin(),
			this->m_vec_pTheMonsters.end(),
			cByNameAndMinAge("TED", 100));


	//cByNameAndMinAge functor("TED", 100);

	//std::vector<cMonster*>::iterator itTed100 =
	//	std::find_if(
	//		this->m_vec_pTheMonsters.begin(),
	//		this->m_vec_pTheMonsters.end(),
	//		functor);

//			IsThisTED_with_AGE_GT_100);
	// If it doesn't find it, return .end()
	if (itTed100 != this->m_vec_pTheMonsters.end())
	{
		// found it
		std::cout << (*itTed100)->name << " " << (*itTed100)->age << std::endl;
	}


//	std::vector<cMonster> vecMonsters;
//	std::sort(vecMonsters.begin(), vecMonsters.end());






	delete pMC;

	return true;
}

void cArena::PrintMonsters(void)
{
	for (unsigned int index = 0; index != this->m_vec_pTheMonsters.size(); index++)
	{
		cMonster* pCurMon = this->m_vec_pTheMonsters[index];

		std::cout 
			<< index << " : " 
			<< pCurMon->name << ", "
			<< pCurMon->age << std::endl;
	}

	return;
}
