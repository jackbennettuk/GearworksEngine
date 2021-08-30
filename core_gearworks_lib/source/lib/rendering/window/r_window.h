#ifndef R_WINDOW_H
#define R_WINDOW_H

#include <gearworks.h>

struct gearworks::window {
private:
	// GLFW handle to this window instance
	GLFWwindow *glfw_handle;

	// Window size properties
	int window_width, window_height;
	float aspect_ratio;

	// Window title
	string window_title;
public:
	/// <summary>
	/// Window default constructor - does not create a window. To do that, use the create_window() function.
	/// </summary>
	window();

	/// <summary>
	/// Creates a window and assigns it a GLFW window handle.
	/// </summary>
	/// <param name="title">The title of the window.</param>
	/// <param name="width">The width of the window (default is 720).</param>
	/// <param name="height">The width of the window (default is 480).</param>
	void create_window(string title, int sizeX = 720, int sizeY = 480);

	/// <summary>
	/// Reevaluates properties such as width and height variables.
	/// </summary>
	void reevaluate();

	/// <summary>
	/// Updates the window instance.
	/// </summary>
	void update_window();

	/// <returns>the unsigned int that has been assigned to this window for GLFW functions.</returns>
	inline GLFWwindow *get_glfwinstance() { return glfw_handle; }

	/// <returns>the window width.</returns>
	inline int get_winwidth() { return window_width; }
	/// <returns>the window height.</returns>
	inline int get_winheight() { return window_height; }
	/// <returns>the window aspect ratio.</returns>
	inline float get_winasprat() { return aspect_ratio; }

	/// <returns>the window title.</returns>
	inline string get_wintitle() { return window_title; }
	/// <summary>
	/// Sets the window title with a given string as its parameter.
	/// </summary>
	inline void set_wintitle(string str) { window_title = str; glfwSetWindowTitle(glfw_handle, window_title.c_str()); }
};


#endif // header guard