//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

// Inclusión de bibliotecas necesarias
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"
#include "glm.h"
#include "Mesh.h"

#include <iostream>
#include <GL/freeglut.h>
#include <GL/glew.h>
#include <FreeImage.h>
#include <cmath>

//-----------------------------------------------------------------------------

// Clase de la ventana de la aplicación
class myWindow : public cwc::glutWindow
{
protected:
    // Administrador de shaders
    cwc::glShaderManager SM;

    // Punteros a objetos Shader
    cwc::glShader* shader;
    cwc::glShader* shader1;

    // ID del programa OpenGL
    GLuint ProgramObject;

    // Objetos 3D representados como mallas
    Mesh seaTile;
    Mesh beach;
    Mesh forest;
    Mesh highlands;
    Mesh snowPeak;

    Mesh sakuras;
    Mesh trees;
    Mesh pines;

    Mesh boat;
    Mesh shelter;

    Mesh goat;
    Mesh cyclope;

    Mesh moon;

    // Parámetros para animación
    float t = M_PI;
    float dt = 0.01;

public:
    myWindow() {}

    // Inicialización de la ventana
    virtual void OnInit()
    {
        glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        // Carga de shaders
        shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt");
        if (shader == 0)
        {
            std::cout << "Error Loading, compiling or linking shader\n";
        }
        else
        {
            ProgramObject = shader->GetProgramObject();
        }

        shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt");
        if (shader1 == 0)
        {
            std::cout << "Error Loading, compiling or linking shader\n";
        }
        else
        {
            ProgramObject = shader1->GetProgramObject();
        }

        // Carga de modelos 3D desde archivos .obj
        seaTile = Mesh("./Meshes/Sea.obj");
        beach = Mesh("./Meshes/Beach.obj");
        forest = Mesh("./Meshes/Forest.obj");
        highlands = Mesh("./Meshes/Highlands.obj");
        snowPeak = Mesh("./Meshes/SnowPeak.obj");

        sakuras = Mesh("./Meshes/Sakuras.obj");
        trees = Mesh("./Meshes/Trees.obj");
        pines = Mesh("./Meshes/Pines.obj");

        boat = Mesh("./Meshes/Boat.obj");
        shelter = Mesh("./Meshes/Shelter.obj");

        goat = Mesh("./Meshes/Goat.obj");
        cyclope = Mesh("./Meshes/Cyclope.obj");

        moon = Mesh("./Meshes/Moon.obj", "./Textures/moon.jpg");
    }

    // Renderizado de la escena
    virtual void OnRender(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateCamera();

        glPushMatrix();

        if (shader) shader->begin();

        glPushMatrix();

        // Dibujo del suelo del escenario (mar)
        for (int i = 0; i < 6; i++)
        {
            glPushMatrix();

            for (int j = 0; j < 6; j++)
            {
                seaTile.draw();
                glTranslatef(0.0f, 0.0f, -0.910f);
            }

            glPopMatrix();
            glTranslatef(0.910f, 0.0f, 0.0f);
        }

        glPopMatrix();

        // Dibujo de otros elementos de la escena
        beach.draw();
        forest.draw();
        highlands.draw();
        snowPeak.draw();

        sakuras.draw();
        trees.draw();
        pines.draw();

        boat.draw();
        shelter.draw();

        goat.draw();
        cyclope.draw();

        if (shader) shader->end();

        glPopMatrix();

        glPushMatrix();

        if (shader1) shader1->begin();

        // Dibujo de la luna
        moon.draw();

        if (shader1) shader1->end();

        glPopMatrix();

        glutSwapBuffers();

        Repaint();
    }

    // Manejo de cambios en el tamaño de la ventana
    virtual void OnResize(int w, int h)
    {
        if (h == 0)
        {
            h = 1;
        }

        float ratio = 1.0f * (float)w / (float)h;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, w, h);

        // Configuración de la proyección y la matriz de vista
        gluPerspective(45, ratio, 1, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(
            0.0f, 0.0f, 100.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );
    }

    // Actualización de la posición de la cámara
    void updateCamera() {
        glLoadIdentity();

        if (t > 2.0f * M_PI)
        {
            t = 0.0f;
        }

        // Configuración de la posición de la cámara
        gluLookAt(
            4.0f * cos(t) - 0.5f, 0.8f, 4.0f * sin(t) + 1.0f,
            -0.5f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f
        );

        t += dt;
    }

    // Manejo de eventos cuando la aplicación está en estado inactivo
    virtual void OnIdle() {}

    // Manejo de eventos cuando se cierra la aplicación
    virtual void OnClose(void) {}

    // Manejo de eventos de clic del mouse
    virtual void OnMouseDown(int button, int x, int y) {}

    // Manejo de eventos de liberación del mouse
    virtual void OnMouseUp(int button, int x, int y) {}

    // Manejo de eventos de rueda de mouse
    virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) {}

    // Manejo de eventos de teclado cuando se presiona una tecla
    virtual void OnKeyDown(int nKey, char cAscii)
    {
        if (cAscii == 27)
        {
            this->Close();
        }
    }

    // Manejo de eventos de teclado cuando se libera una tecla
    virtual void OnKeyUp(int nKey, char cAscii)
    {
        if (cAscii == 's')
        {
            shader->enable();
        }
        else if (cAscii == 'f')
        {
            shader->disable();
        }
    }
};

//-----------------------------------------------------------------------------

// Clase de la aplicación
class myApplication : public cwc::glApplication
{
public:
    virtual void OnInit() {
        std::cout << "Hello World!\n";
    }
};

//-----------------------------------------------------------------------------

// Función principal
int main(void)
{
    myApplication* pApp = new myApplication;
    myWindow* myWin = new myWindow();

    pApp->run();
    delete pApp;

    return 0;
}