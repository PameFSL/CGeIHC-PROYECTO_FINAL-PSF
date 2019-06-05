#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	gira = 0.0f;
	width = windowWidth;
	height = windowHeight;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "La feria del pueblo", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	theWindow->cameraSelAnt = 0;

	// INICIO: CAMARA -------------------------------------------------------------------
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		theWindow->cameraSel = 0;
		theWindow->cameraSelAnt = 1;
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		theWindow->cameraSel = 1;
		theWindow->cameraSelAnt = 1;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		theWindow->cameraSel = 2;
		theWindow->cameraSelAnt = 1;
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		theWindow->cameraSel = 3;
		theWindow->cameraSelAnt = 1;
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		theWindow->cameraSel = 4;
		theWindow->cameraSelAnt = 1;
	}

	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		theWindow->cameraSel = 5;
		theWindow->cameraSelAnt = 1;
	}

	// FIN: CAMARA ---------------------------------------------------------------------
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		theWindow->animarSkybox = GL_TRUE;
	}

	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		theWindow->animarSkybox = GL_FALSE;
	}


	// Animar montaña

	if (key == GLFW_KEY_L && action == GLFW_PRESS)
		theWindow->animarMont = GL_TRUE;

	if (key == GLFW_KEY_K && action == GLFW_PRESS)
		theWindow->animarMont = GL_FALSE;

	// Animar Rueda

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		theWindow->animarRueda = GL_TRUE;

	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		theWindow->animarRueda = GL_FALSE;

	// Prender linterna

	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
		theWindow->prenderLintera = GL_TRUE;

	if (key == GLFW_KEY_8 && action == GLFW_PRESS)
		theWindow->prenderLintera = GL_FALSE;

	// Prender luz puntual

	if (key == GLFW_KEY_7 && action == GLFW_PRESS)
		theWindow->luzPuntual = GL_TRUE;

	if (key == GLFW_KEY_6 && action == GLFW_PRESS)
		theWindow->luzPuntual = GL_FALSE;


	// Mover carro
	if (key == GLFW_KEY_F )
		theWindow->giraCarro += 2.0f;

	if (key == GLFW_KEY_H )
		theWindow->giraCarro -= 2.0f;

	if (key == GLFW_KEY_T )
		theWindow->avanzaCarro += 0.06f;

	if (key == GLFW_KEY_G)
		theWindow->avanzaCarro -= 0.06f;

	// Animar SkyBox


	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}
	
	//******************************
	if (key == GLFW_KEY_X)
	{
		theWindow->gira -= 75.0;
	}
	//*******************************

	
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
	
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
