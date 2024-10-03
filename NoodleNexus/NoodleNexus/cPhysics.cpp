#include "cPhysics.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 

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

//				// HACK: change direction of sphere
//				// Check if the sphere is going "down" -ve in the y
//				if (pCurrentSphere->pPhysicInfo->velocity.y < 0.0f)
//				{
//					// Yes, it's heading down
//					// So reverse the direction of velocity
//					pCurrentSphere->pPhysicInfo->velocity.y = fabs(pCurrentSphere->pPhysicInfo->velocity.y);
//				}

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


void cPhysics::setVAOManager(cVAOManager* pTheVAOManager)
{
	this->m_pVAOManager = pTheVAOManager;
	return;
}

bool cPhysics::addTriangleMesh(std::string meshModelName)
{
	// TODO: 
	return false;
}

bool cPhysics::addTriangleMesh(
	std::string meshModelName,
	glm::vec3 meshWorldPosition,
	glm::vec3 meshWorldOrientation,
	float uniformScale)
{
	if (!this->m_pVAOManager)
	{
		// Haven't set the VAO manager pointer, yet
		return false;
	}

	std::vector<cVAOManager::sTriangle> vecVAOTriangles;
	if (!this->m_pVAOManager->getTriangleMeshInfo(meshModelName, vecVAOTriangles))
	{
		// Can't find mesh
		return false;
	}

	// At this point, the vecTriangles has all the triangle info.
	
	sTriangleMesh* pMesh = new sTriangleMesh();

	// Copy that vector into the local mesh format 
	for (std::vector<cVAOManager::sTriangle>::iterator itVAOTri = vecVAOTriangles.begin();
		itVAOTri != vecVAOTriangles.end(); itVAOTri++)
	{
		cVAOManager::sTriangle curVAOTri = *itVAOTri;

		sTriangle curTri;
		curTri.vertices[0] = curVAOTri.vertices[0];
		curTri.vertices[1] = curVAOTri.vertices[1];
		curTri.vertices[2] = curVAOTri.vertices[2];
		curTri.normal = curVAOTri.normal;

		pMesh->vecTriangles.push_back(curTri);

	}//for (std::vector<cVAOManager::sTriangle>::iterator itVAOTri
	 
	// Transform the triangles to where they are in the world
	for (std::vector<sTriangle>::iterator itTri = pMesh->vecTriangles.begin();
		itTri != pMesh->vecTriangles.end(); itTri++)
	{
		// Take the same matrix transformation technique 
		//	from the render call and apply to each vertex

		glm::mat4 matModel = glm::mat4(1.0f);

		// Translation (movement, position, placement...)
		glm::mat4 matTranslate
			= glm::translate(glm::mat4(1.0f),
				meshWorldPosition);

		// Rotation...
		// Caculate 3 Euler acix matrices...
		glm::mat4 matRotateX =
			glm::rotate(glm::mat4(1.0f),
				glm::radians(meshWorldOrientation.x), // Angle in radians
				glm::vec3(1.0f, 0.0, 0.0f));

		glm::mat4 matRotateY =
			glm::rotate(glm::mat4(1.0f),
				glm::radians(meshWorldOrientation.y), // Angle in radians
				glm::vec3(0.0f, 1.0, 0.0f));

		glm::mat4 matRotateZ =
			glm::rotate(glm::mat4(1.0f),
				glm::radians(meshWorldOrientation.z), // Angle in radians
				glm::vec3(0.0f, 0.0, 1.0f));


		// Scale
		glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
			glm::vec3(uniformScale, uniformScale, uniformScale));


		// Calculate the final model/world matrix
		matModel *= matTranslate;     // matModel = matModel * matTranslate;
		matModel *= matRotateX;
		matModel *= matRotateY;
		matModel *= matRotateZ;
		matModel *= matScale;


		// Like from the vertex shader: 	
		// fvertexWorldLocation = matModel * vec4(finalVert, 1.0);

		sTriangle curTriangle = *itTri;
		// Transform the vertex to where they are in the world...
		glm::vec4 vert0World = matModel * glm::vec4(curTriangle.vertices[0], 1.0f);
		glm::vec4 vert1World = matModel * glm::vec4(curTriangle.vertices[0], 1.0f);
		glm::vec4 vert2World = matModel * glm::vec4(curTriangle.vertices[0], 1.0f);

		// Copy the transformed vertices bacl
		itTri->vertices[0] = vert0World;
		itTri->vertices[1] = vert1World;
		itTri->vertices[2] = vert2World;

		// Also rotate the normal
		glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matModel));

		itTri->normal 
			= glm::vec3( matModelInverseTranspose * glm::vec4(itTri->normal, 1.0f) );

	}//for (std::vector<sTriangle>::iterator itTri

	pMesh->meshInstanceName = meshModelName;
//	pMesh->meshModelName = ??
	this->vecMeshes.push_back(pMesh);


	return true;
}


