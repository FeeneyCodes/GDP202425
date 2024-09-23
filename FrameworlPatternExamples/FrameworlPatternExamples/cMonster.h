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
	std::string name;		// First and last
	float health = defaultHealth;
	cVector3 location;
	int age = -1;
	void KillAllHumans(void);
	void PrintStats(void);
	unsigned int uniqueID;

	void AttackThisMonster(cMonster* pTarget);
	void AttackThisMonster(unsigned int uniqueID);

};




#endif

