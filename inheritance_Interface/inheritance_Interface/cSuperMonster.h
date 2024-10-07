#pragma once

#include "cMonster.h"

// "public" means:
// we want to have all the "public" things that monster has
// In C++ the way this happen is WE CREATE A cMonster
// if "public" then we expose the cMonster inside Super Monster publically.

// Has an axe
#include "cAxe.h"

class cSuperMonster : public cMonster
{
public:
	cSuperMonster();			// constructor (c'tor)
	cSuperMonster(std::string _name);			// constructor (c'tor)
	~cSuperMonster();		// destructor (d'tor)


	// From the iMonster interface
	virtual void MakeNoise(void);
	virtual void Attack(void);
	virtual void Update(double deltaTime);
	virtual void ReceiveGift(std::string theGift);


	virtual void GiveBirth(int numberOfMonsters);


	std::string FavoriteIceCream;

	unsigned int defaultNumberOfChildren;

	cAxe* pTheAxe = NULL;

};
