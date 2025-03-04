#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <string>

//void fncPhysXWraper(std::string theMessage);

#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Forward declare for pointer to implementation
//class cPhysXWrap_Imp;


//cPhysicsObjectTypes

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <map>
#include <string>


class cPhysicsObjectTypes
{
public:
	enum eShapeType
	{
		BOX,		// Params: "half-extents": x,y,z 

		SPHERE,		// Params: "radius": x

		CAPSULE,
		MESH,
		// ...etc.

		UNKNOWN
	};

	eShapeType shapeType = UNKNOWN;

	// Orientation of the object
	glm::mat4 matModel = glm::mat4(1.0f);

	std::map< std::string /*param name*/, glm::vec4 /*value*/ > map_ParamToValue;

};



class cPhysXWraper
{
public:
	cPhysXWraper();
	~cPhysXWraper();

	void initPhysics(bool interactive, std::string PVD_Host_Address = "127.0.0.1");
	void cleanupPhysics(bool interactive);

	void AddBox(std::string name, glm::vec3 halfExtents, glm::vec3 position, glm::vec4 EulerOrientation, float mass);
	void AddSphere(std::string name, float radius, glm::vec3 position, glm::vec4 EulerOrientation, float mass);
	void AddCapsule(std::string name, glm::vec3 position, glm::vec4 EulerOrientation, float mass);


	void update(void);

	void getSceneActors(std::vector<cPhysicsObjectTypes>& vecPhysActors);


	// HACK: Remove this later
//	void HACK_ShootBall(void);

private:
	//	cPhysXWrap_Imp* m_pImp = nullptr;
};
