#include "CLight.h"

CLight::CLight()
{
	return;
}

CLight::~CLight()
{
	return;
}


// Child #1 is the 75%
void CLight::Set75PercentSphere( float distance )
{
	this->vec_pChildObjects[0]->scale = distance;
	return;
}

// Child #2 is the 50% 
void CLight::Set50PercentSphere( float distance )
{
	this->vec_pChildObjects[1]->scale = distance;
	return;
}

// Child #3 is the 25%
void CLight::Set25PercentSphere( float distance )
{
	this->vec_pChildObjects[2]->scale = distance;
	return;
}

// Outer sphere is the 1% light sphere
void CLight::Set01PercentSphere( float distance )
{
	this->vec_pChildObjects[3]->scale = distance;
	return;
}

// One method to rule them all!!!
void CLight::ReceiveMessage( CNameValuePair command )
{
	// There could be a bunch of message that I get...
	if ( command.name == "SetSpheres" )
	{
		CNameValuePair sphere75;
		CNameValuePair sphere50;
		CNameValuePair sphere25;
		CNameValuePair sphere01;
		if ( command.ScanChildrenForName( "75%", sphere75 ) )
		{
			this->Set75PercentSphere( sphere75.fvec4Value.x );
		}
		if ( command.ScanChildrenForName( "50%", sphere50 ) )
		{
			this->Set50PercentSphere( sphere50.fvec4Value.x );
		}
		if ( command.ScanChildrenForName( "25%", sphere25 ) )
		{
			this->Set25PercentSphere( sphere25.fvec4Value.x );
		}
		if ( command.ScanChildrenForName( "01%", sphere25 ) )
		{
			this->Set01PercentSphere( sphere01.fvec4Value.x );
		}
	}// if ( NVPair.name == "SetSpheres" )



	return;
}