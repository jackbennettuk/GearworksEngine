#include "r_window.h"

gearworks::window::window()
	: window_title(""), window_width(0), window_height(0), aspect_ratio(0), glfw_handle(0)
{}

void gearworks::window::create_window(std::string title, int width, int height) {
	// initialize properties with arguments
	window_title = title;
	window_width = width;
	window_height = height;

	// Set the aspect ratio
	aspect_ratio = (float)window_width / (float)window_height;

	// Create the window
	std::cout << "[GW] Creating window... ";
	glfw_handle = glfwCreateWindow(window_width, window_height, window_title.c_str(), NULL, NULL);

	// Assert the now-created window
	if (!glfw_handle) {
		std::cout << "Error creating the window: the member \"glfw_handle\" does not exist!\n";
	} else {
		std::cout << "Successful!\n";
	}

	// Set this window to be the current OpenGL context
	glfwMakeContextCurrent(glfw_handle);
	// Set the OpenGL swap interval to 1
	glfwSwapInterval(1);
}

void gearworks::window::reevaluate() {
	// Update the window size variables
	glfwGetFramebufferSize(glfw_handle, &window_width, &window_height);
	// Update the aspect ratio
	aspect_ratio = (float)window_width / (float)window_height;
}

void gearworks::window::update_window() {
	// Swap buffers
	glfwSwapBuffers(glfw_handle);
	// Poll window events
	glfwPollEvents();
}

#pragma endregion