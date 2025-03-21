#ifndef _IMediator_HG_
#define _IMediator_HG_

// CGameObjects will use this interface to "call back"
//	the mediator

#include "CNameValuePair.h"

class IMediator
{
public:
	virtual ~IMediator() {};
	virtual void SendMessageToMediator( CNameValuePair theMessage ) = 0;
};

#endif