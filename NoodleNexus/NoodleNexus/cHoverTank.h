#pragma once

#include "iTank.h"
#include <glm/glm.hpp>
#include "sMesh.h"

class cHoverTank : public iTank
{
public:
	cHoverTank();
	virtual ~cHoverTank();

	void Attack(/*another tank*/);


	sMesh* pTheMesh;
};