#include "cMoveRelativeTime.h"

void cMoveRelativeTime::OnStart(void)
{
	// TODO: 
	return;
}

void cMoveRelativeTime::Update(double deltaTime)
{
	// Let the physics thing move the object
	// Keep track of the elapsed time
	this->m_elapsedTime += deltaTime;
	return;
}
bool cMoveRelativeTime::isFinished(void)
{
	// Has the amount of time passed
	if (this->m_elapsedTime >= this->m_timeToMove)
	{
		// We've arrived
		return true;
	}

	// Keep going...
	return false;
}

void cMoveRelativeTime::OnFinished(void)
{
	// TODO: 
	return;
}


void cMoveRelativeTime::Init(cPhysics::sPhysInfo* pObject, glm::vec3 endXYZ, double timeToMove)
{
	this->m_endXYZ = endXYZ;
	this->m_timeToMove = timeToMove;
	this->m_pObject = pObject;
	this->m_elapsedTime = 0.0;
	// Calcuate the velocity required to get this object to that location
	glm::vec3 totalDistance = endXYZ - pObject->position;
	// What velocity will get us there?
//	pObject->velocity.x = totalDistance.x / timeToMove;
//	pObject->velocity.y = totalDistance.y / timeToMove;
//	pObject->velocity.z = totalDistance.z / timeToMove;
	pObject->velocity = totalDistance / (float)timeToMove;

	return;
}
