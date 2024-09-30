#include "cMonster.h"

#include <iostream>

cMonster::cMonster()		// Default constructor
{
	std::cout << "cMonster::cMonster()" << std::endl;
	this->eyeColour = "rainbow";

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

