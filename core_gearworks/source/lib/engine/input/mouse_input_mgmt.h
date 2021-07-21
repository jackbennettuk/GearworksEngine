#ifndef MOUSE_INPUT_MGMT_H
#define MOUSE_INPUT_MGMT_H

#include <gearworks.h>

class cursor {
private:
	// X and Y positions of the cursor
	double x_pos, y_pos;

	// Pointer to the window that cursor events will be polled from
	gw_window *window_ptr;
public:
	/// <summary>
	/// <para>Constructor for a GW Cursor object. To initialize the object, use initialize_cursor().</para>
	/// </summary>
	cursor();

	void initialize_cursor(gw_window *window);

	/// <summary>
	/// <para>Updates the cursor object.</para>
	/// </summary>
	void update_cursor();
	
	// Position getters
	inline double get_cursorxpos() { return x_pos; }
	inline double get_cursorypos() { return y_pos; }
};

#endif