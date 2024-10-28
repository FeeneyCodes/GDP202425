#pragma once

#include "iTank.h"
#include <glm/glm.hpp>
#include "sMesh.h"
//
#include "cJetPack.h"
#include "cSheild.h"

class cHoverTank : public iTank
{
public:
	cHoverTank();
	virtual ~cHoverTank();

	void Attack(/*another tank*/);
	virtual glm::vec3 getLocation(void);
	virtual void UpdateTick(double deltaTime);


	sMesh* pTheMesh;

	cJetPack* pTheJetPack;
	cSheild* pShield;

	virtual unsigned int getID(void);

private:
	static unsigned int m_NextID;
	unsigned int m_ID;
};