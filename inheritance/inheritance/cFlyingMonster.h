#pragma once
#include "cMonster.h"

// Inherits means:
// - need an #include
// - "is a" Monster
class cFlyingMonster : public cMonster
{
public:
	cFlyingMonster();
	cFlyingMonster(std::string name);
	~cFlyingMonster();

	void Fly(std::string destination);

	// Called every frame to update the state
	void Update(double deltaTime);

};