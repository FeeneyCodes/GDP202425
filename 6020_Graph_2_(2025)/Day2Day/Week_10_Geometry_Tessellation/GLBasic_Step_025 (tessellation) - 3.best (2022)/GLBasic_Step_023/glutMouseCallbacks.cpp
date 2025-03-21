#include "global.h"		// For all the GLUT stufff


static int fg_oldScrollWheelValue = 0;

void glutMouseFunc_callback(int button, int state, int x, int y)
{
	int modifiers = glutGetModifiers();

	// Keyboard state now handled by GetAsync()
	//::g_pTheKeyboard->SetGLUTModifiers(modifiers);

	::g_pTheMouse->UpdateStateFromGLUT( button, state, x, y, modifiers);

	if ( fg_oldScrollWheelValue != ::g_pTheMouse->getScrollWheel() )
	{
		float deltaScroll = static_cast<float>( fg_oldScrollWheelValue - g_pTheMouse->getScrollWheel() );

		//g_theCamera.z += ( g_theCamera.moveSpeed * deltaScroll );
		//g_theCamera.Move( 0.1f * deltaScroll );

		fg_oldScrollWheelValue = ::g_pTheMouse->getScrollWheel();
	}
	

	return;
}


// The motion callback for a window is called when the mouse moves within the window while one or more mouse buttons are pressed.
void glutMotionFunc_callback(int x, int y)
{
	int modifiers = glutGetModifiers();

	// Keyboard state now handled by GetAsync()
	//::g_pTheKeyboard->SetGLUTModifiers(modifiers);

	::g_pTheMouse->UpdateStateFromGLUT( x, y, modifiers );

	return;
}


// The passive motion callback for a window is called when the mouse moves within the window while no mouse buttons are pressed.
void glutPassiveMotionFunc_callback(int x, int y)
{
	int modifiers = glutGetModifiers();

	// Keyboard state now handled by GetAsync()
	//::g_pTheKeyboard->SetGLUTModifiers(modifiers);

	::g_pTheMouse->UpdateStateFromGLUT( x, y, modifiers );

	return;
}
