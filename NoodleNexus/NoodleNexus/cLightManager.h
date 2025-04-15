#pragma once

#include "GLCommon.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <string>  

// Added a "depth only" shadow map FBO
#include "cFBO/cFBO_Depth_Only.h"

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
    void updateShaderWithLightInfo(void);

    // Mirror of what's inside the shader
    struct sLight
    {
        glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        // rgb = highlight colour, w = power
        glm::vec4 specular = glm::vec4(1.0f, 1.0f, 1.0f, 10.0f);
        // x = constant, y = linear, z = quadratic, w = DistanceCutOff
        glm::vec4 atten = glm::vec4(1.0f, 1.0f, 1.0f, FLT_MAX);
        // For: spot or directional lights
        glm::vec4 direction = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);    // Pointing along z?
        // x = lightType
        //     0 = pointlight
        //     1 = spot light
        //     2 = directional light
        // y = inner angle, z = outer angle, 
        // w = TBD
        glm::vec4 param1 = glm::vec4(0.0f /*pointlight*/, 0.0f, 0.0f, 1.0f);	
        // x = 0 for off, 1 for on
        // y, z, and w: TBD
        glm::vec4 param2 = glm::vec4(0.0f /*off*/, 0.0f, 0.0f, 1.0f);	
        // x : shadow info: 0 = none (light doesn't cast shadow)
        //                  1 = 2D (perspective), 
        //                  2 = cubeMap (persepective)
        // y : shadow sampler ID (integer)
        // z : near plane
        // w : far plane        
        glm::vec4 shadowInfo = glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);

        glm::mat3 lightSpaceShadowMatrix = glm::mat3(1.0f);

        enum eLightType
        {
            POINT_LIGHT = 0,
            SPOT_LIGHT = 1,
            DIRECTIONAL_LIGHT = 2
        };
        enum eShadowType
        {
            NO_SHADOW = 0,
            PERSPECTIVE_2D = 1,
            PERSPECTIVE_CUBE = 2
        };


        // Added a shadow FBO
        cFBO_Depth_Only* pShadowMap = NULL;

        void setLinearAtten(float newLinear)
        {
            this->atten.y = newLinear;
        }
        void setQuadraticAtten(float newQuad)
        {
            this->atten.z = newQuad;
        }
        void TurnOn(void)
        {
            this->param2.x = 1.0f;
        }
        void TurnOff(void)
        {
            this->param2.x = 0.0f;
        }

        // The uniform locations of >this< light
        GLint position_UL = -1;
        GLint diffuse_UL = -1;
        GLint specular_UL = -1;
        GLint atten_UL = -1;
        GLint direction_UL = -1;
        GLint param1_UL = -1;
        GLint param2_UL = -1;
        GLint shadowInfo_UL = -1;
        GLint lightSpaceShadowMatrix_UL = -1;

        std::string getState(void);
        bool loadState(std::string stateString);
    };

    static const int NUMBEROFLIGHTS = 10;
    sLight theLights[NUMBEROFLIGHTS];


    //std::vector<sLight> vecLights;
};

