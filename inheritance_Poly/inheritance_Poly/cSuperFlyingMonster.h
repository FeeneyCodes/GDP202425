#pragma once
#include "cFlyingMonster.h"
#include "cSuperMonster.h"

class cSuperFlyingMonster :
	public cSuperMonster, 
	public cFlyingMonster
{
public:
	cSuperFlyingMonster();			// constructor (c'tor)
	cSuperFlyingMonster(std::string _name);			// constructor (c'tor)
	~cSuperFlyingMonster();		// destructor (d'tor)

	// Overriding
	void MakeNoise(void);

	// This is virtual
	void Update(double deltaTime);

	// SPecific to super flying monster
	void LayEggs(void);

private:
	std::string m_name;

};
