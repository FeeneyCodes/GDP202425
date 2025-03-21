#include "CGameObjectManager.h"


// Message: 
// "Name" = "SendMessage"
// "Value" is the ID (friendly name) of target object

// Name = "FindAllTypeNearby"

void CGameObjectManager::SendMessageToMediator( CNameValuePair theMessage )
{
	// TODO: make awesome code, later
	if ( theMessage.name == "SendMessage" )
	{
		// Find this one... theMessage.sValue 
		CGameObject* pTarget = 
			this->FindGameObjectByFriendlyName( theMessage.sValue );
		if ( pTarget != 0 )
		{	// Found it!
			// Do something...
			//CNameValuePair command;
			//command.name = "FlyAway";
			//pTarget->ReceiveMessage( command );
			pTarget->ReceiveMessage( theMessage.vecChildNVPairs[0] );
		}
	}// if ( theMessage.name == "SendMessage" )
	if ( theMessage.name == "KillMe")
	{

	}


	return;
}