// Header to define classes and external macros.
// They are implemented seperately in their own categorized files.

#ifndef DEFS_H
#define DEFS_H

#include "../../include/gearworks.h"
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>

#include <Windows.h>

#include <opengl/glm/vec4.hpp>
#include <opengl/glm/mat4x4.hpp>
#include <opengl/glm/gtc/matrix_transform.hpp>

#include <opengl/Glad/glad.h>
#include <opengl/GLFW3/glfw3.h>

#include <stb/stb_image.h>

#pragma region Input

class gearworks::input_manager {
private:
	// Pointer to the window
	gearworks::window *window_ptr;

	// --- KEYBOARD MEMBER(S) ---
	std::list<int> current_pressed_keys, previous_pressed_keys;					// Lists of current and previous pressed keys

	// --- CURSOR MEMBER(S) ---
	double x_pos, y_pos;														// X and Y positions of the cursor
public:
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

	// Getters and/or setters
	/// <returns>the x position of the cursor.</returns>
	inline double get_cursorxpos() { return x_pos; }
	/// <returns>the y position of the cursor.</returns>
	inline double get_cursorypos() { return y_pos; }
};

#pragma endregion
#pragma region Rendering

#pragma region General

#pragma region Functions

void gearworks::config_blending() {
	// Enable blending for transparency
	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}
