#include "cSuperFlyingMonster.h"
#include <iostream>

cSuperFlyingMonster::cSuperFlyingMonster()
{
	std::cout << "cSuperFlyingMonster::cSuperFlyingMonster()" << std::endl;
}

cSuperFlyingMonster::cSuperFlyingMonster(std::string _name)
{
	std::cout << "cSuperFlyingMonster::cSuperFlyingMonster()" << std::endl;
	this->m_name = _name;
}


cSuperFlyingMonster::~cSuperFlyingMonster()
{
	std::cout << "cSuperFlyingMonster::~cSuperFlyingMonster()" << std::endl;
}



// Overriding
void cSuperFlyingMonster::MakeNoise(void)
{
	std::cout << "ROAR!" << std::endl;
}


// This is virtual
void cSuperFlyingMonster::Update(double deltaTime)
{
	std::cout << "cSuperFlyingMonster::Update()" << std::endl;
}


// SPecific to super flying monster
void cSuperFlyingMonster::LayEggs(void)
{
	std::cout << "cSuperFlyingMonster::LayEggs()" << std::endl;
}
