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

	// Read only getter (accessor)
	std::string getEyeColour(void);

	void MakeNoise(void);

	// A monster would call this to another monster
	void ReceiveGift(std::string theGift);

	// Called every frame to update the state
	void Update(double deltaTime);

	unsigned int monsterType;

protected:
	// Just like private, but anything 
	//	that inherits form this has this, too
	// Acts like it's still private
	std::string eyeColour;

private:	
	std::string secretCrush;
};
