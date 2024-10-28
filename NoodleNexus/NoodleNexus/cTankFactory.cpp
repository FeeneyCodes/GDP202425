#include "cTankFactory.h"

// HERE (in the cpp or implementation) is where the #includes
// for the specific types go

#include "cTank.h"
#include "cSuperTank.h"
#include "cHoverTank.h"

//const std::string TANK_FACTORY_REGULAR_TANK = "Regular Tank";
//const std::string TANK_FACTORY_SUPER_TANK = "Super Tank";

// Returns NULL if unknown type
iTank* cTankFactory::CreateATank(std::string tankType)
{

	if (tankType == "Regular Tank")
	{
		return new cTank();
	}
	if (tankType == "Super Tank")
	{
		return new cSuperTank();
	}
	if (tankType == "Hover Tank")
	{
		return new cHoverTank();
	}

	// Unknown type
	return NULL;	// or 0 or nullptr
}

void cTankFactory::GetTankTypes(std::vector<std::string>& vecTankTypeList)
{
	// I know how to make these...
	vecTankTypeList.push_back("Regular Tank");
	vecTankTypeList.push_back("Super Tank");
	vecTankTypeList.push_back("Hover Tank");
	// 
	vecTankTypeList.push_back("LASER Tank");
	return;
}
	
