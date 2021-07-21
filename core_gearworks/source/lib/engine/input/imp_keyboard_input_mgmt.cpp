#include "keyboard_input_mgmt.h"

keyboard::keyboard()
	: window_ptr(nullptr)
{}

void keyboard::initialize_keyboard(gw_window *window) {
	// Initialize variables
	window_ptr = window;
}

void keyboard::update_keyboard() {
	// Update the previous-pressed keyboard list before updating current list
	previous_pressed_keys = current_pressed_keys;

	// Clear current pressed keys list
	current_pressed_keys.clear();

	// Increment through all possible keys available in GLFW
	for (int i = 0; i < GW_KEY_AMOUNT; i++) {
		if (glfwGetKey(window_ptr->get_glfwinstance(), i)) {
			// If each key is being pressed, add it to the current_pressed_keys array.
			current_pressed_keys.push_back(i);
		}
	}
}

bool keyboard::get_key_down(int key) {
	// Conditions abstracted into vars for readability
	bool prev_found = std::find(previous_pressed_keys.begin(), previous_pressed_keys.end(), key) != previous_pressed_keys.end();
	bool cur_found = std::find(current_pressed_keys.begin(), current_pressed_keys.end(), key) != current_pressed_keys.end();

	// If the key is currently being pressed but was not previously pressed, return true.
	if (!prev_found && cur_found) {
		return true;
	}

	// If not, return false
	return false;
}

bool keyboard::get_key(int key) {
	// Conditions abstracted into vars for readability
	bool prev_found = std::find(previous_pressed_keys.begin(), previous_pressed_keys.end(), key) != previous_pressed_keys.end();
	bool cur_found = std::find(current_pressed_keys.begin(), current_pressed_keys.end(), key) != current_pressed_keys.end();

	// If the key is currently pressed down and was pressed down last frame, return true.
	if (prev_found && cur_found) {
		return true;
	}

	// If not, return false
	return false;
}

bool keyboard::get_key_release(int key) {
	// Conditions abstracted into vars for readability
	bool prev_found = std::find(previous_pressed_keys.begin(), previous_pressed_keys.end(), key) != previous_pressed_keys.end();
	bool cur_found = std::find(current_pressed_keys.begin(), current_pressed_keys.end(), key) != current_pressed_keys.end();

	// If the key was previously pressed but not currently, return true.
	if (prev_found && !cur_found) {
		return true;
	}

	// If not, return false
	return false;
}