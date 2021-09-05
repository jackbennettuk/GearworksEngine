#include "i_input.h"

gearworks::input_manager::input_manager()
	: window_ptr(nullptr), old_cursor_pos(vec2(0)), cursor_pos(vec2(0)), cursor_offset(vec2(0))
{}

void gearworks::input_manager::initialize(gearworks::window *window) {
	// Initialize variables
	window_ptr = window;
}

void gearworks::input_manager::update() {
	// Update the previous-pressed keyboard list before updating current list
	kb_previous_pressed_keys = kb_current_pressed_keys;
	// Clear current pressed keys list
	kb_current_pressed_keys.clear();
	// Increment through all possible keys available in GLFW
	for (int i = 0; i < 377; i++) {			// the value '377' is based on the extended ASCII table at https://www.ascii-code.com/
		if (glfwGetKey(window_ptr->get_glfwinstance(), i)) {
			// If each key is being pressed, add it to the kb_current_pressed_keys array.
			kb_current_pressed_keys.push_back(i);
		}
	}

	// Update cursor position variables
	old_cursor_pos = cursor_pos;
	glfwGetCursorPos(window_ptr->get_glfwinstance(), &cursor_pos.x, &cursor_pos.y);

	// Update cursor position offset
	cursor_offset = cursor_pos - old_cursor_pos;
}

bool gearworks::input_manager::get_key_down(int key) {
	// Conditions abstracted into vars for readability
	bool prev_found = std::find(kb_previous_pressed_keys.begin(), kb_previous_pressed_keys.end(), key) != kb_previous_pressed_keys.end();
	bool cur_found = std::find(kb_current_pressed_keys.begin(), kb_current_pressed_keys.end(), key) != kb_current_pressed_keys.end();

	// If the key is currently being pressed but was not previously pressed, return true.
	if (!prev_found && cur_found) {
		return true;
	}

	// If not, return false
	return false;
}

bool gearworks::input_manager::get_key(int key) {
	// Conditions abstracted into vars for readability
	bool prev_found = std::find(kb_previous_pressed_keys.begin(), kb_previous_pressed_keys.end(), key) != kb_previous_pressed_keys.end();
	bool cur_found = std::find(kb_current_pressed_keys.begin(), kb_current_pressed_keys.end(), key) != kb_current_pressed_keys.end();

	// If the key is currently pressed down and was pressed down last frame, return true.
	if (prev_found && cur_found) {
		return true;
	}

	// If not, return false
	return false;
}

bool gearworks::input_manager::get_key_release(int key) {
	// Conditions abstracted into vars for readability
	bool prev_found = std::find(kb_previous_pressed_keys.begin(), kb_previous_pressed_keys.end(), key) != kb_previous_pressed_keys.end();
	bool cur_found = std::find(kb_current_pressed_keys.begin(), kb_current_pressed_keys.end(), key) != kb_current_pressed_keys.end();

	// If the key was previously pressed but not currently, return true.
	if (prev_found && !cur_found) {
		return true;
	}

	// If not, return false
	return false;
}

void gearworks::input_manager::center_cursor() {
	// Find center of window and set the cursor's position to that
	cursor_pos.x = round(window_ptr->get_winwidth() / 2);
	cursor_pos.y = round(window_ptr->get_winheight() / 2);

	// Then update the actual position of the cursor
	glfwSetCursorPos(window_ptr->get_glfwinstance(), cursor_pos.x, cursor_pos.y);
}