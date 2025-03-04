// cPhysXWraper.cpp : Defines the functions for the static library.
//
#include "cPhysXWraper.h"

// For PIMPL pattern, this include is ONLY in the CPP file
// (not in the header)
//#include "cPhysXWrap_Imp.h"

cPhysXWraper::cPhysXWraper()
{
//	this->m_pImp = new cPhysXWrap_Imp();
}

cPhysXWraper::~cPhysXWraper()
{
//	delete this->m_pImp;
}

// HACK: Remove this later
//void cPhysXWraper::HACK_ShootBall(void)
//{
//	this->m_pImp->HACK_ShootBall();
//	return;
//}

void cPhysXWraper::getSceneActors(std::vector<cPhysicsObjectTypes>& vecPhysActors)
{
//	this->m_pImp->getSceneActors(vecPhysActors);
	return;
}



void cPhysXWraper::initPhysics(bool interactive, std::string PVD_Host_Address /*= "127.0.0.1"*/)
{
//	this->m_pImp->initPhysics(interactive, PVD_Host_Address);


	return;
}

void cPhysXWraper::update(void)
{
//	this->m_pImp->update();
	return;
}

void cPhysXWraper::cleanupPhysics(bool interactive)
{
//	this->m_pImp->cleanupPhysics(interactive);

	return;
}

void cPhysXWraper::AddBox(
	std::string name,
	glm::vec3 halfExtents,
	glm::vec3 position,
	glm::vec4 EulerOrientation, float mass)
{



	return;
}

void cPhysXWraper::AddSphere(
	std::string name,
	float radius,
	glm::vec3 position,
	glm::vec4 EulerOrientation,
	float mass)
{





	return;
}



