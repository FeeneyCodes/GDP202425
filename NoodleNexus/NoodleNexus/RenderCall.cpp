#include "GLCommon.h"
#include "sharedThings.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "sMesh.h"
#include "cVAOManager/cVAOManager.h"
#include "cBasicTextureManager/cBasicTextureManager.h"

extern cVAOManager* g_pMeshManager;
extern cBasicTextureManager* g_pTextures;

extern unsigned int g_numLODTrisDrawnThisFrame;

//RenderCall

sMesh* pDebugSphere = NULL;



// Texture set up
void SetUpTextures(sMesh* pCurMesh, GLuint program)
{
    GLuint MissingTexture_ID = ::g_pTextures->getTextureIDFromName("UV_Test_750x750.bmp");



    {
        GLuint textureID_00 = ::g_pTextures->getTextureIDFromName(pCurMesh->textures[0]);
        if (textureID_00 == 0)
        {
            textureID_00 = MissingTexture_ID;
        
        }        
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D, textureID_00);

        //glBindTextureUnit(0, textureID_00);

        GLint texture00_UL = glGetUniformLocation(program, "texture00");
        glUniform1i(texture00_UL, 0);       // <-- Note we use the NUMBER, not the GL_TEXTURE3 here
//        mYProgram.SetUniform("texture00", 0)
    }

    {
        GLuint textureID_01 = ::g_pTextures->getTextureIDFromName(pCurMesh->textures[1]);
        if (textureID_01 == 0)
        {
            textureID_01 = MissingTexture_ID;

        }        
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, textureID_01);
        GLint texture01_UL = glGetUniformLocation(program, "texture01");
        glUniform1i(texture01_UL, 1);       // <-- Note we use the NUMBER, not the GL_TEXTURE3 here
    }

    {
        GLuint textureID_02 = ::g_pTextures->getTextureIDFromName(pCurMesh->textures[2]);
        if (textureID_02 == 0)
        {
            textureID_02 = MissingTexture_ID;

        }
        glActiveTexture(GL_TEXTURE0 + 2);
        glBindTexture(GL_TEXTURE_2D, textureID_02);
        GLint texture02_UL = glGetUniformLocation(program, "texture02");
        glUniform1i(texture02_UL, 2);       // <-- Note we use the NUMBER, not the GL_TEXTURE3 here
    }

    {
        GLuint textureID_03 = ::g_pTextures->getTextureIDFromName(pCurMesh->textures[3]);
        if (textureID_03 == 0)
        {
            textureID_03 = MissingTexture_ID;

        }
        glActiveTexture(GL_TEXTURE0 + 3);
        glBindTexture(GL_TEXTURE_2D, textureID_03);
        GLint texture03_UL = glGetUniformLocation(program, "texture03");
        glUniform1i(texture03_UL, 3);       // <-- Note we use the NUMBER, not the GL_TEXTURE3 here
    }    

    // Now the ratios
    // uniform vec4 texRatio_0_to_3;
    GLint texRatio_0_to_3_UL = glGetUniformLocation(program, "texRatio_0_to_3");
    glUniform4f(texRatio_0_to_3_UL,
        pCurMesh->blendRatio[0],
        pCurMesh->blendRatio[1],
        pCurMesh->blendRatio[2],
        pCurMesh->blendRatio[3]);


    // Normal map, if needed
    GLint bUseNormalMap_UL = glGetUniformLocation(program, "bUseNormalMap");
    glUniform1f(bUseNormalMap_UL, (GLfloat)GL_FALSE);

    if (pCurMesh->normalMap != "")
    {
        GLuint normalMap_ID = ::g_pTextures->getTextureIDFromName(pCurMesh->normalMap);
        if (normalMap_ID == 0)
        {
            normalMap_ID = MissingTexture_ID;
        }
        // Arbitrarily pick texture unit 15
        const GLint NORMAL_MAP_TEXTURE_UNIT = 15;
        glActiveTexture(GL_TEXTURE0 + NORMAL_MAP_TEXTURE_UNIT);
        glBindTexture(GL_TEXTURE_2D, normalMap_ID);
        GLint textNormalMap_UL = glGetUniformLocation(program, "textNormalMap");
        glUniform1i(textNormalMap_UL, NORMAL_MAP_TEXTURE_UNIT);       // <-- Note we use the NUMBER, not the GL_TEXTURE3 here

        glUniform1f(bUseNormalMap_UL, (GLfloat)GL_TRUE);
    }

    return;
}





