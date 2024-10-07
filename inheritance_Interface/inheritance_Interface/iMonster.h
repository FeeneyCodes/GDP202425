#pragma once

#include <string>

// This is going to be an "interface class"
// The "i" is just a convention, like "c" for "class"

class iMonster
{
public:
	// The "= 0" means there isn't a method "body" (code) to this
	// It's ONLY a definition of a method
	// "pure virtual method"
	virtual void MakeNoise(void) = 0;
	virtual void Attack(void) = 0;
	virtual void Update(double deltaTime) = 0;
	virtual void ReceiveGift(std::string theGift) = 0;
// No private, no variable, etc. 
};
