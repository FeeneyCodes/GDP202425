#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
#include <string>

struct sVertex
{
    glm::vec3 pos;          // glm::vec2 pos;      // position   or "float x, y"
    glm::vec3 col;      // Colour     or "float x, y, z"
    // Colour range is 0.0 to 1.0
    // 0.0 = black (Red, Green, Blue)
    // 1.0 = white 
};

//sVertex vertices[3] =
//{
//    { { -0.6f, -0.4f }, { 1.0f, 0.0f, 0.0f } },
//    { {  0.6f, -0.4f }, { 0.0f, 1.0f, 0.0f } },
//    { {  0.0f,  0.6f }, { 0.0f, 0.0f, 1.0f } }
//};


static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec3 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";


glm::vec3 cameraEye = glm::vec3(0.0, 0.0, 4.0f);



static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    const float CAMERA_MOVE_SPEED = 0.1f;

    if (key == GLFW_KEY_A)
    {
        cameraEye.x -= CAMERA_MOVE_SPEED;
    }

    if (key == GLFW_KEY_D)
    {
        cameraEye.x += CAMERA_MOVE_SPEED;
    }

    if (key == GLFW_KEY_W)
    {
        cameraEye.z += CAMERA_MOVE_SPEED;
    }

    if (key == GLFW_KEY_S)
    {
        cameraEye.z -= CAMERA_MOVE_SPEED;
    }

    if (key == GLFW_KEY_Q)
    {
        cameraEye.y -= CAMERA_MOVE_SPEED;
    }
    if (key == GLFW_KEY_E)
    {
        cameraEye.y += CAMERA_MOVE_SPEED;
    }


    return;
}

void ConsoleStuff(void);

int main(void)
{   

//    ConsoleStuff();

    // On the stack, at compile time.
    // Limited by the size of the stack.
    // Also: Can't change the size.
//    sVertex vertices[3] =
//    {
//        { { -0.6f, -0.4f }, { 1.0f, 0.0f, 0.0f } },
//        { {  0.6f, -0.4f }, { 0.0f, 1.0f, 0.0f } },
//       { {  0.0f,  0.6f }, { 0.0f, 0.0f, 1.0f } }
//  };

//    sizeof(sVertex) * 3;

//    std::cout << "vertices: " << vertices << '\n';
//    std::cout << (*(vertices + 1)).

    // On the HEAP, so dynamically allocated at run time
//    sVertex* pVertices = new sVertex[3];
//
//    pVertices[0] = { { -0.6f, -0.4f }, { 1.0f, 0.0f, 0.0f } };
//    pVertices[1] = { {  0.6f, -0.4f }, { 0.0f, 1.0f, 0.0f } };
//    pVertices[2] = { {  0.0f,  0.6f }, { 0.0f, 0.0f, 1.0f } };


// ************************************************************
    // Read the top of the file to get some info.

    // Read all the text until I get to the word "vertex"
    std::ifstream plyFile("assets/models/bun_zipper_res3.ply");
    std::string token = "";

    //element vertex 1889
    while (token != "vertex")
    {
        plyFile >> token;
    };
    // Next info is the number of vertices
    int numberOfVertices = 0;
    plyFile >> numberOfVertices;


    //element face 3851
    while (token != "face")
    {
        plyFile >> token;
    };
    // Next info is the number of vertices
    int numberOfTriangles = 0;
    plyFile >> numberOfTriangles;

    //end_header
    // -0.0369122 0.127512 0.00276757 0.850855 0.5 
    while (token != "end_header")
    {
        plyFile >> token;
    };


    // 
    std::cout << numberOfVertices << std::endl;
    std::cout << numberOfTriangles << std::endl;

//property float x
//property float y
//property float z
//property float confidence
//property float intensity
    struct sPlyVertex
    {
        float x, y, z, confidence, intensity;
    };
//
// and 
// 
// 3 572 584 1040 
    struct sTriangle
    {
        unsigned int vertIndex_0;
        unsigned int vertIndex_1;
        unsigned int vertIndex_2;
    };

    // Load the data from the file
    sPlyVertex* pPlyVertices = new sPlyVertex[numberOfVertices];

    // end_header
    // -0.0369122 0.127512 0.00276757 0.850855 0.5
    for (unsigned index = 0; index != numberOfVertices; index++)
    {
        plyFile >> pPlyVertices[index].x;
        plyFile >> pPlyVertices[index].y;
        plyFile >> pPlyVertices[index].z;
        plyFile >> pPlyVertices[index].confidence;
        plyFile >> pPlyVertices[index].intensity;
    }

    // Load the triangle info from the file
    sTriangle* pPlyTriangles = new sTriangle[numberOfTriangles];
    for (unsigned int index = 0; index != numberOfTriangles; index++)
    {
        // 3 737 103 17 
        int discard = 0;
        plyFile >> discard;
        plyFile >> pPlyTriangles[index].vertIndex_0;
        plyFile >> pPlyTriangles[index].vertIndex_1;
        plyFile >> pPlyTriangles[index].vertIndex_2;
    }


// ******************************************************

    // This is the array we are giving the GPU 
    unsigned int numberOfVertices_TO_DRAW = numberOfTriangles * 3;
    // Each triangle has 3 vertices

    sVertex* pVertices = new sVertex[numberOfVertices_TO_DRAW];

    // Copy the data form the "ply" (i.e. file) arrays
    // to the format that the GPU expects
//     struct sPlyVertex
//    {
//        float x, y, z, confidence, intensity;
//    };
//
//    struct sTriangle
//    {
//        unsigned int vertIndex_0;
//        unsigned int vertIndex_1;
//        unsigned int vertIndex_2;
//    };
//
//  to... 
// 
//    struct sVertex
//    {
//        glm::vec2 pos;      // position   or "float x, y"
//        glm::vec3 col;      //

    unsigned int vertexIndex = 0;

    for (unsigned int triIndex = 0; triIndex != numberOfTriangles; triIndex++)
    {
//        { { -0.6f, -0.4f }, { 1.0f, 0.0f, 0.0f } },
//        { {  0.6f, -0.4f }, { 0.0f, 1.0f, 0.0f } },
//        { {  0.0f,  0.6f }, { 0.0f, 0.0f, 1.0f } }

        pVertices[vertexIndex + 0].pos.x = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_0 ].x;
        pVertices[vertexIndex + 0].pos.y = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_0 ].y;
        pVertices[vertexIndex + 0].pos.z = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_0 ].z;
        pVertices[vertexIndex + 0].col.r = 1.0f;
        pVertices[vertexIndex + 0].col.g = 1.0f;
        pVertices[vertexIndex + 0].col.b = 1.0f;

        pVertices[vertexIndex + 1].pos.x = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_1 ].x;
        pVertices[vertexIndex + 1].pos.y = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_1 ].y;
        pVertices[vertexIndex + 1].pos.z = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_1 ].z;
        pVertices[vertexIndex + 1].col.r = 1.0f;
        pVertices[vertexIndex + 1].col.g = 1.0f;
        pVertices[vertexIndex + 1].col.b = 1.0f;

        pVertices[vertexIndex + 2].pos.x = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_2 ].x;
        pVertices[vertexIndex + 2].pos.y = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_2 ].y;
        pVertices[vertexIndex + 2].pos.z = pPlyVertices[ pPlyTriangles[triIndex].vertIndex_2 ].z;
        pVertices[vertexIndex + 2].col.r = 1.0f;
        pVertices[vertexIndex + 2].col.g = 1.0f;
        pVertices[vertexIndex + 2].col.b = 1.0f;

        vertexIndex += 3;
    }



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

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

