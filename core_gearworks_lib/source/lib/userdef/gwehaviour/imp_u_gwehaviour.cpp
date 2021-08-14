#include "u_gwehaviour.h"

gearworks::gwehaviour::~gwehaviour() {
	DELETE_HALLOC(main_engine);
	DELETE_HALLOC(renderer);
	DELETE_HALLOC(input);
}

void gearworks::gwehaviour::initialize() {
	// Heap-allocate non-static objects
	main_engine = new gearworks::engine();
	renderer = new gearworks::renderer();
	input = new gearworks::input_manager();

	// Get Windows Console instance
	HANDLE win_console_instance = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the console window's title
	SetConsoleTitle(L"Gearworks Engine Debug Prompt");
	// Set console text colour to green
	SetConsoleTextAttribute(win_console_instance, 10);

	// Print debug console title
	std::cout << "  -- GEARWORKS ENGINE DEBUG CONSOLE --\nRevision 1.0.0: Windows-only compatibility\n";

	// Print initializing title
	std::cout << "\nInitializing:\n";

	// Create the engine object
	main_engine->create(renderer);

	// Initialize GLFW
	GW_INIT_GLFW();

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						// Minimum OpenGL version = 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						// ...
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		// OpenGL profile = core
	glfwWindowHint(GLFW_SAMPLES, 4);									// Multisampling for MSAA anti-aliasing = 4 samples

	// Create the window
	renderer->create_window("Gearworks Engine - development version");

	// Load Glad
	GW_INIT_GLAD();

	// Enable multi-sample anti-aliasing
	// TODO: make this an option for lower-end machines
	GL_CALL(glEnable(GL_MULTISAMPLE));

	// Enable transparent blending through the main renderer instance
	gearworks::config_blending();
	// Set up shaders
	renderer->initialize_shaders(vertex_shader_path, fragment_shader_path);
	// Update the renderer for the first time (basically initializing it)
	renderer->update_renderer();

	// Initialize the engine object
	main_engine->initialize();

	// Initialize the input manager
	input->initialize(renderer->get_currentwindowinstance());

	// Then print the OpenGL version
	std::cout << "\nRunning engine:\n";
	std::cout << "  Running with minimum OpenGL version " << glGetString(GL_VERSION) << ".\n";
}

void gearworks::gwehaviour::update() {
	while (!glfwWindowShouldClose(renderer->get_currentwindowinstance()->get_glfwinstance())) {
		// Bind the shader program
		gearworks::bind_program(*(renderer->get_currentshaderprogram()));

		// Update the renderer
		renderer->update_renderer();
		// Update the engine instance
		main_engine->update();

		// Update the input manager
		input->update();

		// Render the engine instance
		main_engine->render();
		// Update the window instance
		renderer->get_currentwindowinstance()->update_window();
	}
}

void gearworks::gwehaviour::destroy() {
	std::cout << "\nTermination:\n";
	std::cout << "  Window successfully closed.\n";

	// Destroy the engine
	main_engine->clean();
	// Unbind shader program
	gearworks::unbind_program();

	// Terminate GLFW
	glfwTerminate();
	std::cout << "  GLFW terminated.\n";

	// Done!
	std::cout << "  Done!\n";

	// Prompt the user to press any key to close the console window
	std::cout << "\n  -- Press enter to close the debug window. --";
	std::cin.get();
}