#pragma once

#include "iTank.h"
#include <glm/glm.hpp>
#include "sMesh.h"

// 
#include "cSheild.h"

class cTank : public iTank
{
public:
	cTank();
	virtual ~cTank();

	void Attack(/*another tank*/);
	virtual glm::vec3 getLocation(void);
	virtual void UpdateTick(double deltaTime);


	sMesh* pTheMesh;

	cSheild* pTheShield;

	virtual unsigned int getID(void);

	float health;

private:
	static unsigned int m_NextID;
	unsigned int m_ID;

};