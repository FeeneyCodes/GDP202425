#pragma once

// This is the 3D drawing information
//	to draw a single mesh (single PLY file)

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <string>

struct sMesh
{
	sMesh();
	std::string modelFileName;			// "bunny.ply"
	std::string uniqueFriendlyName;		// "Fred", "Ali", "Bunny_007"

	// Stores the mesh we are drawing at a certain distance
	struct sLODInfo
	{
		sLODInfo(std::string _modelName, float _maxDistance, unsigned int _numTris)
		{
			this->modelName = _modelName;
			this->maxDistance = _maxDistance;
			this->numTris = _numTris;
		}
		std::string modelName = "";
		float maxDistance = FLT_MAX;
		unsigned int numTris = 0;	// This is for debug triangle count info
	};
	// The idea is that if this vector has anything in it, then
	//	we will use this vector to find the mesh to draw,
	//	otherwise we'll just use the modelFileName.
	//
	// NOTE: These are listed from closest to farthest
	// So that we can scan through the vector until we are "far enough"
	std::vector<sLODInfo> vecLODInfos;


//	glm::mat4 matModel;
	glm::vec3 positionXYZ;
//
	glm::vec3 rotationEulerXYZ;		// 90 degrees around the x axis

//	void setRotationEuler(glm::vec3 newRotation);
//	void adjustRotationEuler(glm::vec3 newDeltaRotation);
//	glm::mat4 matRotation;

	void setRotationEuler(glm::vec3 newRotation);
	void adjustRotationEuler(glm::vec3 newDeltaRotation);
	glm::quat qRotation;
	
	glm::vec3 getEulerFromQuaternion(void);



	float uniformScale = 1.0f;				// Same for each axis

	// These two matrices are going to be used before 
	//	and after the transformations above
	//
	// "pre" moves the object to the local origin we want
	glm::mat4 matPreParentRelative = glm::mat4(1.0f);
	// "post" moves it back to where it's supposed to be 
	//	relative to the parent
	glm::mat4 matPostParentRelative = glm::mat4(1.0f);

	// This is the model matrix of the last time this was rendered
	glm::mat4 matModel_LastCalculated = glm::mat4(1.0f);

	glm::mat4 calcLocalMatModel(void);

	glm::vec4 objectColourRGBA;		// 0 - 1.0 
	// If true, it uses the colour above
	bool bOverrideObjectColour = true;

	bool bIsWireframe = false;
	bool bIsVisible = true;
	bool bDoNotLight = false;

	// unique ID is read only
	unsigned int getUniqueID(void);
private:
	unsigned int m_uniqueID = 0;
	// 
	static unsigned int m_NextUniqueID;// = 100;
public:

//	std::string textureName;
	static const unsigned int MAX_NUM_TEXTURES = 8;
	std::string textures[MAX_NUM_TEXTURES];
	float blendRatio[MAX_NUM_TEXTURES];

	// If blank we are NOT using a normal map
	std::string normalMap = "";

	// 0.0 = invisible
	// 1.0 = solid 
	float alphaTransparency = 1.0f;

	std::string getState(void);
	bool loadState(std::string newState);

//	sMesh* pChildMeshes[100];
	std::vector< sMesh* > vec_pChildMeshes;

	sMesh* pFindChildMeshByFriendlyName(std::string theNameToFind);


	// I'm going to remove this...
	// //
	// Relative (start where I'm at, then move to endXYZ)
//	void MoveTo(glm::vec3 endXYZ, double timeToMove);
	//
//	void MoveTo(glm::vec3 startXYZ, glm::vec3 endXYZ, double timeToMove);
	//
//	void MoveTo(glm::vec3 startXYZ, glm::vec3 endXYZ, double maxVelocity);

};