#include "global.h"		// For all the GLUT stufff
#include <iostream>
#include "CHRTimer.h"

// HACK: should be somewhere else, maybe
CHRTimer pKeyboardTimer;

void glutKeyboard_callback(unsigned char key, int x, int y)
{
	float deltaTime = pKeyboardTimer.GetElapsedSeconds();
	static const float MINTIMESTEP = 0.01f;	// 10 ms;
	if ( deltaTime >= MINTIMESTEP )	
	{
		deltaTime = MINTIMESTEP;
	}
	pKeyboardTimer.Reset();
	pKeyboardTimer.Start();


	static const float LIGHTMOVESPEED = 0.1f;

	//CGameObject* pBunny = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "BugsBunny" );
	CGameObject* pLight = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "YellowDebugBall" );

	CGameObject* pMig = ::g_pGameObjectManager->FindGameObjectByFriendlyName("Vladimir");

	CGameObject* pCamera = ::g_pGameObjectManager->FindGameObjectByFriendlyName("CameraProxy");

	// Now are "per second"
	//static const float ANGLECHANGE = 15.0f;		// 0.1f;
	//static const float POSITIONCHANGE = 20.0f;	//  0.1f;

//	std::cout << "Orientation Q: " 
//		<< pMig->qOrientation.x << ", " 
//		<< pMig->qOrientation.y << ", " 
//		<< pMig->qOrientation.z << ", "  
//		<< pMig->qOrientation.w << std::endl;
////		<< pMig->preRotation.x << ", " << pMig->preRotation.y << ", " << pMig->preRotation.z << std::endl;
//
//	glm::vec3 EulerAngles = glm::eulerAngles( pMig->qOrientation );
//	EulerAngles = glm::degrees( EulerAngles );
//	std::cout << "EulerXYZ: " 
//		<< EulerAngles.x << ", "
//		<< EulerAngles.y << ", "
//		<< EulerAngles.z << std::endl;

	switch( key )
	{
	//case 13:	// Enter key
	//	break;
	case 27:	// Esc key
		glutLeaveMainLoop();
		break;
	case 'a':
		break;
	case 'A':
		break;

	default:
		// Only because you "should" have a default in every switch
		break;
	}

	//// Update light to be where the bunny is
	//::g_TheLights[::g_selectedLightID].position = pLight->position;


	return;
}

void glutSpecialKey_callback( int key, int x, int y )
{
	int modifiers = glutGetModifiers();
	bool bShiftDown = ( modifiers & GLUT_ACTIVE_SHIFT ) == GLUT_ACTIVE_SHIFT;


	CGameObject* pGround = ::g_pGameObjectManager->FindGameObjectByFriendlyName( "Ground" );


	switch ( key )
	{
	case GLUT_KEY_F1:
		if ( bShiftDown )	{	pGround->textureName0 = "Green lush grass texture.bmp";	}
		else				{	pGround->textureName0 = "";	}
		break;
	case GLUT_KEY_F2:
		if ( bShiftDown )	{	pGround->bIsWireframe = true;	}
		else				{	pGround->bIsWireframe = false;	}
		break;
	case GLUT_KEY_F3:
		if ( bShiftDown )
		{
			::g_tessellationDistance *= 1.01f;
		}
		else
		{
			::g_tessellationDistance *= 0.99f;
		}
		break;
	case GLUT_KEY_F4:
		if ( bShiftDown )
		{
			::g_tessellationRatioOuter *= 1.01f;
		}
		else 
		{
			::g_tessellationRatioOuter *= 0.99f;
			if ( ::g_tessellationRatioOuter < 1.0f )
			{
				::g_tessellationRatioOuter = 1.0f;
			}
		}
		break;
	case GLUT_KEY_F5:
		if ( bShiftDown )
		{
			::g_tessellationRatioInner *= 1.01f;
		}
		else 
		{
			::g_tessellationRatioInner *= 0.99f;
			if ( ::g_tessellationRatioInner < 1.0f )
			{
				::g_tessellationRatioInner = 1.0f;
			}
		}
		break;
	case GLUT_KEY_F6:
		if ( bShiftDown )	{	g_bTessellateOnlyEdges = true;	}
		else				{	g_bTessellateOnlyEdges = false;	}
		break;
	case GLUT_KEY_F7:
		if ( bShiftDown )
		{
			::g_tessellationEdgeDotProductThreshold += 0.01f;
		}
		else 
		{
			::g_tessellationEdgeDotProductThreshold -= 0.01f;
			if ( ::g_tessellationEdgeDotProductThreshold > 0.99f )	{ ::g_tessellationEdgeDotProductThreshold = 0.99f; }
			if ( ::g_tessellationEdgeDotProductThreshold < -0.99f )	{ ::g_tessellationEdgeDotProductThreshold = -0.99f; }
		}
		break;

	case GLUT_KEY_F8:
		// How far the "hack" curvature thing is pushing the triangles out by
		if ( bShiftDown )
		{
			::g_tessNormProtrudeValue += 0.001f;
		}
		else
		{
			::g_tessNormProtrudeValue -= 0.001f;
		}


	}// switch ( key )

	return;
}
