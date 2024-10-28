#pragma once

#include "iTank.h"
#include <glm/glm.hpp>
#include "sMesh.h"
//
#include "cSheild.h"
#include "cRailGun.h"

class cSuperTank : public iTank
{
public:
	cSuperTank();
	virtual ~cSuperTank();

	void Attack(/*another tank*/);
	virtual glm::vec3 getLocation(void);
	virtual void UpdateTick(double deltaTime);


	sMesh* pTheMesh;

	// Now with 2 shields
	cSheild* pTheShield[2];
	cRailGun* pTheRailGun;

	virtual unsigned int getID(void);

private:
	static unsigned int m_NextID;
	unsigned int m_ID;
};