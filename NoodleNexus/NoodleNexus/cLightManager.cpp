#include "cLightManager.h"


cLightManager::cLightManager()
{

}

void cLightManager::loadUniformLocations(GLuint shaderProgram)
{
	GLint light_00_position_UL = glGetUniformLocation(shaderProgram, "theLights[0].position");
	// and so on...

	return;
}


void cLightManager::updateShaderWithLightInfo(GLuint shaderProgram)
{
	glUniform4f(light_00_position_UL, this->theLights[0].position.x,
		this->theLights[0].position.y,
		this->theLights[0].position.z,
		1.0f);




	return;
}