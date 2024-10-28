#pragma once

#include "iTank.h"
#include <glm/glm.hpp>
#include "sMesh.h"

class cSuperTank : public iTank
{
public:
	cSuperTank();
	virtual ~cSuperTank();

	void Attack(/*another tank*/);


	sMesh* pTheMesh;
};