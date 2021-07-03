#include "gwengine.h"
#include "gwutility.h"
#include "gwrendering.h"

#include <depGL/Glad/glad.h>
#include <depGL/GLFW3/glfw3.h>
#include <depGL/glm/gtc/matrix_transform.hpp>

#include <iostream>
#undef APIENTRY
#include <Windows.h>
#include <time.h>

// The width of the window
#define WIN_WIDTH 720
// The height of the window
#define WIN_HEIGHT 480

// The type of release for the program version
#define __PROG_CONFIG__ "development"
// The major version number of the program
#define __PROG_VERSION_MAJOR__ "d1"
// The minor version number of the program
#define __PROG_VERSION_MINOR__ "5.1"

// Handle to the main window used by the Gearworks Engine
GLFWwindow *mainWindow;
// The main shader program in use for the Gearworks Engine
unsigned int mainShaderProgram;

// The main engine instance
Engine engine(&mainShaderProgram);

/// <summary>
/// <para>Initializes all required shaders for the program.</para>
/// <para>Currently, the shaders implemented in this function are:</para>
/// <para>  - Vertex</para>
///	<para>  - Fragment</para>
/// </summary>
void InitializeShaders();

/// <summary>
/// <para>The main function of the program.</para>
/// </summary>
int main() {
	// Colour variables
	util::ColourRGBA255 bgCol = util::ColourRGBA255(38, 38, 38, 255);

	// Create the window title with version, e.g. "Gearworks Rendering Engine - release version 3.2"
	std::string winTitle = "Gearworks Rendering Engine (OpenGL) - ";
	winTitle += __PROG_CONFIG__; winTitle += " version "; winTitle += __PROG_VERSION_MAJOR__; winTitle += "."; winTitle += __PROG_VERSION_MINOR__;

	// Set the console window's title. In future release builds, this console window will be optional but available for debugging.
	SetConsoleTitle(L"Gearworks Engine Debug Prompt");

	// Set the GLFW error callback before initialization so that it can give any errors when initializing as well as during runtime
	glfwSetErrorCallback(util::glfwErrorCallback);

	// Initialize GLFW
	std::cout << "[GW] Initializing: Loading GLFW... ";
	CONASSERT(glfwInit());

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL version = 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// ...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// OpenGL profile = core

	// Create the window
	std::cout << "[GW] Initializing: Creating the window... ";
	mainWindow = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, winTitle.c_str(), NULL, NULL);
	CONASSERT(mainWindow);

	// Set mainWindow to be the current OpenGL context
	glfwMakeContextCurrent(mainWindow);

	// Set the OpenGL swap interval to 1
	glfwSwapInterval(1);

	// Initialize Glad
	std::cout << "[GW] Initializing: Loading Glad... ";
	CONASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	// Initialize the shaders
	InitializeShaders();

	// Create the main VAO
	VertexArrayObject vao;

	// Bind it so that any shapes can be initialized next
	vao.Bind();
	// Initialize the engine now so any shapes in it can be initialized after the vao has been bound
	engine.Initialize();
	// Then unbind it so it can be bound every frame when rendering instead of just at initialization
	vao.Unbind();

	// Initialize the coordinate system
	util::coord::InitWorldCoordSystem(&mainShaderProgram, 500.0f);

	// Print the version of OpenGL
	std::cout << std::endl << "[OpenGL] Running OpenGL version " << glGetString(GL_VERSION) << "\n\n----------";

	// Print a welcome message
	std::cout << std::endl << "   _____                                   _        \n  / ____|                                 | |       \n | |  __  ___  __ _ _____      _____  _ __| | _____ \n"
		" | | |_ |/ _ \\/ _` | '_\\ \\ /\\ / / _ \\| '__| |/ / __|\n | |__| |  __/ (_| | |  \\ V  V / (_) | |  |   <\\__ \\\n  \\_____|\\___|\\__,_|_|   \\_/\\_/ \\___/|_|  |_|\\_\\___/" << std::endl;
	std::cout << "\nBy Jack Bennett\n----------" << std::endl;

	// Main program loop
	while (!glfwWindowShouldClose(mainWindow)) {
		// Change the background colour to a dark gray
		GL_CALL(glClearColor(bgCol.r, bgCol.g, bgCol.b, bgCol.a));
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		// Update the engine instance
		engine.Update();

		// Bind the shader program
		GL_CALL(glUseProgram(mainShaderProgram));
		// Bind the vertex array
		vao.Bind();

		// Render the engine instance
		engine.Render();

		// Swap buffers
		glfwSwapBuffers(mainWindow);

		// Poll window events
		glfwPollEvents();
	}

	// Unbind the VAO
	vao.Unbind();
	// Clean the main instance of Engine.cpp
	engine.Clean();

	// Terminate GLFW
	glfwTerminate();

	// End the application successfully
	return 0;
}

// InitializeShaders() implementation
void InitializeShaders() {
	// Create the main shader program
	mainShaderProgram = glCreateProgram();

	// Necessary shaders - they are destroyed when outside the InitializeShaders scope
	Shader vertexShader("resources/shaders/.vert", GL_VERTEX_SHADER, mainShaderProgram);		// Vertex shader
	Shader fragmentShader("resources/shaders/.frag", GL_FRAGMENT_SHADER, mainShaderProgram);	// Fragment shader

	GL_CALL(glUseProgram(mainShaderProgram));
}