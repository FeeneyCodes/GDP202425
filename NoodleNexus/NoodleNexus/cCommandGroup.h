#pragma once

#include "iCommand.h"
#include <vector>

class cCommandGroup : public iCommand
{
public:
	cCommandGroup();
	void addSerial(iCommand* pNewSerialCommand);
	void addParallel(iCommand* pNewSepNewParallelCommandrialCommand);

	// From the iCommand interface
	virtual void OnStart(void);
	virtual void Update(double deltaTime);
	virtual bool isFinished(void);
	virtual void OnFinished(void);

private:
	std::vector< iCommand* > m_vecSerialCommands;
//	std::vector< iCommand* >::iterator itCurSerialCommand; // = begining 

	std::vector< iCommand* > m_vecParallelCommands;
};