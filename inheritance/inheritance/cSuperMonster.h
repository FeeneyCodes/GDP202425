#pragma once

#include "cMonster.h"

// "public" means:
// we want to have all the "public" things that monster has
// In C++ the way this happen is WE CREATE A cMonster
// if "public" then we expose the cMonster inside Super Monster publically.
class cSuperMonster : public cMonster
{
public:
	cSuperMonster();			// constructor (c'tor)
	cSuperMonster(std::string _name);			// constructor (c'tor)
	~cSuperMonster();		// destructor (d'tor)

	// Overriding
	void MakeNoise(void);


	void GiveBirth(int numberOfMonsters);


	// Called every frame to update the state
	void Update(double deltaTime);

};
