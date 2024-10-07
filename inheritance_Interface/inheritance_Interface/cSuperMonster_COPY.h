#pragma once

#pragma once

#define defaultHealth 100.0f

#include <string>
#include "cVector3.h"


class cSuperMonster
{
public:
	cSuperMonster();			// constructor (c'tor)
	cSuperMonster(std::string _name);			// constructor (c'tor)
	~cSuperMonster();		// destructor (d'tor)
	std::string lastName;
	std::string firstName;
	std::string name;		// First and last
	float health = defaultHealth;
	cVector3 location;
	int age = -1;

	void KillAllHumans(void);
	void GiveBirth(int numberOfMonsters);

private:
};