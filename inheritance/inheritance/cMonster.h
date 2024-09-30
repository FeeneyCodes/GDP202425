#pragma once

#define defaultHealth 100.0f

#include <string>
#include "cVector3.h"


class cMonster
{
public:
	cMonster();			// constructor (c'tor)
	cMonster(std::string _name);			// constructor (c'tor)
	~cMonster();		// destructor (d'tor)
	std::string firstName;
	std::string lastName;
	std::string name;		// First and last
	float health = defaultHealth;
	cVector3 location;
	int age = -1;

	void KillAllHumans(void);

private:
};
