#include "cPhysics.h"

//struct sPoint: 
//  glm::vec3 position;
//struct sEdge : 
//	sPoint* pointA;
//	sPoint* pointB;
//	float restLength;
//
//std::vector< sPoint > vecPoints;
//std::vector< sEdge > vecEdges;

bool cPhysics::createSoftBodyFromMesh(std::string friendlyName, sModelDrawInfo* pTheMesh)
{
	cSoftBody_Verlet* pSoftBody = new cSoftBody_Verlet();

	// Go through the vertices and add them as points to the vector of points
	for (unsigned int index = 0; index != pTheMesh->numberOfVertices; index++)
	{
		cSoftBody_Verlet::sPoint newPoint;
		newPoint.position.x = pTheMesh->pVertices[index].x;
		newPoint.position.y = pTheMesh->pVertices[index].y;
		newPoint.position.z = pTheMesh->pVertices[index].z;
		pSoftBody->vecPoints.push_back(newPoint);
	}

	for (unsigned int index = 0; index != pTheMesh->numberOfIndices; index += 3)
	{
		// The indices are in multiples of 3:
		// In the file: 3 950 2582 2583 
		// But they are "unrolled" into a 1D array

		// There are 3 edges to this triangle
		unsigned int vert0index = pTheMesh->pIndices[index + 0];
		unsigned int vert1index = pTheMesh->pIndices[index + 1];
		unsigned int vert2index = pTheMesh->pIndices[index + 2];

		// Edge 0 --> vert0 to vert1
		cSoftBody_Verlet::sEdge edge0;
		edge0.pointA = &(pSoftBody->vecPoints[vert0index]);
		edge0.vertAindex = vert0index;

		edge0.pointB = &(pSoftBody->vecPoints[vert1index]);
		edge0.vertAindex = vert1index;

		// Calcualte rest length between these vertices
		edge0.restLength = glm::distance(edge0.pointA->position, edge0.pointB->position);



		// Edge 1 --> vert1 to vert2
		cSoftBody_Verlet::sEdge edge1;
		edge1.pointA = &(pSoftBody->vecPoints[vert1index]);
		edge1.vertAindex = vert1index;
		edge1.pointB = &(pSoftBody->vecPoints[vert2index]);
		edge1.vertBindex = vert2index;

		// Calcualte rest length between these vertices
		edge1.restLength = glm::distance(edge1.pointA->position, edge1.pointB->position);



		// Edge 2 --> vert2 to vert0
		cSoftBody_Verlet::sEdge edge2;
		edge2.pointA = &(pSoftBody->vecPoints[vert2index]);
		edge2.vertAindex = vert2index;
		edge2.pointB = &(pSoftBody->vecPoints[vert0index]);
		edge2.vertBindex = vert0index;

		edge2.restLength = glm::distance(edge2.pointA->position, edge2.pointB->position);

		pSoftBody->vecEdges.push_back(edge0);
		pSoftBody->vecEdges.push_back(edge1);
		pSoftBody->vecEdges.push_back(edge2);
	}

	// Add this soft body to the map of soft bodies
	this->m_MapSoftBodiesByName[friendlyName] = pSoftBody;

	return true;
}
