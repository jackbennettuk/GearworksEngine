#include "defs.h"

#pragma region Engine

gearworks::engine::engine()
	: renderer_handle(nullptr) {
}

void gearworks::engine::create(gearworks::renderer *_renderer) {
	// Updates private pointer to the renderer to the user-given renderer.
	renderer_handle = _renderer;
}

// The rest of 'Engine' will be defined by the user with their own code.

#pragma endregion
#pragma region GWehaviour

void gearworks::gwehaviour::initialize() {
	// Create the engine object
	main_engine.create(&renderer);

	// Set the console window's title. In future release builds, this console window can be optional but available for debugging.
	SetConsoleTitle(L"Gearworks Engine Debug Prompt");

	// Initialize GLFW
	GW_INIT_GLFW();

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// Minimum OpenGL version = 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// ...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// OpenGL profile = core
	glfwWindowHint(GLFW_SAMPLES, 4);									// Multisampling for MSAA anti-aliasing = 4 samples

	// Create the window
	renderer.create_window("Gearworks Engine - development version - by Jack Bennett");

	// Load Glad
	GW_INIT_GLAD();

	// Enable multi-sample anti-aliasing
	// TODO: make this an option for lower-end machines
	GL_CALL(glEnable(GL_MULTISAMPLE));

	// Enable transparent blending through the main renderer instance
	gearworks::config_blending();
	// Set up shaders
	renderer.initialize_shaders(vertex_shader_path, fragment_shader_path);
	// Update the renderer for the first time (basically initializing it)
	renderer.update_renderer();

	// Initialize the engine object
	main_engine.initialize();

	// Initialize the input manager
	input.initialize(renderer.get_currentwindowinstance());
}

void gearworks::gwehaviour::update() {
	while (!glfwWindowShouldClose(renderer.get_currentwindowinstance()->get_glfwinstance())) {
		// Bind the shader program
		gearworks::bind_program(*(renderer.get_currentshaderprogram()));

		// Update the renderer
		renderer.update_renderer();
		// Update the engine instance
		main_engine.update();

		// Update the input manager
		input.update();

		// Render the engine instance
		main_engine.render();
		// Update the window instance
		renderer.get_currentwindowinstance()->update_window();
	}
}

void gearworks::gwehaviour::destroy() {
	// Print a success message
	std::cout << "Window successfully closed; process ended.\n";

	// Destroy the engine
	main_engine.clean();
	// Unbind shader program
	gearworks::unbind_program();
	// Terminate GLFW
	glfwTerminate();
}

#pragma endregion