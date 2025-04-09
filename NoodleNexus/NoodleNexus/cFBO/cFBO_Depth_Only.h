#ifndef _cFBO_Depth_Only_HG_
#define _cFBO_Depth_Only_HG_

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class cFBO_Depth_Only
{
public:
	cFBO_Depth_Only() :
		ID(0),
		depthTexture_ID(0),
		width(-1), height(-1) {
	};

	GLuint ID;						// = 0;
	// NO colour buffer
	GLuint depthTexture_ID;		// = 0;
	GLint width;		// = 512 the WIDTH of the framebuffer, in pixels;
	GLint height;

	// Inits the FBP
	bool init(int width, int height, std::string& error);
	bool shutdown(void);

	// Calls shutdown(), then init()
	bool reset(int width, int height, std::string& error);

	void clearDepthBuffer(void);

};

#endif