void DrawMesh(
    sMesh* pCurMesh, 
    glm::mat4 matModel,         // "parent" or initial model matrix
    GLuint program, 
    bool SetTexturesFromMeshInfo = true)
{

    // Calculate transformation even if model is NOT visible

    // Translation (movement, position, placement...)
    glm::mat4 matTranslate
        = glm::translate(glm::mat4(1.0f),
            glm::vec3(pCurMesh->positionXYZ.x,
                pCurMesh->positionXYZ.y,
                pCurMesh->positionXYZ.z));

    // Rotation...
    // Caculate 3 Euler acix matrices...
    glm::mat4 matRotateX =
        glm::rotate(glm::mat4(1.0f),
            glm::radians(pCurMesh->rotationEulerXYZ.x), // Angle in radians
            glm::vec3(1.0f, 0.0, 0.0f));

    //    //
    //    glm::quat qRotation = glm::quat(glm::vec3(0.0f, 15.0f, 0.0f));
    //    // Make matrix 15 degrees around y
    //    glm::mat4 matRotation = glm::mat4(qRotation);
    //    // Rotate it 15 degrees around Y FROM WHERE IS WAY
    //    matRotation *= glm::mat4(qRotation);

    glm::mat4 matRotateY =
        glm::rotate(glm::mat4(1.0f),
            glm::radians(pCurMesh->rotationEulerXYZ.y), // Angle in radians
            glm::vec3(0.0f, 1.0, 0.0f));

    glm::mat4 matRotateZ =
        glm::rotate(glm::mat4(1.0f),
            glm::radians(pCurMesh->rotationEulerXYZ.z), // Angle in radians
            glm::vec3(0.0f, 0.0, 1.0f));


    // Scale
    glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
        glm::vec3(pCurMesh->uniformScale,
            pCurMesh->uniformScale,
            pCurMesh->uniformScale));


    // Calculate the final model/world matrix

    // In matrix math, the last thing multipled is the 1st thing mathematically
    // Apply any POST transformation
    matModel *= pCurMesh->matPostParentRelative;


    matModel *= matTranslate;     // matModel = matModel * matTranslate;
    matModel *= matRotateX;
    matModel *= matRotateY;
    matModel *= matRotateZ;
    matModel *= matScale;


    // In matrix math, the last thing multipled is the 1st thing mathematically
    // Apply any PRE transformation
    matModel *= pCurMesh->matPreParentRelative;


    //           matRoationOnly = matModel * matRotateX * matRotateY * matRotateZ;


               //mat4x4_mul(mvp, p, m);
               //mvp = p * v * m;
   //            glm::mat4 matMVP = matProjection * matView * matModel;

               //const GLint mvp_location = glGetUniformLocation(program, "MVP");
               //glUniformMatrix4fv(mvp_location, 
               //    1,
               //    GL_FALSE,
               //    (const GLfloat*)&matMVP);

    // Save the last matrix that was rendered on this object
    pCurMesh->matModel_LastCalculated = matModel;



    // Is it visible? 
    if (!pCurMesh->bIsVisible)
    {
        // Continue in loops jumps to the end of this loop
        // (for, while, do)

        // If there's a lot of invisible child objects
        // then you may want to call the render on the child objects, too
        // 
        //// Check if there are child meshes
        for (unsigned int childIndex = 0; childIndex != pCurMesh->vec_pChildMeshes.size(); childIndex++)
        {
            // sMesh* pCurMesh, 
            // glm::mat4 matModel,         // "parent" or initial model matrix

            sMesh* pChildMesh = pCurMesh->vec_pChildMeshes[childIndex];

            // note that we DON'T reset the model matrix to the indenty
            //  matrix (setting it back to the origin). Instead we 
            //  pass THIS current matrix (wherever it is) as 
            //  the STARTING point.
            //
            DrawMesh(pChildMesh, matModel, program);
        }

        // DON'T draw this mesh
        return;
    }

    // HACK:
    // For the discard example
	// uniform bool bUseStencilTexture;
    GLint bUseStencilTexture_UL = glGetUniformLocation(program, "bUseStencilTexture");

    if (pCurMesh->uniqueFriendlyName == "Ground")
    {
        glUniform1f(bUseStencilTexture_UL, (GLfloat)GL_TRUE);

        // uniform sampler2D stencilTexture;
        GLuint stencilTextureID = ::g_pTextures->getTextureIDFromName("SurprisedChildFace.bmp");

        glActiveTexture(GL_TEXTURE0 + 40);
        glBindTexture(GL_TEXTURE_2D, stencilTextureID);

        GLint stencilTexture_UL = glGetUniformLocation(program, "stencilTexture");
        glUniform1i(stencilTexture_UL, 40);       // <-- Note we use the NUMBER, not the GL_TEXTURE3 here
    }
    else
    {
        glUniform1f(bUseStencilTexture_UL, (GLfloat)GL_FALSE);
    }

    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    // Use lighting or not
    // uniform bool bDoNotLight;	
    GLint bDoNotLight_UL = glGetUniformLocation(program, "bDoNotLight");
    if (pCurMesh->bDoNotLight)
    {
        //glUniform1f(bDoNotLight_UL, 1.0f);  // True
        glUniform1f(bDoNotLight_UL, (GLfloat)GL_TRUE);  // True
    }
    else
    {
        //                glUniform1f(bDoNotLight_UL, 0.0f);  // False
        glUniform1f(bDoNotLight_UL, (GLfloat)GL_FALSE);  // False
    }

    // Set up the textures for THIS mesh
    // uniform bool bUseTextureAsColour;	// If true, then sample the texture
    GLint bUseTextureAsColour_UL = glGetUniformLocation(program, "bUseTextureAsColour");
    glUniform1f(bUseTextureAsColour_UL, (GLfloat)GL_TRUE);

    if (SetTexturesFromMeshInfo)
    {
        SetUpTextures(pCurMesh, program);
    }

    //// See if we are using a normal map
    //GLint bUseNormalMap_UL = glGetUniformLocation(program, "bUseNormalMap");

    //if (pCurMesh->normalMap == "")
    //{
    //    glUniform1f(bUseNormalMap_UL, (GLfloat)GL_FALSE);
    //}
    //else
    //{
    //    glUniform1f(bUseNormalMap_UL, (GLfloat)GL_TRUE);
    //}


    // Could be called the "model" or "world" matrix
 //   glm::mat4 matModel = glm::mat4(1.0f);






    const GLint mvp_location = glGetUniformLocation(program, "matModel");
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&matModel);

    //const GLint mvp_location = glGetUniformLocation(program, "matView");
    //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&matMVP);

    //const GLint mvp_location = glGetUniformLocation(program, "matProjection");
    //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&matMVP);

    // uniform bool bUseObjectColour;
    GLint bUseObjectColour = glGetUniformLocation(program, "bUseObjectColour");

    if (pCurMesh->bOverrideObjectColour)
    {
        // bool doesn't really exist, it's a float...
        glUniform1f(bUseObjectColour, (GLfloat)GL_TRUE);    // or 1.0f
        // Set the object colour
        // uniform vec4 objectColour;
        GLint objectColour_UL = glGetUniformLocation(program, "objectColour");
        glUniform4f(objectColour_UL,
            pCurMesh->objectColourRGBA.r,
            pCurMesh->objectColourRGBA.g,
            pCurMesh->objectColourRGBA.b,
            1.0f);    }
    else
    {
        glUniform1f(bUseObjectColour, (GLfloat)GL_FALSE);   // or 0.0f
    }




    ///uniform float wholeObjectTransparencyAlpha;
    GLint wholeObjectTransparencyAlpha_UL = glGetUniformLocation(program, "wholeObjectTransparencyAlpha");
    glUniform1f(wholeObjectTransparencyAlpha_UL, pCurMesh->alphaTransparency);


    // solid or wireframe, etc.
