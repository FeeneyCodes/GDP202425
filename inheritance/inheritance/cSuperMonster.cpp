#include "cSuperMonster.h"

#include <iostream>

cSuperMonster::cSuperMonster()		// Default constructor
{
	std::cout << "cSuperMonster::cSuperMonster()" << std::endl;
	this->eyeColour = "grey";
	// 
	this->monsterType = 2;

}

cSuperMonster::cSuperMonster(std::string _name)
{
	this->firstName = _name;
	std::cout << "cSuperMonster::cSuperMonster() : " << this->firstName << std::endl;
}


cSuperMonster::~cSuperMonster()
{
	std::cout << "cSuperMonster::~cSuperMonster() : " << this->firstName << std::endl;

}

// GiveBirth@cSuperMonster@@QEAAXH@Z
void cSuperMonster::GiveBirth(int numberOfMonsters)
{
	std::cout << "Super Monster had " << numberOfMonsters << " children" << std::endl;

	return;
}


void cSuperMonster::MakeNoise(void)
{
	std::cout << "cSuperMonster says bark!" << std::endl;
	return;
}

// Called every frame to update the state
void cSuperMonster::Update(double deltaTime)
{
	std::cout << "cSuperMonster::Update() called" << std::endl;
	return;
}
