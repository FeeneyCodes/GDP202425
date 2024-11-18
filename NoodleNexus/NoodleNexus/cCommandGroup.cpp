#include "cCommandGroup.h"

cCommandGroup::cCommandGroup()
{
	// point the iterator to the begining of the serial vector
	// (which is also the end() if there aren't any commands
	this->itCurSerialCommand = this->m_vecSerialCommands.begin();
}

void cCommandGroup::addSerial(iCommand* pNewSerialCommand)
{
	this->m_vecSerialCommands.push_back(pNewSerialCommand);
	return;
}

void cCommandGroup::addParallel(iCommand* pNewParallelCommand)
{
	this->m_vecParallelCommands.push_back(pNewParallelCommand);
	return;
}


void cCommandGroup::OnStart(void)
{
	// TODO: 
	return;
}

void cCommandGroup::Update(double deltaTime)
{
	// If the parallel commands are NOT done, call update
	for (iCommand* pCurPC : this->m_vecParallelCommands)
	{
		if ( ! pCurPC->isFinished())
		{
			pCurPC->Update(deltaTime);
		}
	}
	//
	if (this->itCurSerialCommand != this->m_vecSerialCommands.end())
	{
		// Is this one done?
		if ( ! (*this->itCurSerialCommand)->isFinished() )
		{
			// Call update
			(*this->itCurSerialCommand)->Update(deltaTime);
		}
		else
		{
			// Move to the next command
			this->itCurSerialCommand++;
		}
	}

	return;
}
bool cCommandGroup::isFinished(void)
{
	// All parallel commands are done when all the commands in vector reutrn isFinished
	for (iCommand* pCurPC : this->m_vecParallelCommands)
	{
		if (!pCurPC->isFinished())
		{
			// One of these ISN'T done
			return false;
		}
	}

	// Serial: is the iterator pointing to the end of the vector?
	if (this->itCurSerialCommand != this->m_vecSerialCommands.end())
	{
		// No, so there are still active serial commands
		return false;
	}

	// every command is done
	return true;
}

void cCommandGroup::OnFinished(void)
{
	// TODO: 
	return;
}