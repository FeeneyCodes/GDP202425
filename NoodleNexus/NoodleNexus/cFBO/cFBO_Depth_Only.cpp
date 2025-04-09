#include "cFBO_Depth_Only.h"

bool cFBO_Depth_Only::init(int width, int height, std::string& error)
{
	this->width = width;
	this->height = height;

	//	glCreateFramebuffers(1, &( this->ID ) );	// GL 4.5		//g_FBO
	glGenFramebuffers(1, &(this->ID));		// GL 3.0
	glBindFramebuffer(GL_FRAMEBUFFER, this->ID);

	//************************************************************
	// NO colour buffer
	//***************************************************************

	// Create the depth buffer (texture)
	glGenTextures(1, &(this->depthTexture_ID));			//g_FBO_depthTexture
	glBindTexture(GL_TEXTURE_2D, this->depthTexture_ID);

	//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, ]

	// Note that, unless you specifically ask for it, the stencil buffer
	// is NOT present... i.e. GL_DEPTH_COMPONENT32F DOESN'T have stencil
	// These are:
	// - GL_DEPTH32F_STENCIL8, which is 32 bit float depth + 8 bit stencil (default with Apple)
	// - GL_DEPTH24_STENCIL8,  which is 24 bit float depth + 8 bit stencil (more common? Apple doesn't have this)
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F,	//GL_DEPTH32F_STENCIL8,
		this->width,		//g_FBO_SizeInPixes
		this->height);

	// Set some texture params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// Fastest sampling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// Fastest sampling
	// Set the edges of the shadow to the maximum depth (which is 1.0f):
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float outOfRangeDepthValue[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, outOfRangeDepthValue);



	glFramebufferTexture(GL_FRAMEBUFFER,
						 GL_DEPTH_ATTACHMENT,
						 this->depthTexture_ID, 0);

	// If it's also got a stencil buffer
	//	glFramebufferTexture(GL_FRAMEBUFFER,
	//		GL_DEPTH_STENCIL_ATTACHMENT,
	//		this->depthTexture_ID, 0);

	// Turn off any read+write to the colour buffer
	//	to let OpenGL know we aren't using it
	// (and it's fine that this FBO doesn't have a colour buffer)
	glDrawBuffer(GL_NONE);	// Won't write to a colour buffer
	glReadBuffer(GL_NONE);	// Won't read from any colour buffers


	// ADD ONE MORE THING...
	bool bFrameBufferIsGoodToGo = true;

	switch (glCheckFramebufferStatus(GL_FRAMEBUFFER))
	{
	case GL_FRAMEBUFFER_COMPLETE:
		bFrameBufferIsGoodToGo = true;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		error = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
		bFrameBufferIsGoodToGo = false;
		break;
		//	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
	case GL_FRAMEBUFFER_UNSUPPORTED:
	default:
		bFrameBufferIsGoodToGo = false;
		break;
	}//switch ( glCheckFramebufferStatus(GL_FRAMEBUFFER) )

	// Point back to default frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return bFrameBufferIsGoodToGo;
}

bool cFBO_Depth_Only::shutdown(void)
{
	glDeleteTextures(1, &(this->depthTexture_ID));

	glDeleteFramebuffers(1, &(this->ID));

	return true;
}

// Calls shutdown(), then init()
bool cFBO_Depth_Only::reset(int width, int height, std::string& error)
{
	if (!this->shutdown())
	{
		error = "Could not shutdown";
		return false;
	}

	return this->init(width, height, error);
}

void cFBO_Depth_Only::clearDepthBuffer(void)
{
	glViewport(0, 0, this->width, this->height);

	GLfloat one = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &one);		// Depth is normalized 0.0 to 1.0f

	// If buffer is GL_STENCIL, drawbuffer must be zero, and value points to a 
	//  single value to clear the stencil buffer to. Masking is performed in the 
	//  same fashion as for glClearStencil. Only the *iv forms of these commands 
	//  should be used to clear stencil buffers; be used to clear stencil buffers; 
	//  other forms do not accept a buffer of GL_STENCIL.
	// 
	glStencilMask(0xFF);

	{	// Clear stencil
		//GLint intZero = 0;
		//glClearBufferiv(GL_STENCIL, 0, &intZero );
		glClearBufferfi(GL_DEPTH_STENCIL,
			0,		// Must be zero
			1.0f,	// Clear value for depth
			0);	// Clear value for stencil
	}

	return;
}