//        glPointSize(10.0f);
    if (pCurMesh->bIsWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // Also render body sides
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }

    //        glDrawArrays(GL_TRIANGLES, 0, 3);
//            glDrawArrays(GL_TRIANGLES, 0, numberOfVertices_TO_DRAW);


    // Update for the LOD rendering
    //
    std::string meshToDraw = pCurMesh->modelFileName;

    // Does it have an LOD list? 
    if (!pCurMesh->vecLODInfos.empty())
    {
        // Calculate distance from camera
        float cameraDist = glm::distance(pCurMesh->positionXYZ, ::g_pFlyCamera->getEyeLocation());

        // Scan through this from begining to end.
        // This is important because the 1st item that is "close enough" will be chosen
        //  so the vector should be loaded from closest to farthest away
        for (sMesh::sLODInfo& LODinfo : pCurMesh->vecLODInfos)
        {
            // Close enough (within range?)?
            if (cameraDist < LODinfo.maxDistance)
            {
                // Yes, so use this model
                meshToDraw = LODinfo.modelName;
                ::g_numLODTrisDrawnThisFrame += LODinfo.numTris;
                break;  // Exit loop
            }
        }
    }//if (!pCurMesh->vecLODInfos.empty())


    sModelDrawInfo meshToDrawInfo;
