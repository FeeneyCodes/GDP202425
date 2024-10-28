#pragma once

#include "iTank.h"
#include <glm/glm.hpp>
#include "sMesh.h"

class cTank : public iTank
{
public:
	cTank();
	virtual ~cTank();

	void Attack(/*another tank*/);


	sMesh* pTheMesh;
};