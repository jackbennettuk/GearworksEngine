#ifndef RENDERPL_H
#define RENDERPL_H

#include <opengl_pack.h>

// Struct to handle windows
struct gw_window {
private:
	// GLFW handle to this window instance
	GLFWwindow *glfw_handle;

	// Window size properties
	int window_width, window_height;
	float aspect_ratio;

	// Window title
	std::string window_title;
public:
	/// <summary>
	/// <para>Window default constructor - does not create a window. To do that, use the create_window() function.</para>
	/// </summary>
	gw_window();

	/// <summary>
	/// <para>Creates a window and assigns it a GLFW window handle.</para>
	/// </summary>
	/// <param name="title">The title of the window.</param>
	/// <param name="width">The width of the window (default is 720).</param>
	/// <param name="height">The width of the window (default is 480).</param>
	void create_window(std::string title, int sizeX = 720, int sizeY = 480);

	/// <summary>
	/// <para>Reevaluates properties such as width and height variables.</para>
	/// </summary>
	void reevaluate();

	/// <summary>
	/// <para>Updates the window instance.</para>
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
	inline std::string get_wintitle() { return window_title; }
	/// <summary>
	/// <para>Sets the window title with a given string as its parameter.</para>
	/// </summary>
	inline void set_wintitle(std::string str) { window_title = str; glfwSetWindowTitle(glfw_handle, window_title.c_str()); }
};

// Class for only static members and functions
class gw_rendering_pl {
public:
	/// <summary>
	/// <para>Sets up blending to allow for transparent pixels or textures.</para>
	/// </summary>
	static void gw_config_blending();

	/// <summary>
	/// <para>Clears the screen of the window assigned to the current OpenGL context.</para>
	/// </summary>
	/// <param name="colour">The colour of the screen to clear. If not given, the screen will be cleared to black.</param>
	static void gw_clear_screen(glm::vec4 colour);

	/// <summary>
	/// <para>Binds a given shader program.</para>
	/// </summary>
	/// <param name="shader_program_id"></param>
	static void gw_bind_program(unsigned int shader_program_id);
	/// <summary>
	/// <para>Unbinds the shader program.</para>
	/// </summary>
	static void gw_unbind_program();

	/// <summary>
	/// <para>Turns wireframe rendering on or off.</para>
	/// </summary>
	/// <param name="wireframe">Either on or off. Surely that doesn't need to be explained :/</param>
	static void gw_toggle_wireframe(bool wireframe);
};

// Class for nonstatic members and functions
class gw_renderer {
private:
	// Handle to the shader program for the renderer
	unsigned int cur_shader_program_id;
	// The window currently assigned to the renderer
	gw_window cur_window;
public:
	// Projection, view, and model matrices
	glm::mat4 project_matrix, view_matrix, model_matrix;

	/// <summary>
	/// <para>Constructor for the GW renderer.</para>
	/// </summary>
	gw_renderer();

	/// <summary>
	/// <para>Updates this instance of the renderer. Make sure to run this function every frame!</para>
	/// <para>Also important: run this function once at program initialization, too.</para>
	/// </summary>
	void update_renderer();

	/// <summary>
	/// <para>Creates a GLFW window with given title, size, and any other properties.</para>
	/// </summary>
	/// <param name="title">The title of the window.</param>
	/// <param name="sizeX">The width of the window.</param>
	/// <param name="sizeY">The height of the window.</param>
	void create_window(std::string title, int sizeX = 720, int sizeY = 480);

	/// <summary>
	/// <para>Initializes the global:</para>
	/// <para>  - vertex shader</para>
	/// <para>  - fragment shader</para>
	/// <para>and binds them to this renderer.</para>
	/// </summary>
	void initialize_shaders();

	/// <returns>the current shader program via its ID.</returns>
	inline unsigned int *get_currentshaderprogram() { return &cur_shader_program_id; }
	/// <returns>the current window.</returns>
	inline gw_window get_currentwindowinstance() { return cur_window; }
};

#endif