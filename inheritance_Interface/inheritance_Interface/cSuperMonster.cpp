#include "cSuperMonster.h"

#include <iostream>

cSuperMonster::cSuperMonster()		// Default constructor
{
	std::cout << "cSuperMonster::cSuperMonster()" << std::endl;
	this->eyeColour = "grey";
	// 
	this->monsterType = 2;

	this->defaultNumberOfChildren = 10;

}

cSuperMonster::cSuperMonster(std::string _name)
{
	this->firstName = _name;
	std::cout << "cSuperMonster::cSuperMonster() : " << this->firstName << std::endl;
	this->defaultNumberOfChildren = 10;
}


cSuperMonster::~cSuperMonster()
{
	std::cout << "cSuperMonster::~cSuperMonster() : " << this->firstName << std::endl;

	// 
//	delete this->pTheAxe;
}

// GiveBirth@cSuperMonster@@QEAAXH@Z
void cSuperMonster::GiveBirth(int numberOfMonsters)
{
//	std::cout << "Super Monster had " << numberOfMonsters << " children" << std::endl;
	std::cout << "Super Monster had " << this->defaultNumberOfChildren << " children" << std::endl;

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


void cSuperMonster::Attack(void)
{
	std::cout << "cSuperMonster: ";
	this->pTheAxe->Chop();
	return;
}

void cSuperMonster::ReceiveGift(std::string theGift)
{
	std::cout << "Super monster recieved a " << theGift << std::endl;
	return;
}

