#include "cPhysics.h"

#include <iostream>

glm::vec3 cPhysics::sAABB::getExtentsXYZ(void)
{
	glm::vec3 extentXYZ;
	extentXYZ.x = this->maxXYZ.x - this->minXYZ.z;
	extentXYZ.y = this->maxXYZ.y - this->minXYZ.y;
	extentXYZ.z = this->maxXYZ.z - this->minXYZ.z;
	return extentXYZ;
}

void cPhysics::StepTick(double deltaTime)
{
	// Clear all the collision from the last frame
	this->vec_SphereAABB_Collisions.clear();
	this->vec_SphereSphere_Collisions.clear();


	// ***********************************************************************************
	//    ___       _                       _                   _             
	//   |_ _|_ __ | |_ ___  __ _ _ __ __ _(_) ___  _ __    ___| |_ ___ _ __  
	//    | || '_ \| __/ _ \/ _` | '__/ _` | |/ _ \| '_ \  / __| __/ _ \ '_ \ 
	//    | || | | | ||  __/ (_| | | | (_| | | (_) | | | | \__ \ ||  __/ |_) |
	//   |___|_| |_|\__\___|\__, |_|  \__,_|_|\___/|_| |_| |___/\__\___| .__/ 
	//                      |___/                                      |_|    
	// Copy the "physics info" part to another vector to do the integration step
	std::vector< sPhysInfo* > vec_Temp_pPhysInfos;

	// COPY the sphere info
	for (unsigned int sphereIndex = 0; sphereIndex != this->vecSpheres.size(); sphereIndex++)
	{
		sSphere* pCurrentSphere = this->vecSpheres[sphereIndex];
		vec_Temp_pPhysInfos.push_back(pCurrentSphere->pPhysicInfo);
	}
	// COPY the AABB info
	for (unsigned int AABBindex = 0; AABBindex != this->vecAABBs.size(); AABBindex++)
	{
		sAABB* pCurrentAABB = this->vecAABBs[AABBindex];
		vec_Temp_pPhysInfos.push_back(pCurrentAABB->pPhysicInfo);
	}



	// Now ALL the physical properties we are integrating are in one step
	for (unsigned int index = 0; index != vec_Temp_pPhysInfos.size(); index++)
	{
		sPhysInfo* pCurObject = vec_Temp_pPhysInfos[index];

		// Can this object move? 
		if (pCurObject->bDoesntMove)
		{
			// No, so skip integration step
			continue;
		}

		//Update the velocity based on the acceleration
		glm::vec3 deltaVelocity = pCurObject->acceleration * (float)deltaTime;
		pCurObject->velocity += deltaVelocity;

		// Update the position based on the velocity
		// i.e. how much this objects velocity is changing THIS step (this frame)
		glm::vec3 deltaPosition = pCurObject->velocity * (float)deltaTime;
		pCurObject->position += deltaPosition;
	}//for (unsigned int index

	// ***********************************************************************************


	// Update the mesh locations to match the new physics positions, etc.
	for (unsigned int index = 0; index != vec_Temp_pPhysInfos.size(); index++)
	{
		sPhysInfo* pCurObject = vec_Temp_pPhysInfos[index];
		// 
		pCurObject->pAssociatedDrawingMeshInstance->positionXYZ = pCurObject->position;

		// TODO: If there's other things that update, too 
		// (rotation, etc.
	}//for (unsigned int index




//
//	// Update the positions, etc. of the object
//	for (unsigned int sphereIndex = 0; sphereIndex != this->vecSpheres.size(); sphereIndex++)
//	{
//		sSphere* pCurrentSphere = this->vecSpheres[sphereIndex];
//
//		pCurrentSphere->physicInfo.position += (pCurrentSphere->physicInfo.velocity * (float)deltaTime);
//		//pCurrentSphere->physicInfo.position.x += (pCurrentSphere->physicInfo.velocity.x * (float)deltaTime);
//		//pCurrentSphere->physicInfo.position.y += (pCurrentSphere->physicInfo.velocity.y * (float)deltaTime);
//		//pCurrentSphere->physicInfo.position.z += (pCurrentSphere->physicInfo.velocity.z * (float)deltaTime);
////		std::cout << pCurrentSphere->physicInfo.position.y << std::endl;
//
//		// Update the position of the associated me
//		pCurrentSphere->physicInfo.pAssociatedDrawingMeshInstance->positionXYZ
//			= pCurrentSphere->physicInfo.position;
//	}

	// Test for collisions
	this->m_CheckForCollisions(deltaTime);

	return;
}

