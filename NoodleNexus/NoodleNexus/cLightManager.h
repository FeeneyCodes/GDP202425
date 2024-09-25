#pragma once

#include "GLCommon.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

class cLightManager
{
public:
    // This is inside our shader
    //struct sLight
    //{
    //    vec4 position;
    //    vec4 diffuse;
    //    vec4 specular;	// rgb = highlight colour, w = power
    //    vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
    //    vec4 direction;	// Spot, directional lights
    //    vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
    //    // 0 = pointlight
    //    // 1 = spot light
    //    // 2 = directional light
    //    vec4 param2;	// x = 0 for off, 1 for on
    //    // yzw are TBD
    //};
    //const int NUMBEROFLIGHTS = 10;
    //uniform sLight theLights[NUMBEROFLIGHTS];

    cLightManager();

    void loadUniformLocations(GLuint shaderProgram);
    void updateShaderWithLightInfo(GLuint shaderProgram);

    // Mirror of what's inside the shader
    struct sLight
    {
        glm::vec4 position;
        glm::vec4 diffuse;
        glm::vec4 specular;	// rgb = highlight colour, w = power
        glm::vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
        glm::vec4 direction;	// Spot, directional lights
        glm::vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
        // 0 = pointlight
        // 1 = spot light
        // 2 = directional light
        glm::vec4 param2;	// x = 0 for off, 1 for on
        // yzw are TBD
    };

    static const int NUMBEROFLIGHTS = 10;
    sLight theLights[NUMBEROFLIGHTS];

    //std::vector<sLight> vecLights;
};

