//#define GLAD_GL_IMPLEMENTATION
//#include <glad/glad.h>
//
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include "GLCommon.h"

//#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <iostream>     // "input output" stream
#include <fstream>      // "file" stream
#include <sstream>      // "string" stream ("string builder" in Java c#, etc.)
#include <string>

#include <vector>


//void ReadPlyModelFromFile(std::string plyFileName);
#include "PlyFileLoaders.h"

#include "Basic_Shader_Manager/cShaderManager.h"

#include "sMesh.h"

#include "cVAOManager/cVAOManager.h"

#include "sharedThings.h"       // Fly camera

#include "cPhysics.h"

//
//const unsigned int MAX_NUMBER_OF_MESHES = 1000;
//unsigned int g_NumberOfMeshesToDraw;
//sMesh* g_myMeshes[MAX_NUMBER_OF_MESHES] = { 0 };    // All zeros

std::vector<sMesh*> g_vecMeshesToDraw;

cPhysics* g_pPhysicEngine = NULL;
// This loads the 3D models for drawing, etc.
cVAOManager* g_pMeshManager = NULL;

void AddModelsToScene(void);


//glm::vec3 cameraEye = glm::vec3(0.0, 0.0, 4.0f);


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    const float CAMERA_MOVE_SPEED = 0.1f;

    if (mods == GLFW_MOD_SHIFT)
    {

    }

//    if (key == GLFW_KEY_A)
//    {
//        cameraEye.x -= CAMERA_MOVE_SPEED;
////        g_myMeshes[::g_SelectedObjectIndex]->positionXYZ.x += CAMERA_MOVE_SPEED;
//    }
//
//    if (key == GLFW_KEY_D)
//    {
//        cameraEye.x += CAMERA_MOVE_SPEED;
////        g_myMeshes[0]->positionXYZ.x -= CAMERA_MOVE_SPEED;
//    }
//
//    if (key == GLFW_KEY_W)
//    {
//        cameraEye.z += CAMERA_MOVE_SPEED;
//    }
//
//    if (key == GLFW_KEY_S)
//    {
//        cameraEye.z -= CAMERA_MOVE_SPEED;
//    }
//
//    if (key == GLFW_KEY_Q)
//    {
//        cameraEye.y -= CAMERA_MOVE_SPEED;
//    }
//    if (key == GLFW_KEY_E)
//    {
//        cameraEye.y += CAMERA_MOVE_SPEED;
//    }


    return;
}

void ConsoleStuff(void);

// https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
float getRandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

// Returns NULL if NOT found
sMesh* pFindMeshByFriendlyName(std::string theNameToFind)
{
    for (unsigned int index = 0; index != ::g_vecMeshesToDraw.size(); index++)
    {
        if (::g_vecMeshesToDraw[index]->uniqueFriendlyName == theNameToFind)
        {
            return ::g_vecMeshesToDraw[index];
        }
    }
    // Didn't find it
    return NULL;
}


