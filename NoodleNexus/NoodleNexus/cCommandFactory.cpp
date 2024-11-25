#include "cCommandFactory.h"

// Abstract factory: includes specific classes here
// NEVER in the header
#include "cMoveRelativeTime.h"
#include "cFollowObject_A.h"

cCommandFactory::cCommandFactory()
{
}

// If the command is NOT known, will return NULL
iCommand* cCommandFactory::pCreateCommandObject(
	std::string command,
	std::vector< std::string > vecDetails)
{
	// Determine which commands I want
	if (command == "Move Relative Time")
	{
		iCommand* pMoveCommand = new cMoveRelativeTime();
	

		return pMoveCommand;
	}
	if (command == "Follow Object, offset & max velocity")
	{
		iCommand* pFollow = new cFollowObject_A();


		return pFollow;
	}



	// Don't know that command
	return NULL;
}
