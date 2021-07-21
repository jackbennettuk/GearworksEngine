#include "mouse_input_mgmt.h"

cursor::cursor() 
	: window_ptr(nullptr), x_pos(0.0), y_pos(0.0)
{}

void cursor::initialize_cursor(gw_window *window) {
	// Initialize window pointer
	window_ptr = window;
}

void cursor::update_cursor() {
	// Update the position variables
	glfwGetCursorPos(window_ptr->get_glfwinstance(), &x_pos, &y_pos);
}