int main(void)
{   

//    ConsoleStuff();
//
    // On the stack, at compile time.
    // Limited by the size of the stack.
    // Also: Can't change the size.
//    sVertex vertices[3] =
//    {
//        { { -0.6f, -0.4f }, { 1.0f, 0.0f, 0.0f } },
//        { {  0.6f, -0.4f }, { 0.0f, 1.0f, 0.0f } },
//       { {  0.0f,  0.6f }, { 0.0f, 0.0f, 1.0f } }
//  };
//
//    sizeof(sVertex) * 3;
////    std::cout << "vertices: " << vertices << '\n';
//    std::cout << (*(vertices + 1)).
//
    // On the HEAP, so dynamically allocated at run time
//    sVertex* pVertices = new sVertex[3];
//
//    pVertices[0] = { { -0.6f, -0.4f }, { 1.0f, 0.0f, 0.0f } };
//    pVertices[1] = { {  0.6f, -0.4f }, { 0.0f, 1.0f, 0.0f } };
//    pVertices[2] = { {  0.0f,  0.6f }, { 0.0f, 0.0f, 1.0f } };
//
    //s3DFileData plyFileInfoBunny;
    //plyFileInfoBunny.fileName = "assets/models/bun_zipper_res3.ply";
    //ReadPlyModelFromFile_xyz_ci(plyFileInfoBunny);
//
    //s3DFileData plyFileInfo;
    //plyFileInfo.fileName = "assets/models/VintageRacingCar_xyz_only.ply";
    //ReadPlyModelFromFile_xyz(plyFileInfo);
//
    //s3DFileData plyFileInfo;
    //plyFileInfo.fileName = "assets/models/Dragon 2.5Edited_xyz_only.ply";
    //ReadPlyModelFromFile_xyz(plyFileInfo);
//
// ******************************************************
//
//    // This is the array we are giving the GPU 
////    unsigned int numberOfVertices_TO_DRAW = numberOfTriangles * 3;
//    unsigned int numberOfVertices_TO_DRAW = plyFileInfo.numberOfTriangles * 3;
//    // Each triangle has 3 vertices
//
//    sVertex* pVertices = new sVertex[numberOfVertices_TO_DRAW];
//
//    // Copy the data form the "ply" (i.e. file) arrays
//    // to the format that the GPU expects
////     struct sPlyVertex
////    {
////        float x, y, z, confidence, intensity;
////    };
////
////    struct sTriangle
////    {
////        unsigned int vertIndex_0;
////        unsigned int vertIndex_1;
////        unsigned int vertIndex_2;
////    };
////
////  to... 
//// 
////    struct sVertex
////    {
////        glm::vec2 pos;      // position   or "float x, y"
////        glm::vec3 col;      //
//
//    unsigned int vertexIndex = 0;
//
////    for (unsigned int triIndex = 0; triIndex != numberOfTriangles; triIndex++)
//    for (unsigned int triIndex = 0; triIndex != plyFileInfo.numberOfTriangles; triIndex++)
//    {
////        { { -0.6f, -0.4f }, { 1.0f, 0.0f, 0.0f } },
////        { {  0.6f, -0.4f }, { 0.0f, 1.0f, 0.0f } },
////        { {  0.0f,  0.6f }, { 0.0f, 0.0f, 1.0f } }
//
////        pVertices[vertexIndex + 0].pos.x = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_0 ].x;
//        pVertices[vertexIndex + 0].pos.x = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_0 ].x;
//        pVertices[vertexIndex + 0].pos.y = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_0 ].y;
//        pVertices[vertexIndex + 0].pos.z = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_0 ].z;
//        pVertices[vertexIndex + 0].col.r = 1.0f;
//        pVertices[vertexIndex + 0].col.g = 1.0f;
//        pVertices[vertexIndex + 0].col.b = 1.0f;
//
//        pVertices[vertexIndex + 1].pos.x = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_1 ].x;
//        pVertices[vertexIndex + 1].pos.y = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_1 ].y;
//        pVertices[vertexIndex + 1].pos.z = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_1 ].z;
//        pVertices[vertexIndex + 1].col.r = 1.0f;
//        pVertices[vertexIndex + 1].col.g = 1.0f;
//        pVertices[vertexIndex + 1].col.b = 1.0f;
//
//        pVertices[vertexIndex + 2].pos.x = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_2 ].x;
//        pVertices[vertexIndex + 2].pos.y = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_2 ].y;
//        pVertices[vertexIndex + 2].pos.z = plyFileInfo.pPlyVertices[plyFileInfo.pPlyTriangles[triIndex].vertIndex_2 ].z;
//        pVertices[vertexIndex + 2].col.r = 1.0f;
//        pVertices[vertexIndex + 2].col.g = 1.0f;
//        pVertices[vertexIndex + 2].col.b = 1.0f;
//
//        vertexIndex += 3;
//    }
//
//
//    // Scale the dragon
////    for (unsigned int index = 0; index != numberOfVertices_TO_DRAW; index++)
////    {
////        pVertices[index].pos.x *= 0.01f;
////        pVertices[index].pos.y *= 0.01f;
////        pVertices[index].pos.z *= 0.01f;
////    }
//
////    for (unsigned int index = 0; index != numberOfVertices_TO_DRAW; index++)
////    {
////        pVertices[index].pos.x += 1.0f;
////    }
//



    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Callback for keyboard, but for "typing"
    // Like it captures the press and release and repeat
    glfwSetKeyCallback(window, key_callback);

    // 
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowFocusCallback(window, cursor_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);



    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity



//    GLuint vertex_buffer;
//    glGenBuffers(1, &vertex_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//
////    int size_in_bytes_of_vertex_array = sizeof(sVertex) * 3;
//    int size_in_bytes_of_vertex_array = sizeof(sVertex) * numberOfVertices_TO_DRAW;
//
//    glBufferData(GL_ARRAY_BUFFER,
//                 size_in_bytes_of_vertex_array,     // sizeof(vertices),
//                 pVertices,                         // vertices,
//                 GL_STATIC_DRAW);

    cShaderManager* pShaderManager = new cShaderManager();

    cShaderManager::cShader vertexShader;
    vertexShader.fileName = "assets/shaders/vertex01.glsl";

    cShaderManager::cShader fragmentShader;
    fragmentShader.fileName = "assets/shaders/fragment01.glsl";

    if ( ! pShaderManager->createProgramFromFile("shader01",
                                                 vertexShader, fragmentShader))
    {
        std::cout << "Error: " << pShaderManager->getLastError() << std::endl;
    }
    else
    {
        std::cout << "Shader built OK" << std::endl;
    }

    const GLuint program = pShaderManager->getIDFromFriendlyName("shader01");

    glUseProgram(program);

//    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
//    glCompileShader(vertex_shader);
//
//    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
//    glCompileShader(fragment_shader);
//
//    const GLuint program = glCreateProgram();
//    glAttachShader(program, vertex_shader);
//    glAttachShader(program, fragment_shader);
//    glLinkProgram(program);
//
//    const GLint mvp_location = glGetUniformLocation(program, "MVP");
//
//    const GLint vpos_location = glGetAttribLocation(program, "vPos");   
//    const GLint vcol_location = glGetAttribLocation(program, "vCol");
//
//    GLuint vertex_array;
//    glGenVertexArrays(1, &vertex_array);
//    glBindVertexArray(vertex_array);
//
//
//
//    // Where the data specifically is.
//    // Called the "vertex layout"
//
//    //glm::vec3 pos;       
//    //glm::vec3 col;    
////    { { -0.6f, -0.4f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
////    { {  0.6f, -0.4f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
////    { {  0.0f,  0.6f, 0.0f }, { 0.0f, 0.0f, 1.0f } }
//
//
//    glEnableVertexAttribArray(vpos_location);
//    glVertexAttribPointer(
//        vpos_location, 
//        3, 
//        GL_FLOAT, 
//        GL_FALSE,
//        sizeof(sVertex),                        // 6 floats or 24 bytes
//        (void*)offsetof(sVertex, pos));         // 0 bytes into the sVertex structure
//
//    glEnableVertexAttribArray(vcol_location);
//    glVertexAttribPointer(
//        vcol_location, 
//        3, 
//        GL_FLOAT, 
//        GL_FALSE,
//        sizeof(sVertex), 
//        (void*)offsetof(sVertex, col));     // 3 floats or 12 bytes into the sVertex structure


    // Loading the TYPES of models I can draw...

//    cVAOManager* pMeshManager = new cVAOManager();
    ::g_pMeshManager = new cVAOManager();

    //sModelDrawInfo carModelInfo;
    //pMeshManager->LoadModelIntoVAO("assets/models/VintageRacingCar_xyz_only.ply", 
    //                               carModelInfo, program);
    //std::cout << carModelInfo.numberOfVertices << " vertices loaded" << std::endl;

    //sModelDrawInfo dragonModel;
    //pMeshManager->LoadModelIntoVAO("assets/models/Dragon 2.5Edited_xyz_only.ply", 
    //    dragonModel, program);
    //std::cout << dragonModel.numberOfVertices << " vertices loaded" << std::endl;

    //sModelDrawInfo terrainModel;
    //pMeshManager->LoadModelIntoVAO("assets/models/Simple_MeshLab_terrain_xyz_only.ply", 
    //    terrainModel, program);
    //std::cout << terrainModel.numberOfVertices << " vertices loaded" << std::endl;

    sModelDrawInfo bunnyModel;
    ::g_pMeshManager->LoadModelIntoVAO("assets/models/bun_zipper_res2_10x_size_xyz_only.ply",
        bunnyModel, program);
    std::cout << bunnyModel.numberOfVertices << " vertices loaded" << std::endl;

    sModelDrawInfo platPlaneDrawInfo;
    ::g_pMeshManager->LoadModelIntoVAO("assets/models/Flat_Plane_xyz.ply", 
        platPlaneDrawInfo, program);
    std::cout << platPlaneDrawInfo.numberOfVertices << " vertices loaded" << std::endl;
    
    sModelDrawInfo sphereMesh;
    ::g_pMeshManager->LoadModelIntoVAO("assets/models/Sphere_radius_1_xyz.ply",
        sphereMesh, program);
    std::cout << sphereMesh.numberOfVertices << " vertices loaded" << std::endl;

//    pMeshManager->LoadTheListOfModelsIWantFromASexyFile("MyModels.sexy");


    ::g_pPhysicEngine = new cPhysics();

    AddModelsToScene();

   
    ::g_pFlyCamera = new cBasicFlyCamera();
    ::g_pFlyCamera->setEyeLocation(glm::vec3(0.0f, 0.0f, -20.0f));



    glUseProgram(program);

    // Enable depth buffering (z buffering)
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml
    glEnable(GL_DEPTH_TEST);

    double currentFrameTime = glfwGetTime();
    double lastFrameTime = glfwGetTime();





    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //        glm::mat4 m, p, v, mvp;
        glm::mat4 matProjection = glm::mat4(1.0f);

        matProjection = glm::perspective(0.6f,           // FOV
            ratio,          // Aspect ratio of screen
            0.1f,           // Near plane
            1000.0f);       // Far plane

        // View or "camera"
        glm::mat4 matView = glm::mat4(1.0f);

        //        glm::vec3 cameraEye = glm::vec3(0.0, 0.0, 4.0f);
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

        matView = glm::lookAt(::g_pFlyCamera->getEyeLocation(),
            ::g_pFlyCamera->getTargetLocation(),
            upVector);
        //        matView = glm::lookAt( cameraEye,
        //                               cameraTarget,
        //                               upVector);


        const GLint matView_UL = glGetUniformLocation(program, "matView");
        glUniformMatrix4fv(matView_UL, 1, GL_FALSE, (const GLfloat*)&matView);

        const GLint matProjection_UL = glGetUniformLocation(program, "matProjection");
        glUniformMatrix4fv(matProjection_UL, 1, GL_FALSE, (const GLfloat*)&matProjection);



        // Draw all the objects
        //for (unsigned int meshIndex = 0; meshIndex != ::g_NumberOfMeshesToDraw; meshIndex++)
        for (unsigned int meshIndex = 0; meshIndex != ::g_vecMeshesToDraw.size(); meshIndex++)
        {
            //            sMesh* pCurMesh = ::g_myMeshes[meshIndex];
            sMesh* pCurMesh = ::g_vecMeshesToDraw[meshIndex];

            // Is it visible? 
            if (!pCurMesh->bIsVisible)
            {
                // Continue in loops jumps to the end of this loop
                // (for, while, do)
                continue;
            }

            // Could be called the "model" or "world" matrix
            glm::mat4 matModel = glm::mat4(1.0f);

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
            matModel *= matTranslate;     // matModel = matModel * matTranslate;
            matModel *= matRotateX;
            matModel *= matRotateY;
            matModel *= matRotateZ;
            matModel *= matScale;

            //mat4x4_mul(mvp, p, m);
            //mvp = p * v * m;
//            glm::mat4 matMVP = matProjection * matView * matModel;

            //const GLint mvp_location = glGetUniformLocation(program, "MVP");
            //glUniformMatrix4fv(mvp_location, 
            //    1,
            //    GL_FALSE,
            //    (const GLfloat*)&matMVP);

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
            }
            else
            {
                glUniform1f(bUseObjectColour, (GLfloat)GL_FALSE);   // or 0.0f
            }

            // Set the object colour
            // uniform vec4 objectColour;
            GLint objectColour_UL = glGetUniformLocation(program, "objectColour");
            glUniform4f(objectColour_UL,
                pCurMesh->objectColourRGBA.r,
                pCurMesh->objectColourRGBA.g,
                pCurMesh->objectColourRGBA.b,
                1.0f);


            // solid or wireframe, etc.
    //        glPointSize(10.0f);
            if (pCurMesh->bIsWireframe)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            //        glDrawArrays(GL_TRIANGLES, 0, 3);
//            glDrawArrays(GL_TRIANGLES, 0, numberOfVertices_TO_DRAW);

            sModelDrawInfo meshToDrawInfo;
            if (::g_pMeshManager->FindDrawInfoByModelName(pCurMesh->modelFileName, meshToDrawInfo))
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

        }//for (unsigned int meshIndex..


        // Calculate elapsed time
        // We'll enhance this
        currentFrameTime = glfwGetTime();
        double deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        //sMesh* pBall = pFindMeshByFriendlyName("Ball");
        //if (pBall)
        //{
        //    pBall->positionXYZ.y -= 1.0f * deltaTime;
        //}

        // Physic update and test 
        ::g_pPhysicEngine->StepTick(deltaTime);

        // Handle async IO stuff
        handleKeyboardAsync(window);
        handleMouseAsync(window);

        glfwSwapBuffers(window);
        glfwPollEvents();


        //std::cout << "Camera: "
        std::stringstream ssTitle;
        ssTitle << "Camera: "
            << ::g_pFlyCamera->getEyeLocation().x << ", "
            << ::g_pFlyCamera->getEyeLocation().y << ", "
            << ::g_pFlyCamera->getEyeLocation().z << std::endl;
