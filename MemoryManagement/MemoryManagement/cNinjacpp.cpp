#include "cNinja.h"
#include <iostream>

cNinja::cNinja()
{
	this->name = "";
	this->age = 35.0f;
	this->health = 100.0f;
}

cNinja::~cNinja()
{
}


void cNinja::Attack(void)
{
	std::cout << this->name << " attacks" << std::endl;
	return;
};