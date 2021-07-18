#include <iostream>
#undef APIENTRY
#include <Windows.h>

#include <opengl_pack.h>
#include <gearworks.h>

int main() {
	// Renderer instance
	gw_renderer main_renderer;
	// Engine object
	engine main_engine(&main_renderer);

	// Set the console window's title. In future release builds, this console window can be optional but available for debugging.
	SetConsoleTitle(L"Gearworks Engine Debug Prompt");

	// Initialize GLFW
	GW_INIT_GLFW();

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// Minimum OpenGL version = 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// ...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// OpenGL profile = core
	glfwWindowHint(GLFW_SAMPLES, 4);									// 4 samples for MSAA anti-aliasing

	// Create the window
	main_renderer.create_window("Gearworks Engine 3D Renderer - development version - by Jack Bennett");

	// Load Glad
	GW_INIT_GLAD();

	GL_CALL(glEnable(GL_MULTISAMPLE));

	// Enable transparent blending through the main renderer instance
	gw_rendering_pl::gw_config_blending();
	// Set up shaders
	main_renderer.initialize_shaders();
	// Update the renderer for the first time (basically initializing it)
	main_renderer.update_renderer();

	// Initialize the engine object
	main_engine.initialize();

	// Main program loop
	while (!glfwWindowShouldClose(main_renderer.get_currentwindowinstance().get_glfwinstance())) {
		// Clear the screen with a dark gray colour
		gw_rendering_pl::gw_clear_screen(glm::vec4(0.12f, 0.12f, 0.12f, 1.0f));

		// Bind the shader program
		gw_rendering_pl::gw_bind_program(*(main_renderer.get_currentshaderprogram()));

		// Update the renderer
		main_renderer.update_renderer();

		// Update the engine instance
		main_engine.update();
		// Render the engine instance
		main_engine.render();

		// Update the window instance
		main_renderer.get_currentwindowinstance().update_window();
	}

	// Print a success message
	std::cout << "Window successfully closed; process ended.\n";

	// 'Clean the engine'
	main_engine.clean();
	// Unbind shader program
	gw_rendering_pl::gw_unbind_program();
	// Terminate GLFW
	glfwTerminate();

	// End the application successfully
	return 0;
}