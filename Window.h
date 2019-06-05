#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();

	/*

		Seleccion de camara
			0 - Camara libre
			1 - Camara aerea
			2 - Camara rueda
			3 - Camara carrusel
	*/

	GLint cameraSel = 0, cameraSelAnt = 0;

	/* Animar Skybox */
	GLboolean animarSkybox = GL_FALSE;

	/* Animar montaña */
	GLboolean animarMont = GL_FALSE;

	/* Animar rueda */
	GLboolean animarRueda = GL_FALSE;

	/* Encender linterna */
	GLboolean prenderLintera = GL_FALSE;

	/* Encender luz puntual */
	GLboolean luzPuntual = GL_FALSE;

	/* Mover carro */
	GLfloat giraCarro = 0.0f;
	GLfloat avanzaCarro = 0.0f;

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}

	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getgira() { return gira; }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat gira;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

