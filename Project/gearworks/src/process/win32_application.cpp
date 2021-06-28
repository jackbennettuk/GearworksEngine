#include "gwengine.h"
#include "gwutility.h"

#include <depGL/Glad/glad.h>
#include <depGL/GLFW3/glfw3.h>

#include <iostream>

#define WIN_WIDTH 720
#define WIN_HEIGHT 480

#define __PROG_CONFIG__ "Development"
#define __PROG_VERSION_MAJOR__ "0"
#define __PROG_VERSION_MINOR__ "2"

GLFWwindow *mainWindow;

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