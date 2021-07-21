#ifndef KEYBOARD_INPUT_MGMT_H
#define KEYBOARD_INPUT_MGMT_H

#include <gearworks.h>

#include <list>

// The amount of possible GLFW key inputs as keycodes, or ints.
#define GW_KEY_AMOUNT GLFW_KEY_MENU - 1

class keyboard {
private:
	// Pointer to the window
	gw_window *window_ptr;

	// Lists of current and previous pressed keys
	std::list<int> current_pressed_keys, previous_pressed_keys;
public:
	/// <summary>
	/// <para>Constructor for a GW Keyboard object. To initialize the object, use initialize_keyboard().</para>
	/// </summary>
	keyboard();

	/// <summary>
	/// <para>Initalizes a keyboard manager.</para>
	/// </summary>
	/// <param name="window">The window from which input will be detected.</param>
	void initialize_keyboard(gw_window *window);

	/// <summary>
	/// <para>Updates the lists of pressed keys.</para>
	/// </summary>
	void update_keyboard();

	/// <summary>
	/// <para>Returns true on the frame that a key is pressed down.</para>
	/// </summary>
	/// <param name="key">The key code of the key to check. It is recommended you use GLFW codes, such as "GLFW_KEY_ENTER" or others.</param>
	/// <param name="key">A project-specific enum for Keys may be created in the future.</param>
	bool get_key_down(int key);

	/// <summary>
	/// <para>Returns true for as long as a key is being held down.</para>
	/// </summary>
	/// <param name="key">The key code of the key to check. It is recommended you use GLFW codes, such as "GLFW_KEY_ENTER" or others.</param>
	/// <param name="key">A project-specific enum for Keys may be created in the future.</param>
	bool get_key(int key);

	/// <summary>
	/// <para>Returns true for as long as a key is being held down.</para>
	/// </summary>
	/// <param name="key">The key code of the key to check. It is recommended you use GLFW codes, such as "GLFW_KEY_ENTER" or others.</param>
	/// <param name="key">A project-specific enum for Keys may be created in the future.</param>
	bool get_key_release(int key);
};

#endif