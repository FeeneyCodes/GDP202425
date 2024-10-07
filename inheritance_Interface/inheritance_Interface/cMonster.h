#pragma once

#include "iMonster.h"

#define defaultHealth 100.0f

#include <string>
#include "cVector3.h"


class cMonster : public iMonster
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

	// Read only getter (accessor)
	std::string getEyeColour(void);

	// From the iMonster interface
	virtual void MakeNoise(void);
	virtual void Attack(void);
	virtual void Update(double deltaTime);
	virtual void ReceiveGift(std::string theGift);


	unsigned int monsterType;

	bool bIsFlyingMonster;
	bool bIsSuperMonsterOnly;

protected:
	// Just like private, but anything 
	//	that inherits form this has this, too
	// Acts like it's still private
	std::string eyeColour;

private:	
	std::string secretCrush;
};