void gearworks::clear_screen(glm::vec3 colour) {
	// Change the background colour to the colour variable
	GL_CALL(glClearColor(colour.r, colour.g, colour.b, 1.0f));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void gearworks::bind_program(unsigned int shader_program_id) {
	// Bind a shader program via its id
	GL_CALL(glUseProgram(shader_program_id));
}

void gearworks::unbind_program() {
	// Unbind any shader programs
	GL_CALL(glUseProgram(0));
}

void gearworks::toggle_wireframe(bool wireframe) {
	// Set the OpenGl polygon mode accordingly.
	if (wireframe) {
		GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	} else {
		GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	}
}

#pragma endregion
#pragma region Classes

struct gearworks::window {
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
	/// Window default constructor - does not create a window. To do that, use the create_window() function.
	/// </summary>
	window();

	/// <summary>
	/// Creates a window and assigns it a GLFW window handle.
	/// </summary>
	/// <param name="title">The title of the window.</param>
	/// <param name="width">The width of the window (default is 720).</param>
	/// <param name="height">The width of the window (default is 480).</param>
	void create_window(std::string title, int sizeX = 720, int sizeY = 480);

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
	inline std::string get_wintitle() { return window_title; }
	/// <summary>
	/// Sets the window title with a given string as its parameter.
	/// </summary>
	inline void set_wintitle(std::string str) { window_title = str; glfwSetWindowTitle(glfw_handle, window_title.c_str()); }
};

class gearworks::renderer {
private:
	// Handle to the shader program for the renderer
	unsigned int cur_shader_program_id;
	// The window currently assigned to the renderer
	gearworks::window cur_window;

	// Zooming values
	float current_zoom;
	const float max_zoom = 2.5f, min_zoom = 0.1f;
public:
	/// <summary>
	/// Matrix used in calculation of the 'ModelViewProjection' or 'MVP' matrix.
	/// </summary>
	glm::mat4 project_matrix, view_matrix, model_matrix;

	/// <summary>
	/// Constructor for the GW renderer.
	/// </summary>
	renderer();

	/// <summary>
	/// Updates this instance of the renderer. Make sure to run this function every frame!
	/// Also important: run this function once at program initialization, too.
	/// </summary>
	void update_renderer();

	/// <summary>
	/// Creates a GLFW window with given title, size, and any other properties.
	/// </summary>
	/// <param name="title">The title of the window.</param>
	/// <param name="sizeX">The width of the window.</param>
	/// <param name="sizeY">The height of the window.</param>
	void create_window(std::string title, int sizeX = 720, int sizeY = 480);

	/// <summary>
	/// Initializes the global:
	///   - vertex shader
	///   - fragment shader
	/// and binds them to this renderer.
	/// </summary>
	/// <param name="vertex_shader_path">Path to the vertex shader to use.</param>
	/// <param name="fragment_shader_path">Path to the fragment shader to use.</param>
	void initialize_shaders(std::string vertex_shader_path = GW_NULLSTR, std::string fragment_shader_path = GW_NULLSTR);

	/// <summary>
	/// Zooms in and out by a given amount.
	/// When using this function, keep in mind that the minimum zoom is 0.1 and the maximum zoom is 2.5.
	/// </summary>
	/// <param name="amount">The amount to zoom by. To zoom in, set it to be positive, and to zoom out, set it to be negative.</param>
	void zoom_by_value(float amount);

	/// <returns>the current shader program via its ID.</returns>
	inline unsigned int *get_currentshaderprogram() { return &cur_shader_program_id; }
	/// <returns>the current window.</returns>
	inline gearworks::window *get_currentwindowinstance() { return &cur_window; }
};

#pragma endregion

#pragma endregion
#pragma region Shaders

struct gearworks::shader {
private:
	unsigned int shader_program_id = 0;
public:
	/// <summary>
	/// Constructor that creates, parses, compiles, and links a given shader.
	/// A new shader program is also created if needed.
	/// </summary>
	/// <param name="path">The path to the source file for the shader</param>
	/// <param name="type">The type of shader, given as an OpenGL macro</param>
	/// <param name="program">A handle to the program the shader should be linked to</param>
	shader(const std::string &path, unsigned int type, unsigned int program);

	/// <returns>the handle to the shader program that this shader is bound to</returns>
	inline unsigned int *get_shaderprogramid() { return &shader_program_id; }
};

#pragma endregion
#pragma region Buffer objects

class gearworks::vertex_array_object {
private:
	// The ID that is referred in GL commands such as glGenVertexArrays
	unsigned int renderer_id;
public:
	/// <returns>The renderer ID associated with this object.</returns>
	unsigned int get_rendererid();

	/// <summary>
	/// The default constructor for the VAO. IMPORTANT: This constructor does NOT generate a VAO! To do that, you must call vertex_array_object.initialize()!
	/// </summary>
	vertex_array_object();

	/// <summary>
	/// Initializes the VAO.
	/// </summary>
	void initialize();

	/// <summary>
	/// Adds a vertexattrib to a given vertex buffer with given parameters rather than a pre-made Vertex Buffer Layout.
	/// For parameter information please see the official documentation for the glVertexAttribPointer() OpenGL method.
	/// </summary>
	void add_vb_attrib(vertex_buffer_object &vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

	/// <summary>
	/// Binds the Vertex Array Object.
	/// </summary>
	void bind();
	/// <summary>
	/// Unbinds the Vertex Array Object.
	/// </summary>
	void unbind();
};
class gearworks::vertex_buffer_object {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int renderer_id;
public:
	/// <returns>The renderer ID associated with this object.</returns>
	unsigned int get_rendererid();

	/// <summary>
	/// The default constructor for the VBO. IMPORTANT: This constructor does NOT generate a VBO! To do that, you must call vertex_buffer_object.initialize()!
	/// </summary>
	vertex_buffer_object();

	/// <summary>
	/// Initializes the VBO.
	/// </summary>
	/// <param name="count">The amount of items in the array "data"</param>
	/// <param name="data">The array of positions, given as floats, for the VBO</param>
	void initialize(unsigned int count, float data[]);

	/// <summary>
	/// Binds the Vertex Buffer Object to GL_ARRAY_BUFFER
	/// </summary>
	void bind();
	/// <summary>
	/// Binds 0 to GL_ARRAY_BUFFER, overriding the Vertex Buffer Object
	/// </summary>
	void unbind();
};
class gearworks::index_buffer_object {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int renderer_id;
public:
	/// <returns>The renderer ID associated with this object.</returns>
	unsigned int get_rendererid();

	/// <summary>
	/// The default constructor for the IBO. IMPORTANT: This constructor does NOT generate a IBO! To do that, you must call index_buffer_object.initialize()!
	/// </summary>
	index_buffer_object();

	/// <summary>
	/// Initializes the IBO.
	/// </summary>
	/// <param name="count">The amount of indices.</param>
	/// <param name="data">The array of indices.</param>
	void initialize(unsigned int count, unsigned int data[]);

	/// <summary>
	/// Binds the Index Buffer Object to GL_ELEMENT_ARRAY_BUFFER
	/// </summary>
	void bind();
	/// <summary>
	/// Binds 0 to GL_ARRAY_BUFFER, overriding the Index Buffer Object
	/// </summary>
	void unbind();
};

#pragma endregion
#pragma region Textures

class gearworks::texture_2d {
private:
	// Renderer ID
	unsigned int renderer_id;
	// Path to the image file
	std::string path;
	// Texture properties - width, height, and bits-per-pixel.
	int width, height, bits_per_pixel;
public:
	/// <summary>
	/// Creates an empty texture object.
	/// </summary>
	texture_2d();

	/// <summary>
	/// Load a given image into the texture.
	/// </summary>
	/// <param name="_path">The path of the texture as a string.</param>
	void load(std::string _path);

	/// <summary>
	/// Binds the texture at a (optional) given slot.
	/// </summary>
	/// <param name="slot">(Optional) the texture slot to bind the texture to.</param>
	void bind(unsigned int slot = 0);
	/// <summary>
	/// Unbinds the texture.
	/// </summary>
	void unbind();

	/// <returns>the width of the texture in pixels.</returns>
	inline int get_width() const { return width; };
	/// <returns>the height of the texture in pixels.</returns>
	inline int get_height() const { return height; };
};

#pragma endregion

#pragma endregion
#pragma region Shapes

class gearworks::rectangle {
private:
	// Vectors to cache transformations that have not yet been applied.
	// These get released in the private apply_transformations() function, which is run directly before glDrawElements().
	glm::vec3 active_translation;
	glm::vec3 active_scaling;
	glm::vec3 active_rotation;

	// This function applies any outstanding transformations to the primitive.
	// It is only ever run in the base render() function, and so it can be private.
	// In order to publicly transform the primitive, use the translate(), scale(), and rotate() functions.
	void apply_transformations();

	// The default-used indices
	unsigned int indices[6] = { 0, 1, 2, 0, 3, 2 };

	// Pointer to renderer object
	gearworks::renderer *renderer_handle;

	// IBO and VAO
	gearworks::vertex_array_object vao;
	gearworks::index_buffer_object ibo;

	// Texture used for the primitive
	gearworks::texture_2d texture_object;
public:
	/// <summary>
	/// The blending colour of the rectangle
	/// </summary>
	glm::vec4 colour;
	/// <summary>
	/// The path to the texture of the rectangle
	/// </summary>
	std::string texture;

	/// <summary>
	/// Default constructor. Note: to actually create the rectangle with vertex coordinates etc, use the create() function.
	/// </summary>
	rectangle();

	/// <summary>
	/// Creates a Rectangle struct and its appropriate VBOs and IBO.
	/// A blend colour and a texture may be given.
	/// </summary>
	/// <param name="renderer">The renderer that the rectangle will be 'bound' to.</param>
	/// <param name="position">The starting position coordinate of the rectangle primitive, with 0 as its center.</param>
	/// <param name="scale">The scale values of the rectangle primitive.</param>
	/// <param name="texture_path">The texture to use for the rectangle.</param>
	/// <param name="blend_colour">The colour to render the rectangle. Default is white.</param>
	void create(gearworks::renderer *renderer, glm::vec3 position, glm::vec3 scale, std::string texture_path, glm::vec4 blend_colour = glm::vec4(1.0, 1.0, 1.0, 1.0));

	/// <summary>
	/// Renders the rectangle via glDrawElements.
	/// </summary>
	void render();

	/// <summary>
	/// Translates, or moves, the rectangle by a given distance.
	/// </summary>
	/// <param name="transformation">The distance to move by in x, y, and z.</param>
	inline void translate(glm::vec3 transformation) { active_translation += transformation; }		// cache a translation to be applied in render()
	/// <summary>
	/// Rotates the rectangle by a given amount.
	/// </summary>
	/// <param name="scaling">The amount to rotate by in degrees.</param>
	/// <param name="axes">The axes to rotate around.</param>
	inline void rotate(glm::vec3 rotation) { active_rotation += +glm::radians(rotation); }			// cache a rotation amount to be applied in render()
	/// <summary>
	/// Scales the rectangle by a given amount.
	/// </summary>
	/// <param name="scaling">The amount to scale by.</param>
	inline void scale(glm::vec3 scaling) { active_scaling += scaling; }								// cache an amount to be scaled by in render()
};
class gearworks::triangle {
private:
	// Vectors to cache transformations that have not yet been applied.
	// These get released in the private apply_transformations() function, which is run directly before glDrawElements().
	glm::vec3 active_translation;
	glm::vec3 active_scaling;
	glm::vec3 active_rotation;

	// This function applies any outstanding transformations to the primitive.
	// It is only ever run in the base render() function, and so it can be private.
	// In order to publicly transform the primitive, use the translate(), scale(), and rotate() functions.
	void apply_transformations();

	// The default-used indices
	unsigned int indices[3] = { 0, 1, 2 };

	// Pointer to renderer object
	gearworks::renderer *renderer_handle;

	// IBO and VAO
	gearworks::vertex_array_object vao;
	gearworks::index_buffer_object ibo;

	// Texture used for the primitive
	gearworks::texture_2d texture_object;
public:
	/// <summary>
	/// The blending colour of the triangle
	/// </summary>
	glm::vec4 colour;
	/// <summary>
	/// The path to the texture of the triangle
	/// </summary>
	std::string texture;

	/// <summary>
	/// Default constructor. Note: to actually create the rectangle with vertex coordinates etc, use the create() function.
	/// </summary>
	triangle();

	/// <summary>
	/// Creates a Rectangle struct and its appropriate VBOs and IBO.
	/// A blend colour and a texture may be given.
	/// </summary>
	/// <param name="renderer">The renderer that the triangle will be 'bound' to.</param>
	/// <param name="vertices">The starting vertex coordinates to use.</param>
	/// <param name="texture_path">The texture to use for the rectangle.</param>
	/// <param name="blend_colour">The colour to render the rectangle. Default is white.</param>
	void create(gearworks::renderer *renderer, glm::vec2 vertices[3], std::string texture_path, glm::vec4 blend_colour = glm::vec4(1.0, 1.0, 1.0, 1.0));

	/// <summary>
	/// Renders the triangle via glDrawElements.
	/// </summary>
	void render();

	/// <summary>
	/// Translates, or moves, the triangle by a given distance.
	/// </summary>
	/// <param name="transformation">The distance to move by in x, y, and z.</param>
	inline void translate(glm::vec3 transformation) { active_translation += transformation; }		// cache a translation to be applied in render()
	/// <summary>
	/// Rotates the triangle by a given amount.
	/// </summary>
	/// <param name="scaling">The amount to rotate by in degrees.</param>
	/// <param name="axes">The axes to rotate around.</param>
	inline void rotate(glm::vec3 rotation) { active_rotation += +glm::radians(rotation); }			// cache a rotation amount to be applied in render()
	/// <summary>
	/// Scales the triangle by a given amount.
	/// </summary>
	/// <param name="scaling">The amount to scale by.</param>
	inline void scale(glm::vec3 scaling) { active_scaling += scaling; }								// cache an amount to be scaled by in render()
};

#pragma endregion

#pragma region Nonstatic
class gearworks::engine {
private:
	// Handle to the renderer
	gearworks::renderer *renderer_handle;
public:
	/// <summary>
	/// Constructor for the engine class.
	/// To actually create the object, use the create() function.
	/// </summary>
	engine();

	/// <summary>
	/// Creates an engine object with a given renderer.
	/// Override this with your own code but be sure to set the renderer_handle variable to the given parameter, _renderer.
	/// If you don't do that step, other code likely will not work.
	/// </summary>
	/// <param name="_renderer">The renderer to `bind` this engine object to.</param>
	void create(gearworks::renderer *_renderer);

	/// <summary>
	/// All initializing logic here.
	/// </summary>
	void initialize();
	/// <summary>
	/// Updating logic, e.g. variable updates and function calls, goes here.
	/// </summary>
	void update();
	/// <summary>
	/// Rendering logic goes here.
	/// </summary>
	void render();
	/// <summary>
	/// Delete any heap allocated members or anything else here.
	/// </summary>
	void clean();
};

class gearworks::gwehaviour {
public:
	/// <summary>
	/// The main renderer used for the program.
	/// </summary>
	gearworks::renderer renderer;
	/// <summary>
	/// The main input manager used for the program.
	/// </summary>
	gearworks::input_manager input;
	/// <summary>
	/// The main engine instance used for the program.
	/// </summary>
	gearworks::engine main_engine;

	/// <summary>
	/// Path to the vertex shader to use in the program.
	/// Make sure to set it BEFORE calling initialize()!
	/// </summary>
	std::string vertex_shader_path;
	/// <summary>
	/// Path to the fragment shader to use in the program.
	/// Make sure to set it BEFORE calling initialize()!
	/// </summary>
	std::string fragment_shader_path;

	/// <summary>
	/// Function to initialize the program.
	/// Run it in the main function before update().
	/// </summary>
	void initialize();

	/// <summary>
	/// Function to update the program.
	/// Run it in the main function. To add your own logic, edit the engine class's update and render functions.
	/// </summary>
	void update();

	/// <summary>
	/// Function to destroy the program (deleting heap-allocated members or other memory-related logic).
	/// Run it in the main function before the return 0 statement.
	/// </summary>
	void destroy();
};
#pragma endregion

#endif