#include "cMonster.h"

#include <iostream>

cMonster::cMonster()		// Default constructor
{
	std::cout << "cMonster::cMonster()" << std::endl;


}

cMonster::cMonster(std::string _name)
{
	this->firstName = _name;
	std::cout << "cMonster::cMonster() : " << this->firstName << std::endl;
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
