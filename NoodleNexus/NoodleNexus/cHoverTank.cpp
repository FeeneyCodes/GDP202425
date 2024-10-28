#include "cHoverTank.h"
#include <iostream>

cHoverTank::cHoverTank()
{
	std::cout << "A hover tank is created" << std::endl;
	this->m_ID = cHoverTank::m_NextID++;

}

/*static*/
unsigned int cHoverTank::m_NextID = 3000;


cHoverTank::~cHoverTank()
{

}

void cHoverTank::Attack(/*another tank*/)
{

	return;
}

glm::vec3 cHoverTank::getLocation(void)
{
	// TODO: 

	return glm::vec3(0.0f);
}

void cHoverTank::UpdateTick(double deltaTime)
{
	// TODO:
	std::cout << "Tank# " << this->m_ID << " updating" << std::endl;

	return;
}

unsigned int cHoverTank::getID(void)
{
	return this->m_ID;
}