//    int size_in_bytes_of_vertex_array = sizeof(sVertex) * 3;
    int size_in_bytes_of_vertex_array = sizeof(sVertex) * numberOfVertices_TO_DRAW;

    glBufferData(GL_ARRAY_BUFFER,
                 size_in_bytes_of_vertex_array,     // sizeof(vertices),
                 pVertices,                         // vertices,
                 GL_STATIC_DRAW);

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    const GLint mvp_location = glGetUniformLocation(program, "MVP");

    const GLint vpos_location = glGetAttribLocation(program, "vPos");   
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Where the data specifically is.
    // Called the "vertex layout"

    //glm::vec3 pos;       
    //glm::vec3 col;    
//    { { -0.6f, -0.4f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
//    { {  0.6f, -0.4f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
//    { {  0.0f,  0.6f, 0.0f }, { 0.0f, 0.0f, 1.0f } }


    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(
        vpos_location, 
        3, 
        GL_FLOAT, 
        GL_FALSE,
        sizeof(sVertex),                        // 6 floats or 24 bytes
        (void*)offsetof(sVertex, pos));         // 0 bytes into the sVertex structure

    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(
        vcol_location, 
        3, 
        GL_FLOAT, 
        GL_FALSE,
        sizeof(sVertex), 
        (void*)offsetof(sVertex, col));     // 3 floats or 12 bytes into the sVertex structure

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        //       mat4x4 m, p, mvp;
        glm::mat4 m, p, v, mvp;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        //         mat4x4_identity(m);
        m = glm::mat4(1.0f);

        //mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        glm::mat4 rotateZ = 
            glm::rotate(glm::mat4(1.0f),    // Ignore this
            0.0f, // (float)glfwGetTime(),           // Angle in radians
            glm::vec3(0.0f, 0.0, 1.0f));    // Around the z

        m = m * rotateZ;

        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        p = glm::perspective(0.6f,
            ratio,
            0.1f,
            1000.0f);

        v = glm::mat4(1.0f);

//        glm::vec3 cameraEye = glm::vec3(0.0, 0.0, 4.0f);
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

        v = glm::lookAt(
                cameraEye,
                cameraTarget,
                upVector);

        //mat4x4_mul(mvp, p, m);
        mvp = p * v * m;
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
        glBindVertexArray(vertex_array);


        // solid or wireframe, etc.
//        glPointSize(10.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 0, numberOfVertices_TO_DRAW);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
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