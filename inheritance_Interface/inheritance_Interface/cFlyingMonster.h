#pragma once
#include "cMonster.h"

// Inherits means:
// - need an #include
// - "is a" Monster

// Has a sword
#include "cSword.h"

class cFlyingMonster : public cMonster
{
public:
	cFlyingMonster();
	cFlyingMonster(std::string name);
	~cFlyingMonster();

	// From the iMonster interface
	virtual void MakeNoise(void);
	virtual void Attack(void);
	virtual void Update(double deltaTime);
	virtual void ReceiveGift(std::string theGift);


	void Fly(std::string destination);

	cSword* pTheSword = NULL;

};