//        ssTitle << "Camera: "
//            << cameraEye.x << ", "
//            << cameraEye.y << ", "
//            << cameraEye.z << std::endl;

//        glfwSetWindowTitle(window, "Hey!");
        glfwSetWindowTitle(window, ssTitle.str().c_str());


    }// End of the draw loop


    // Delete everything
    delete ::g_pFlyCamera;
    delete ::g_pPhysicEngine;

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


void AddModelsToScene(void)
{

    // Load some models to draw

    // Add a bunch of bunny rabbits
    float boxLimit = 50.0f;
    float boxStep = 5.0f;
    for (float x = -boxLimit; x <= boxLimit; x += boxStep)
    {
        for (float z = -boxLimit; z <= boxLimit; z += boxStep)
        {
            sMesh* pBunny = new sMesh();
            pBunny->modelFileName = "assets/models/bun_zipper_res2_10x_size_xyz_only.ply";
            pBunny->positionXYZ = glm::vec3(x, -3.0f, z);
            pBunny->objectColourRGBA 
                = glm::vec4(getRandomFloat(0.0f, 1.0f),
                            getRandomFloat(0.0f, 1.0f),
                            getRandomFloat(0.0f, 1.0f), 
                            1.0f );
            pBunny->uniqueFriendlyName = "Ground";
            ::g_vecMeshesToDraw.push_back(pBunny);
        }
    }//for (float x = -boxLimit...


    {
        sMesh* pFlatPlane = new sMesh();
        pFlatPlane->modelFileName = "assets/models/Flat_Plane_xyz.ply";
        pFlatPlane->positionXYZ = glm::vec3(0.0f, -5.0f, 0.0f);
        pFlatPlane->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        pFlatPlane->uniqueFriendlyName = "Ground";
        //        pFlatPlane->bIsWireframe = true;
        //        ::g_myMeshes[::g_NumberOfMeshesToDraw] = pFlatPlane;
        //        ::g_NumberOfMeshesToDraw++;
        ::g_vecMeshesToDraw.push_back(pFlatPlane);


        // Add the "ground" to the physcs
        cPhysics::sAABB* pAABBGround = new cPhysics::sAABB();
        pAABBGround->centreXYZ = pFlatPlane->positionXYZ;
        sModelDrawInfo planeMeshInfo;
        ::g_pMeshManager->FindDrawInfoByModelName(pFlatPlane->modelFileName, planeMeshInfo);
        pAABBGround->extentsXYZ = planeMeshInfo.extenXYZ;

        pAABBGround->physicInfo.pAssociatedDrawingMeshInstance = pFlatPlane;

        ::g_pPhysicEngine->vecAABBs.push_back(pAABBGround);
    }
    {
        sMesh* pFlatPlane = new sMesh();
        pFlatPlane->modelFileName = "assets/models/Flat_Plane_xyz.ply";
        pFlatPlane->positionXYZ = glm::vec3(0.0f, -5.0f, 0.0f);
        pFlatPlane->bIsWireframe = true;
        pFlatPlane->uniformScale = 1.01f;
        pFlatPlane->objectColourRGBA = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        //::g_myMeshes[::g_NumberOfMeshesToDraw] = pFlatPlane;
        //::g_NumberOfMeshesToDraw++;
        //::g_vecMeshesToDraw.push_back(pFlatPlane);
    }


    {
        sMesh* pSphereMesh = new sMesh();
        pSphereMesh->modelFileName = "assets/models/Sphere_radius_1_xyz.ply";
        pSphereMesh->positionXYZ = glm::vec3(0.0f, 10.0f, 0.0f);
        //pSphereMesh->bIsWireframe = true;
        pSphereMesh->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        pSphereMesh->uniqueFriendlyName = "Ball";

        //::g_myMeshes[::g_NumberOfMeshesToDraw] = pSphere;
        //::g_NumberOfMeshesToDraw++;
        ::g_vecMeshesToDraw.push_back(pSphereMesh);

        // Add sphere
        cPhysics::sSphere* pSphereInfo = new cPhysics::sSphere();
        pSphereInfo->centre = pSphereMesh->positionXYZ;
        // HACK: We know this is 1.0 because...?
        // We could also have pulled that information from the mesh info
        pSphereInfo->radius = 1.0f;

//        pSphereInfo->physicInfo.velocity.y = -0.5f;
        
        // Associate this drawing mesh to this physics object
        pSphereInfo->physicInfo.pAssociatedDrawingMeshInstance = pSphereMesh;

        ::g_pPhysicEngine->vecSpheres.push_back(pSphereInfo);
    }
    //    sMesh* pDragon = new sMesh();
    //    pDragon->modelFileName = "assets/models/Dragon 2.5Edited_xyz_only.ply";
    //    pDragon->positionXYZ = glm::vec3(20.0f, 0.0f, 0.0f);
    //    pDragon->rotationEulerXYZ.x = -90.0f;
    //    pDragon->uniformScale = 0.1f;
    //    pDragon->objectColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); 
    //
    //    ::g_myMeshes[0] = pDragon;
    //
    //
    //    sMesh* pDragon2 = new sMesh();
    //    pDragon2->modelFileName = "assets/models/Dragon 2.5Edited_xyz_only.ply";
    //    pDragon2->positionXYZ = glm::vec3(-20.0f, 0.0f, 0.0f);
    //    pDragon2->rotationEulerXYZ.x = 90.0f;
    //    pDragon2->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    //    pDragon2->uniformScale = 0.2f;
    //
    //
    //    ::g_myMeshes[1] = pDragon2;
    //
    //    ::g_NumberOfMeshesToDraw = 2;
    //
    //
    //    sMesh* pTerrainMesh = new sMesh();
    //    pTerrainMesh->modelFileName = "assets/models/Simple_MeshLab_terrain_xyz_only.ply";
    //    pTerrainMesh->positionXYZ = glm::vec3(0.0f, -25.0f, 0.0f);
    //    //pTerrainMesh->rotationEulerXYZ.x = 90.0f;
    //    pTerrainMesh->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //    pTerrainMesh->bOverrideObjectColour = true;
    ////    pTerrainMesh->bIsWireframe = true;
    //    ::g_myMeshes[::g_NumberOfMeshesToDraw] = pTerrainMesh;
    //    ::g_NumberOfMeshesToDraw++;
    //
    //
    //    for (int count = 0; count != 100; count++)
    //    {
    //        sMesh* pDragon = new sMesh();
    //        pDragon->modelFileName = "assets/models/VintageRacingCar_xyz_only.ply";
    //        pDragon->positionXYZ = glm::vec3(getRandomFloat(-5.0f, 5.0f),
    //                                         getRandomFloat(-5.0f, 5.0f),
    //                                         getRandomFloat(-5.0f, 5.0f));
    //        pDragon->rotationEulerXYZ.x = 90.0f;
    //        pDragon->objectColourRGBA
    //            = glm::vec4(getRandomFloat(0.0f, 1.0f),
    //                        getRandomFloat(0.0f, 1.0f),
    //                        getRandomFloat(0.0f, 1.0f),
    //                        1.0f);
    //
    //
    //        pDragon->uniformScale = 0.2f;
    //
    //        // This is evil, nasty code. 
    //        // Do this if you hate humanity...
    ////        pDragon->bIsWireframe = rand() % 2;
    //
    //        ::g_myMeshes[::g_NumberOfMeshesToDraw] = pDragon;
    //
    //        ::g_NumberOfMeshesToDraw++;
    //    }



    return;
}




























