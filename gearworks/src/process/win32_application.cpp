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

/// <summary>
/// <para>The main function of the program.</para>
/// </summary>
int main() {
	// Create the main renderer instance...
	GWRenderer mainRenderer;
	// ...and the main engine instance
	Engine engine(&mainRenderer);

	// Set the console window's title. In future release builds, this console window will be optional but available for debugging.
	SetConsoleTitle(L"Gearworks Engine Debug Prompt");

	// Initialize GLFW
	std::cout << "[GW] Initializing: Loading GLFW... ";
	CONASSERT(glfwInit());

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// OpenGL version = 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// ...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// OpenGL profile = core

	// Create the window
	GWRenderer::GWWindow mainWindow("Gearworks Engine: Powered by OpenGL");

	// Initialize Glad
	std::cout << "[GW] Initializing: Loading Glad... ";
	CONASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	// Explicity set the OpenGL viewport size to be the window size
	glViewport(0, 0, mainWindow.GetWindowSizeX(), mainWindow.GetWindowSizeY());

	// Print the name of the engine as ASCII art because why not :D
	std::cout << "\n----------\n   _____                                   _        \n  / ____|                                 | |       \n | |  __  ___  __ _ _____      _____  _ __| | _____ \n"
		" | | |_ |/ _ \\/ _` | '_\\ \\ /\\ / / _ \\| '__| |/ / __|\n | |__| |  __/ (_| | |  \\ V  V / (_) | |  |   <\\__ \\\n  \\_____|\\___|\\__,_|_|   \\_/\\_/ \\___/|_|  |_|\\_\\___/\n"
		"\nBy Jack Bennett\n----------\n";

	// Enable transparent blending through the main renderer instance
	mainRenderer.EnableTransparentBlending();

	// Set up shaders
	mainRenderer.InitializeShaders();

	// Initialize the engine
	engine.Initialize();

	// Initialize the coordinate system
	mainRenderer.InitializeOrthoProjection();

	// Clear shader program
	mainRenderer.UnbindShaderProgram();

	// Update the title with the current-used OpenGL version
	std::string _newWinTitle = "Gearworks Engine: Running OpenGl version "; _newWinTitle += (const char *)glGetString(GL_VERSION);
	mainWindow.SetWindowTitle(_newWinTitle);

	// Main program loop
	while (!glfwWindowShouldClose(mainWindow.GetGLFWInstance())) {
		// Clear the screen with a dark gray colour
		GWRenderer::ClearScreen(glm::vec4(0.12f, 0.12f, 0.12f, 1.0f));

		// Update the engine instance
		engine.Update();
		// Bind the shader program
		mainRenderer.BindShaderProgram();
		// Render the engine instance
		engine.Render();

		// Update the window instance
		mainWindow.UpdateWindow();
	}

	// Clean the main instance of Engine.cpp
	engine.Clean();

	// Unbind shader program
	mainRenderer.UnbindShaderProgram();

	// Terminate GLFW
	glfwTerminate();

	// End the application successfully
	return 0;
}