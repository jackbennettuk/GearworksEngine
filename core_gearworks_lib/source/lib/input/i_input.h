#ifndef I_INPUT_H
#define I_INPUT_H

#include <gearworks.h>

class gearworks::input_manager {
private:
	// Pointer to the window
	gearworks::window *window_ptr;

	// --- KEYBOARD MEMBER(S) ---
	std::list<int> kb_current_pressed_keys, kb_previous_pressed_keys;						// Lists of current and previous pressed keys

	// --- CURSOR MEMBER(S) ---
	double cursor_x_pos, cursor_y_pos;														// X and Y positions of the cursor
public:
	// Getters and/or setters
	/// <returns>the x position of the cursor.</returns>
	inline double get_cursorxpos() { return cursor_x_pos; }
	/// <returns>the y position of the cursor.</returns>
	inline double get_cursorypos() { return cursor_y_pos; }

	/// <summary>
	/// Constructor for an input manager. To create an object of this class, use the initialize() function.</par>
	/// </summary>
	input_manager();

	/// <summary>
	/// Creates the input manager object.
	/// </summary>
	void initialize(gearworks::window *window);
	/// <summary>
	/// Updates the input manager object.
	/// </summary>
	void update();

	/// <summary>
	/// Returns true on the frame that a key is pressed down.
	/// </summary>
	/// <param name="key">The key code of the key to check. It is recommended you use GLFW codes, such as "GLFW_KEY_ENTER" or others.</param>
	/// <param name="key">A project-specific enum for Keys may be created in the future.</param>
	bool get_key_down(int key);

	/// <summary>
	/// Returns true for as long as a key is being held down.
	/// </summary>
	/// <param name="key">The key code of the key to check. It is recommended you use GLFW codes, such as "GLFW_KEY_ENTER" or others.</param>
	/// <param name="key">A project-specific enum for Keys may be created in the future.</param>
	bool get_key(int key);

	/// <summary>
	/// Returns true for as long as a key is being held down.
	/// </summary>
	/// <param name="key">The key code of the key to check. It is recommended you use GLFW codes, such as "GLFW_KEY_ENTER" or others.</param>
	/// <param name="key">A project-specific enum for Keys may be created in the future.</param>
	bool get_key_release(int key);
};

#endif // header guard