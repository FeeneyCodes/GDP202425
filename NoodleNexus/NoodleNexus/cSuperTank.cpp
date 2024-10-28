#include "cSuperTank.h"

#include <iostream>

cSuperTank::cSuperTank()
{
	std::cout << "A super tank is created" << std::endl;
	this->m_ID = cSuperTank::m_NextID++;
	// Add a rail gun
	this->pTheRailGun = new cRailGun();

}

/*static*/
unsigned int cSuperTank::m_NextID = 8000;


cSuperTank::~cSuperTank()
{
//	delete this->pTheRailGun;
}

void cSuperTank::Attack(/*another tank*/)
{

	return;
}

glm::vec3 cSuperTank::getLocation(void)
{
	// TODO: 

	return glm::vec3(0.0f);
}

void cSuperTank::UpdateTick(double deltaTime)
{
	// TODO:
	std::cout << "Tank# " << this->m_ID << " updating" << std::endl;

	return;
}

unsigned int cSuperTank::getID(void)
{
	return this->m_ID;
}