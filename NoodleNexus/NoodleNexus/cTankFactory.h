#pragma once

// ONLY include the interface
// NEVER EVER the specific derrived types
#include "iTank.h"
#include <string>
#include <vector>

class cTankFactory
{
public:
	// Factory method
	// Always pass a known type, not an enum, etc.
	// Returns NULL if unknown type
	iTank* CreateATank(std::string tankType);

	// Returns false if unknown type
//	bool CreateATank(std::string tankType, iTank*& pNewTank);
	// Etc.

	void GetTankTypes(std::vector<std::string>& vecTankTypeList);
};