void cPhysics::m_CheckForCollisions(double deltaTime)
{
	// For each sphere, test all the other spheres?



	// For each AABB, test all the other AABBs?


	// For each sphere, test all the AABBs
	for (unsigned int sphereIndex = 0; sphereIndex != this->vecSpheres.size(); sphereIndex++)
	{
		sSphere* pCurrentSphere = this->vecSpheres[sphereIndex];

		for (unsigned int AABBIndex = 0; AABBIndex != this->vecAABBs.size(); AABBIndex++)
		{
			sAABB* pCurrentAABB = this->vecAABBs[AABBIndex];

			if (this->bSphereAABBCollision(pCurrentSphere, pCurrentAABB))
			{
				// They collided! 
				// Oh no... what are we supposed to do now?? 

				// HACK: change direction of sphere
				// Check if the sphere is going "down" -ve in the y
				if (pCurrentSphere->pPhysicInfo->velocity.y < 0.0f)
				{
					// Yes, it's heading down
					// So reverse the direction of velocity
					pCurrentSphere->pPhysicInfo->velocity.y = fabs(pCurrentSphere->pPhysicInfo->velocity.y);
				}

				// HACK:
//				std::cout << "A sphere and AABB collided! Huzzah!" << std::endl;
//				this->SphereAABBCollided(pCurrentSphere, pCurrentAABB);

				sCollision_SphereAABB theCollision;
				theCollision.pTheSphere = pCurrentSphere;
				theCollision.pTheAABB = pCurrentAABB;
				// And so on...

				this->vec_SphereAABB_Collisions.push_back(theCollision);

			}//if (this->bSphereAABBCollision(
		}//for (unsigned int AABBIndex 
	}//for (unsigned int sphereIndex


	// 100x100 --> 10,000 checks every frame

	// Check every sphere with every other sphere
	for (unsigned int outerLoopSphereIndex = 0; outerLoopSphereIndex != this->vecSpheres.size(); outerLoopSphereIndex++)
	{
		sSphere* pOuterLoopSphere = this->vecSpheres[outerLoopSphereIndex];

		for (unsigned int innerLoopSphereIndex = 0; innerLoopSphereIndex != this->vecSpheres.size(); innerLoopSphereIndex++)
		{
			sSphere* pInnerLoopSphere = this->vecSpheres[innerLoopSphereIndex];

			// Are these the same sphere? 
			if (pOuterLoopSphere == pInnerLoopSphere)
			{
				// Yes, so DON'T test these ('cuase they are the same, so always colliding)
				continue;
			}

			if ( this->bSphereSphereCollision(pInnerLoopSphere, pOuterLoopSphere) )
			{
//				std::cout << "Two spheres have collided!" << std::endl;
			}

		}//for (unsigned int innerLoopSphereIndex

	}//for (unsigned int outerLoopSphereIndex


	return;
}


bool cPhysics::bSphereAABBCollision(sSphere* pSphere, sAABB* pAABB)
{
	glm::vec3 AABBextents = pAABB->getExtentsXYZ();


	// Check if it HASN'T connected
	// Y axis first
	if ((pSphere->pPhysicInfo->position.y - pSphere->radius) > (pAABB->pPhysicInfo->position.y + AABBextents.y))
	{
		// Isn't colliding
		return false;
	}
	if ((pSphere->pPhysicInfo->position.y + pSphere->radius) < (pAABB->pPhysicInfo->position.y - AABBextents.y))
	{
		// Isn't colliding
		return false;
	}

	// X axis
	if ((pSphere->pPhysicInfo->position.x + pSphere->radius) < (pAABB->pPhysicInfo->position.x - AABBextents.x))
	{
		// Isn't colliding
		return false;
	}
	if ((pSphere->pPhysicInfo->position.x - pSphere->radius) > (pAABB->pPhysicInfo->position.x + AABBextents.x))
	{
		// Isn't colliding
		return false;
	}

	// Z axis
	if ((pSphere->pPhysicInfo->position.z + pSphere->radius) < (pAABB->pPhysicInfo->position.z - AABBextents.z))
	{
		// Isn't colliding
		return false;
	}
	if ((pSphere->pPhysicInfo->position.z - pSphere->radius) > (pAABB->pPhysicInfo->position.z + AABBextents.z))
	{
		// Isn't colliding
		return false;
	}

	// Overlapping on ALL axes, so must be colliding

	return true;
}

bool cPhysics::bSphereSphereCollision(sSphere* pA, sSphere* pB)
{

	float totalRadius = pA->radius + pB->radius;

		// Like 2D pythagorean theorem, you can calculate the distance between two points
		//	by taking the square root of the sum of the differences of each axis
//			float deltaX = pInnerLoopSphere->pPhysicInfo->position.x - pOuterLoopSphere->pPhysicInfo->position.x;
//			float deltaY = pInnerLoopSphere->pPhysicInfo->position.y - pOuterLoopSphere->pPhysicInfo->position.y;
//			float deltaZ = pInnerLoopSphere->pPhysicInfo->position.z - pOuterLoopSphere->pPhysicInfo->position.z;
//
//			float distance = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
			
	// Or use glm
	float distance = glm::distance(pA->pPhysicInfo->position, pB->pPhysicInfo->position);

	if (distance <= totalRadius)
	{
//		std::cout << "Two spheres have collided!" << std::endl;
		return true;
	}

	return false;
}

bool cPhysics::bAABB_ABBBCollision(sAABB* pA, sAABB* pB)
{
	// TODO: 

	return false;
}
