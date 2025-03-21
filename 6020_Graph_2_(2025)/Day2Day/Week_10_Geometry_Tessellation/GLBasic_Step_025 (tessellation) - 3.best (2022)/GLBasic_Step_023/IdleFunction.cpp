#include "global.h"

#include <iostream>


bool bIsKeyDown( char key )
{
	if( GetAsyncKeyState( key ) & 0x8000 )
	{
		return true;
	}
	// Key isn't down
	return false;
}

void HandleIO( float deltaTime )
{
	bool bCrtlDown =	( (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0 );
	bool bShiftDown =	( (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0 );
	bool bAltDown =		( (GetAsyncKeyState(VK_MENU) & 0x8000) != 0 );

	// Now are "per second"
	static const float PITCHANGLECHANGE_PERSECOND = 25.0f;	// 0.1f;
	static const float YAWANGLECHANGE_PERSECOND = 35.0f;		// 0.1f;
	static const float POSITIONCHANGE_PERSECOND = 10.0f;		//  0.1f;

	float deltaPitchAngleThisFrame = PITCHANGLECHANGE_PERSECOND * deltaTime;
	float deltaYawAngleThisFrame = YAWANGLECHANGE_PERSECOND * deltaTime;
	float deltaPosThisFrame = POSITIONCHANGE_PERSECOND * deltaTime;

	CGameObject* pCamera = ::g_pGameObjectManager->FindGameObjectByFriendlyName("CameraProxy");

	if ( bShiftDown )
	{
		if ( bIsKeyDown( 'W' ) )		// Pitch "down"
		{
			pCamera->adjustOrientationFromEuler( glm::vec3( +deltaPitchAngleThisFrame, 0.0f, 0.0f ), deltaTime );
		}
		if ( bIsKeyDown( 'S' ) )		// Pitch "up"
		{
			pCamera->adjustOrientationFromEuler( glm::vec3( -deltaPitchAngleThisFrame, 0.0f, 0.0f ), deltaTime );
		}
		if ( bIsKeyDown( 'A' ) )		// Yaw "left"
		{
			pCamera->adjustOrientationFromEuler( glm::vec3( 0.0f, +deltaYawAngleThisFrame, 0.0f ), deltaTime );
		}
		if ( bIsKeyDown( 'D' ) )		// Yaw "right"
		{
			pCamera->adjustOrientationFromEuler( glm::vec3( 0.0f, -deltaYawAngleThisFrame, 0.0f ), deltaTime );
		}
		// The up vector for our camera isn't actually changing in our look at.... so this is off
		//if ( bIsKeyDown( 'Q' ) )		// "roll" or "bank" left  (like when a plane turns left)
		//{
		//	pCamera->adjustOrientationFromEuler( glm::vec3( 0.0f, 0.0f, +deltaPitchAngleThisFrame ), deltaTime );
		//}
		//if ( bIsKeyDown( 'E' ) )			// "roll" or "bank" right
		//{
		//	pCamera->adjustOrientationFromEuler( glm::vec3( 0.0f, 0.0f, -deltaPitchAngleThisFrame ), deltaTime );
		//}
	}
	else
	{	// Shift is UP  (lower case)
		//// Upper case moves object (rather than rotate)
		if ( bIsKeyDown( 'W' ) )		// Move "forward" (+ve in Z)
		{
			pCamera->updatePositionBasedOnOrientation( glm::vec3( 0.0f, 0.0f, +POSITIONCHANGE_PERSECOND ), deltaTime );
		}
		if ( bIsKeyDown( 'S' ) )		// Move "backward" (-ve in Z)
		{
			pCamera->updatePositionBasedOnOrientation( glm::vec3( 0.0f, 0.0f, -POSITIONCHANGE_PERSECOND ), deltaTime );
		}

		if ( bIsKeyDown( 'A' ) )	// Move "left" (-ve in X)
		{
			pCamera->updatePositionBasedOnOrientation( glm::vec3( +POSITIONCHANGE_PERSECOND, 0.0f, 0.0f ), deltaTime );
		}
		if ( bIsKeyDown( 'D' ) )	// Move "right" (+ve in X)
		{
			pCamera->updatePositionBasedOnOrientation( glm::vec3( -POSITIONCHANGE_PERSECOND, 0.0f, 0.0f ), deltaTime );
		}

		if ( bIsKeyDown( 'Q' ) )	// Move "down" ( -ve in Y )
		{
			pCamera->updatePositionBasedOnOrientation( glm::vec3( 0.0f, -POSITIONCHANGE_PERSECOND, 0.0f ), deltaTime );
		}
		if ( bIsKeyDown( 'E' ) )	// Move "up" ( +ve in Y )
		{
			pCamera->updatePositionBasedOnOrientation( glm::vec3( 0.0f, +POSITIONCHANGE_PERSECOND, 0.0f ), deltaTime );
		}
	}//if ( bShiftDown )


	if ( bIsKeyDown( VK_UP ) )
	{
		pCamera->position.y += deltaPosThisFrame;		
	}
	if( bIsKeyDown( VK_DOWN ) )
	{
		pCamera->position.y -= deltaPosThisFrame;		
	}
	if( bIsKeyDown( VK_LEFT ) )
	{
		pCamera->position.x += deltaPosThisFrame;		
	}
	if( bIsKeyDown( VK_RIGHT ) )
	{
		pCamera->position.x -= deltaPosThisFrame;
	}

	if( bIsKeyDown( VK_PRIOR ) )
	{
		pCamera->position.z += deltaPosThisFrame;
	}
	if( bIsKeyDown( VK_NEXT ) )
	{
		pCamera->position.z -= deltaPosThisFrame;
	}


	return;
}

void IdleFunction(void)
{
	float deltaTime = ::g_pIOTimer->GetElapsedSecondsAverage(true);

	static const float MAXFRAMEDELTATIME = 0.02f;		// 20 ms max
	
	if ( deltaTime > MAXFRAMEDELTATIME )
	{
		deltaTime = MAXFRAMEDELTATIME;
	}

	HandleIO(deltaTime);

	// Match the object we've called "Light00" with the actual light 0
	CGameObject* pLight0 = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "Light0" );
	if ( pLight0 != 0 )
	{	// Object exists
		pLight0->position = ::g_TheLights[::g_selectedLightID].position;
		// "Ball" mesh edge is at the 50% "brightness" mark
		// Ambient level is 0.2, so let's say that's "black" (no effect)
		//pLight0->scale = ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.2f );

		CNameValuePair scaleForSphere75( "75%", ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.75f ) );
		CNameValuePair scaleForSphere50( "50%", ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.50f ) );
		CNameValuePair scaleForSphere25( "25%", ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.25f ) );
		CNameValuePair scaleForSphere01( "01%", ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.01f ) );

		CNameValuePair command( "SetSpheres" );
		command.AddChild( scaleForSphere75 ); // "75%"
		command.AddChild( scaleForSphere50 ); // "50%"
		command.AddChild( scaleForSphere25 ); // "25%"
		command.AddChild( scaleForSphere01 ); // "01%"


		//CNameValuePair command( "SetSpheres", scaleForSphere75, scaleForSphere50, scaleForSphere25, scaleForSphere01 );

		pLight0->ReceiveMessage( command );
		//pLight0->Set75PercentSphere( ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.75f ) );
		//pLight0->Set50PercentSphere( ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.50f ) );
		//pLight0->Set25PercentSphere( ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.25f ) );
		//pLight0->Set01PercentSphere( ::g_TheLights[::g_selectedLightID].calcApproxDistFromAtten( 0.01f ) );
	}

	// Update the light to where the debug ball is
	CGameObject* pLight = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "YellowDebugBall" );
	if ( pLight )
	{
		::g_TheLights[::g_selectedLightID].position = pLight->position;
	}

	// Move the skybox to the same location as the camera
	// so we are always in the centre of the skybox
	CGameObject* pSkyBox = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "SkyBox" );
	if ( pSkyBox )
	{
		pSkyBox->position.x = ::g_cameraEyeX;
		pSkyBox->position.y = ::g_cameraEyeY;
		pSkyBox->position.z = ::g_cameraEyeZ;
	}

	// Align camera to proxy object
	CGameObject* pCameraProxyObject = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "CameraProxy" );

	::g_cameraEyeX = pCameraProxyObject->position.x;
	::g_cameraEyeY = pCameraProxyObject->position.y;
	::g_cameraEyeZ = pCameraProxyObject->position.z;

	glm::vec3 cameraTarget = pCameraProxyObject->getTarget( glm::vec3( 0.0f, 0.0f, 1.0f ) );
	::g_cameraAtX = cameraTarget.x;
	::g_cameraAtY = cameraTarget.y;
	::g_cameraAtZ = cameraTarget.z;

	std::stringstream ss;
	//ss << "Camera: " << ::g_cameraEyeX << ", " << ::g_cameraEyeY << ", " << ::g_cameraEyeZ;

	ss << "F1(texture), F2(wireframe), (Shift=+) Tess: Dist(F3)=" << ::g_tessellationDistance 
		<< " Ratio(outer:F4)=" << ::g_tessellationRatioOuter
		<< " Ratio(inner:F5)=" << ::g_tessellationRatioInner
		<< " Only Edges(F6) = " << (::g_bTessellateOnlyEdges ? "ON" : "OFF" )
		<< " Edge DotProd Thres(F7)=" << ::g_tessellationEdgeDotProductThreshold
		<< " Normal Prodtrude HACK(F8)=" << ::g_tessNormProtrudeValue;




	glutSetWindowTitle( ss.str().c_str() );

	glutPostRedisplay();

	return;
}

//