//    if (::g_pMeshManager->FindDrawInfoByModelName(pCurMesh->modelFileName, meshToDrawInfo))
    if (::g_pMeshManager->FindDrawInfoByModelName(meshToDraw, meshToDrawInfo))
    {
        // Found the model
        glBindVertexArray(meshToDrawInfo.VAO_ID); 		// enable VAO(and everything else)
        //https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawElements.xhtml
        glDrawElements(GL_TRIANGLES,
            meshToDrawInfo.numberOfIndices,
            GL_UNSIGNED_INT,
            (void*)0);

        glBindVertexArray(0); 			//disable VAO(and everything else)
    }


//    // Check if there are child meshes
    for (unsigned int childIndex = 0; childIndex != pCurMesh->vec_pChildMeshes.size(); childIndex++)
    {
        // sMesh* pCurMesh, 
        // glm::mat4 matModel,         // "parent" or initial model matrix

        sMesh* pChildMesh = pCurMesh->vec_pChildMeshes[childIndex];

        // note that we DON'T reset the model matrix to the indenty
        //  matrix (setting it back to the origin). Instead we 
        //  pass THIS current matrix (wherever it is) as 
        //  the STARTING point.
        //
        DrawMesh(pChildMesh, matModel, program);
    }

	return;
}


void DrawDebugSphere(glm::vec3 position, glm::vec4 RGBA, float scale, GLuint program)
{
    // Created the debug sphere, yet?
    if (!pDebugSphere)           // Same as if ( pDebugSphere == NULL )
    {
        pDebugSphere = new sMesh();
//        pDebugSphere->modelFileName = "assets/models/Sphere_radius_1_xyz_N.ply";
        pDebugSphere->modelFileName = "assets/models/Sphere_radius_1_xyz_N_uv.ply";
        pDebugSphere->positionXYZ = glm::vec3(0.0f, 5.0f, 0.0f);
        pDebugSphere->bIsWireframe = true;
        pDebugSphere->objectColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        pDebugSphere->uniqueFriendlyName = "Debug_Sphere";
        pDebugSphere->uniformScale = 10.0f;
        pDebugSphere->bDoNotLight = true;
    }
    // At this point the debug sphere is created

    pDebugSphere->bIsVisible = true;
    pDebugSphere->positionXYZ = position;
    pDebugSphere->bOverrideObjectColour = true;
    pDebugSphere->objectColourRGBA = RGBA;
    pDebugSphere->uniformScale = scale;

    glm::mat4 matModel = glm::mat4(1.0f);   // identity matrix
    DrawMesh(pDebugSphere, matModel, program);

    pDebugSphere->bIsVisible = false;

    return;
}