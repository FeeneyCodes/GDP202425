#ifndef _CLight_HG_
#define _CLight_HG_

// this will have four concentric spheres at different 
// cut off "brightness"
// * 75%
// * 50%
// * 25%
// * 0.1% (zero)

#include "CGameObject.h"
class CLight : public CGameObject
{
public:
	CLight();
	virtual ~CLight();

	// This is from the CGameObject class
	virtual void ReceiveMessage( CNameValuePair NVPair );


	// These are specific to ME!!
	void Set75PercentSphere( float distance );
	void Set50PercentSphere( float distance );
	void Set25PercentSphere( float distance );
	void Set01PercentSphere( float distance );
};

#endif