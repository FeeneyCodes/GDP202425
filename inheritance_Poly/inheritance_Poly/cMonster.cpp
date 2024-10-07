#include "cMonster.h"

#include <iostream>

cMonster::cMonster()		// Default constructor
{
	std::cout << "cMonster::cMonster()" << std::endl;
	this->eyeColour = "rainbow";

	// 
	this->monsterType = 1;

}

cMonster::cMonster(std::string _name)
{
	this->firstName = _name;
	std::cout << "cMonster::cMonster() : " << this->firstName << std::endl;
	this->eyeColour = "brown cat eye";
}


cMonster::~cMonster()
{
	std::cout << "cMonster::~cMonster() : " << this->firstName << std::endl;

}


void cMonster::KillAllHumans(void)
{
	std::cout << "cMonster::KillAllHumans(void)" << std::endl;
	// And other stuff too...


	return;
}

std::string cMonster::getEyeColour(void)
{
	return this->eyeColour;
}

void cMonster::MakeNoise(void)
{
	std::cout << "Monster says meow!" << std::endl;
	return;
}

// Called every frame to update the state
void cMonster::Update(double deltaTime)
{
	std::cout << "cMonster::Update() called" << std::endl;


	return;
}

// A monster would call this to another monster
void cMonster::ReceiveGift(std::string theGift)
{
	std::cout << "cMonster: I got a gift!!" << std::endl;
	return;
}
