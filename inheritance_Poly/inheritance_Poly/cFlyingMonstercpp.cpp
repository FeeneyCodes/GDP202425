#include "cFlyingMonster.h"
#include <iostream>

cFlyingMonster::cFlyingMonster()		// Default constructor
{
	std::cout << "cFlyingMonster::cFlyingMonster()" << std::endl;

	// 
	this->monsterType = 3;

}

void cFlyingMonster::Fly(std::string destination)
{
	std::cout << "cFlyingMonster::Fly()" << std::endl;
	return;
}


cFlyingMonster::cFlyingMonster(std::string _name)
{
	this->firstName = _name;
	std::cout << "cFlyingMonster::cFlyingMonster() : " << this->firstName << std::endl;
}


cFlyingMonster::~cFlyingMonster()
{
	std::cout << "cFlyingMonster::~cFlyingMonster() : " << this->firstName << std::endl;

}


// Called every frame to update the state
void cFlyingMonster::Update(double deltaTime)
{
	std::cout << "cFlyingMonster::Update() called" << std::endl;
	return;
}

void cFlyingMonster::MakeNoise(void)
{
	std::cout << "cFlyingMonster says caw!" << std::endl;
	return;
}
