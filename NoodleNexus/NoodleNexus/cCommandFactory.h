#pragma once

// This recieves a command in the form of a string or JSON or NV pair
//	or whatever (something type that is known)
// 
// Returns the specific command object

// Only has the iCommand interface
#include "iCommand.h"
#include <string>
#include <vector>

class cCommandFactory
{
public:
	cCommandFactory();

	// If the command is NOT known, will return NULL
	iCommand* pCreateCommandObject(std::string command, 
		                           std::vector< std::string > vecDetails);

	// You could have this return a list of commands,
	// or you could document this outside

};