//using namespace std;

void ConsoleStuff(void)
{
    // "o" for output
//    std::ofstream myFile("someData.txt");
    // Write something
    //myFile << "Hello" << std::endl;
    //myFile << "there";
    //myFile.close();

    // Now read this file
//    std::ifstream myFile2("someData.txt");
//    std::string someString;
//    myFile2 >> someString;
//    std::cout << someString << std::endl;
//
    //std::string aword;
    //while (aword != "END_OF_FILE")
    //{
    //    myFile2 >> aword;
    //    std::cout << aword << std::endl;
    //};

    //std::string aword;
    //while (myFile2 >> aword)
    //{
    //    std::cout << aword << std::endl;
    //};

    std::ifstream myFile2("assets/models/bun_zipper_res3.ply");
    if (myFile2.is_open())
    {

        std::string aword;
        while (myFile2 >> aword)
        {
            std::cout << aword << std::endl;
        };
    }
    else
    {
        std::cout << "Can't find file" << std::endl;
    }


    // iostream
    std::cout << "Type a number:" << std::endl;

    int x = 0;
    std::cin >> x;

    std::cout << "You typed: " << x << std::endl;

    std::cout << "Type your name:" << std::endl;
    std::string name;
    std::cin >> name;

    std::cout << "Hello " << name << std::endl;
    return;
}