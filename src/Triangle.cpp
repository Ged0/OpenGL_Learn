// Triangle.cpp
// Our first OpenGL program that will just draw a triangle on the screen.

#include <GLTools.h>         // OpenGL toolkit
#include <GLShaderManager.h> // Shader Manager Class

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#ifdef __APPLE__
#include <glut/glut.h> // OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL/glut.h> // Windows FreeGlut equivalent
#endif

#include <iostream>

// using namespace glm;

GLBatch triangleBatch;
GLShaderManager shaderManager;

// Load up a triangle
GLfloat vVerts[] = {-0.5f, 0.0f, 0.0f,
                    0.5f, 0.0f, 0.0f,
                    0.0f, 0.5f, 0.0f};

///////////////////////////////////////////////////////////////////////////////
// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
}

///////////////////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering context.
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC()
{
    // Blue background
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    shaderManager.InitializeStockShaders();

    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}

void Specialkeys(int key, int x, int y)
{
    GLfloat stepSize = 0.025f;

    if (key == GLUT_KEY_UP)
    {
        std::cout << "changed" << std::endl;
        // for (GLfloat &x : vVerts)
        // {
        //     x += stepSize;
        //     std::cout << x << std::endl;
        // }
        for (int i = 0; i < sizeof(vVerts) / sizeof(vVerts[0]); i++)
        {
            vVerts[i] += stepSize;
        }
    }
    else if (key == GLUT_KEY_F1)
    {
        std::cout << "test" << std::endl;
    }

    triangleBatch.CopyVertexData3f(vVerts);
    glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    triangleBatch.Draw();

    // Perform the buffer swap to display back buffer
    glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
// Main entry point for GLUT based programs
int main(int argc, char *argv[])
{
    gltSetWorkingDirectory(argv[0]);

    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(Specialkeys);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    SetupRC();

    glutMainLoop();
    return 0;
}
