#include "gwengine.h"
#include "gwutility.h"

#include <depGL/Glad/glad.h>
#include <depGL/GLFW3/glfw3.h>

#include <iostream>

#include "gwrendering.h"

// The width of the window
#define WIN_WIDTH 720
// The height of the window
#define WIN_HEIGHT 480

// The type of release for the program version
#define __PROG_CONFIG__ "development"
// The major version number of the program
#define __PROG_VERSION_MAJOR__ "1"
// The minor version number of the program
#define __PROG_VERSION_MINOR__ "2"

// Handle to the main window used by the Gearworks Engine
GLFWwindow *mainWindow;
// The main shader program in use for the Gearworks Engine
unsigned int mainShaderProgram;

/// <summary>
/// <para>Initializes all required shaders for the program.</para>
/// <para>Currently, the shaders implemented in this function are:</para>
/// <para>  - Vertex</para>
///	<para>  - Fragment</para>
/// </summary>
void InitializeShaders() {
	// Create the main shader program
	mainShaderProgram = glCreateProgram();

	// Necessary shaders - they are destroyed when outside the InitializeShaders scope
	Shader vertexShader("resources/shaders/.vert", GL_VERTEX_SHADER, mainShaderProgram);		// Vertex shader
	Shader fragmentShader("resources/shaders/.frag", GL_FRAGMENT_SHADER, mainShaderProgram);	// Fragment shader
}

/// <summary>
/// The main function of the program.
/// </summary>
int main() {
	// Create the window title with version, e.g. "Gearworks Rendering Engine - release version 3.2"
	std::string winTitle = "Gearworks Rendering Engine - ";
	winTitle += __PROG_CONFIG__; winTitle += " version "; winTitle += __PROG_VERSION_MAJOR__; winTitle += "."; winTitle += __PROG_VERSION_MINOR__;

	// Set the GLFW error callback before initialization so that it can give any errors when initializing as well as during runtime
	glfwSetErrorCallback(util::glfwErrorCallback);

	// Initialize GLFW
	std::cout << "[GW] Initializing GLFW... ";
	CONASSERT(glfwInit());

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL version = 3.3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// ...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// OpenGL profile = core

	// Create the window
	std::cout << "[GW] Creating the window... ";
	mainWindow = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, winTitle.c_str(), NULL, NULL);
	CONASSERT(mainWindow);

	// Set mainWindow to be the current OpenGL context
	glfwMakeContextCurrent(mainWindow);

	// Set the OpenGL swap interval to 1
	glfwSwapInterval(1);

	// Initialize Glad
	std::cout << "[GW] Loading Glad... ";
	CONASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	// Initialize the shaders
	InitializeShaders();
	// Initially unbind the current shader program so any previous ones are cleared
	glUseProgram(0);

	// Main program loop
	while (!glfwWindowShouldClose(mainWindow)) {
		// Swap buffers and poll window events
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();

	// End the application successfully
	return 0;
}