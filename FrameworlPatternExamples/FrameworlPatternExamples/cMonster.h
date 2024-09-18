#ifndef cMonster_HG_
#define cMonster_HG_

#define defaultHealth 100.0f

#include <string>
#include "cVector3.h"

// No code in the header (unless it's a template)

class cMonster
{
public:
	cMonster();			// constructor (c'tor)
	~cMonster();		// destructor (d'tor)
	std::string firstName;
	std::string lastName;
	float health = defaultHealth;
	cVector3 location;
	void KillAllHumans(void);
};




#endif