bool cPhysics::rayCast(glm::vec3 start, glm::vec3 end,
	std::vector<sCollision_RayTriangleInMesh>& vec_RayTriangle_Collisions)
{
	sLine theRay;
	theRay.startXYZ = start;
	theRay.endXYZ = end;

	// Clear the vector being passed in...
	vec_RayTriangle_Collisions.clear();

	// Got through all the triangle mesh objects and test 
	//	the ray triangle for each triangle in each mesh
	for (std::vector< sTriangleMesh*>::iterator itMesh = this->vecMeshes.begin();
		itMesh != this->vecMeshes.end(); itMesh++)
	{
		// Dereference the iterator to get the mesh
		sTriangleMesh* pCurTriMesh = *itMesh;

		// Go through each triangle
		for (std::vector<sTriangle>::iterator itTri = pCurTriMesh->vecTriangles.begin();
			itTri != pCurTriMesh->vecTriangles.end(); itTri++)
		{

			sTriangle CurTriangle = *itTri;
			// Sorry, but the method takes pointers to the 
			//	line(ray) and triangle.
			// I did this because the other methods did this
			if (this->bRay_TriangleCollision(theRay, CurTriangle))
			{
				// They intersect
				sCollision_RayTriangleInMesh intersectionInfo;
				// TODO: add the information about the intersection
				
				// Add this intersection event to the vector
				vec_RayTriangle_Collisions.push_back(intersectionInfo);
			}

		}//for (std::vector<sTriangle>::iterator itTri

	}//for (std::vector< sTriangleMesh*>::iterator itMesh

	// Any collisions? 
	if (vec_RayTriangle_Collisions.empty())
	{
		// No
		return false;
	}

	// There were collisions
	return true;
}

// This one adds the collision to the vec_RayTriangle_Collisions
void cPhysics::rayCast(glm::vec3 start, glm::vec3 end)
{
	// TODO: 

	return;
}

bool cPhysics::bRay_TriangleCollision(sLine theLine, sTriangle theTri)
{
	// From Christer Ericsson collision detection book
	// == = Section 5.3.4: ============================================================ =

	// Given line pq and ccw triangle abc, return whether line pierces triangle. If
	// so, also return the barycentric coordinates (u,v,w) of the intersection point
	//int IntersectLineTriangle(Point p, Point q, Point a, Point b, Point c,
	//	float& u, float& v, float& w)
	//{
	//	Vector pq = q - p;
	//	Vector pa = a - p;
	//	Vector pb = b - p;
	//	Vector pc = c - p;
	//	// Test if pq is inside the edges bc, ca and ab. Done by testing
	//	// that the signed tetrahedral volumes, computed using scalar triple
	//	// products, are all positive
	//	u = ScalarTriple(pq, pc, pb);
	//	if (u < 0.0f) return 0;
	//	v = ScalarTriple(pq, pa, pc);
	//	if (v < 0.0f) return 0;
	//	w = ScalarTriple(pq, pb, pa);
	//	if (w < 0.0f) return 0;

	//	// Compute the barycentric coordinates (u, v, w) determining the
	//	// intersection point r, r = u*a + v*b + w*c
	//	float denom = 1.0f / (u + v + w);
	//	u *= denom;
	//	v *= denom;
	//	w *= denom; // w = 1.0f - u - v;
	//	return 1;
	//}


	return false;
}


	// Feeney asked chatGPT this:
	// 
	// "give me the triple product of three vectors in C++"
	// 
	// And got this:
//#include <iostream>
//#include <vector>
//	using namespace std;
//
//	// Function to compute the cross product of two 3D vectors
//	vector<int> crossProduct(vector<int> a, vector<int> b) {
//		vector<int> result(3);
//		result[0] = a[1] * b[2] - a[2] * b[1];
//		result[1] = a[2] * b[0] - a[0] * b[2];
//		result[2] = a[0] * b[1] - a[1] * b[0];
//		return result;
//	}
//
//	// Function to compute the dot product of two 3D vectors
//	int dotProduct(vector<int> a, vector<int> b) {
//		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
//	}
//
//	// Function to compute the scalar triple product
//	int scalarTripleProduct(vector<int> a, vector<int> b, vector<int> c) {
//		vector<int> bCrossC = crossProduct(b, c);
//		return dotProduct(a, bCrossC);
//	}
//
//	int main() {
//		vector<int> vecA(3), vecB(3), vecC(3);
//
//		// Input the three 3D vectors
//		cout << "Enter the components of the first vector (x y z): ";
//		cin >> vecA[0] >> vecA[1] >> vecA[2];
//
//		cout << "Enter the components of the second vector (x y z): ";
//		cin >> vecB[0] >> vecB[1] >> vecB[2];
//
//		cout << "Enter the components of the third vector (x y z): ";
//		cin >> vecC[0] >> vecC[1] >> vecC[2];
//
//		// Calculate the scalar triple product
//		int result = scalarTripleProduct(vecA, vecB, vecC);
//
//		// Display the result
//		cout << "The scalar triple product is: " << result << endl;
//
//		return 0;
//	}