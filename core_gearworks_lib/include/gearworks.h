// ---
// Gearworks Engine: gearworks.h - main library header file
// Include this in your project to make use of the Gearworks game engine
// ---

#ifndef GWREND_H
#define GWREND_H

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

#pragma region Macros

/// <summary>
/// The maximum amount of keys that GLFW can handle at once.
/// The value '377' is based on the extended ASCII table at https://www.ascii-code.com/.
/// </summary>
#define GW_KEY_AMOUNT 377

/// <summary>
/// A string to use in place of null in gearworks operations.
/// </summary>
#define GW_NULLSTR "ngiven"

/// <summary>
/// Checks an OpenGL function for errors - if there is one, output the line and file-path at which the error occurs to the console.
/// </summary>
#define GL_CALL(x)x;\
__pragma(warning(push));\
__pragma(warning(disable:4566));\
while (GLenum error = glGetError()) {\
std::cout << "[OpenGL] Error " << error << " found referencing function " << #x << " in file " << __FILE__ << " at line " << __LINE__ << "!" << std::endl;\
}\
__pragma(warning(pop))

/// <summary>
/// Deletes a heap-allocated variable. This should not be called often, if at all.
/// </summary>
#define DELETE_HALLOC(x)delete x;\
x = NULL

/// <summary>
/// Loads GLFW.
/// </summary>
#define GW_INIT_GLFW()\
std::cout << "[GW] Loading GLFW... ";\
if (!glfwInit()) {\
	std::cout << "Error loading GLFW: the function \"glfwInit()\" does not exist or work!\n";\
} else {\
	std::cout << "Successful!\n";\
}

/// <summary>
/// Initializes the Glad OpenGl loader.
/// </summary>
#define GW_INIT_GLAD()\
std::cout << "[GW] Loading Glad... ";\
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {\
	std::cout << "Error loading Glad: the function gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) does not exist or work!\n\n";\
} else {\
	std::cout << "Successful!\n\n";\
}

#pragma endregion

namespace gearworks {
#pragma region Rendering

#pragma region General

	/// <summary>
	/// Gearworks window that handles window operations via GLFW.
	/// </summary>
	struct window;

	/// <summary>
	/// A gearworks renderer which handles all rendering-related tasks.
	/// </summary>
	class renderer;

	/// <summary>
	/// Sets up blending to allow for transparent pixels or textures.
	/// </summary>
	static void config_blending();
	/// <summary>
	/// Clears the screen of the window assigned to the current OpenGL context.
	/// </summary>
	/// <param name="colour">The colour of the screen to clear. If not given, the screen will be cleared to black.</param>
	static void clear_screen(glm::vec3 colour = glm::vec3(0));
	/// <summary>
	/// Binds a given shader program.
	/// </summary>
	/// <param name="shader_program_id">The shader program to bind.</param>
	static void bind_program(unsigned int shader_program_id);
	/// <summary>
	/// Unbinds all shader programs.
	/// </summary>
	static void unbind_program();
	/// <summary>
	/// Turns wireframe rendering on or off.
	/// </summary>
	/// <param name="wireframe">Either on or off, basically.</param>
	static void toggle_wireframe(bool wireframe);

#pragma endregion
#pragma region Shaders

	/// <summary>
	/// A gearworks shader for rendering.
	/// </summary>
	struct shader;

	/// <summary>
	/// Takes a file path of a shader and returns the source code of the shader from that file as a string.
	/// </summary>
	/// <param name="path">The path to the source code of the shader.</param>
	std::string parse_shader(const std::string &path);

	/// <summary>
	/// Compiles a shader with standard OpenGL error handling.
	/// </summary>
	/// <param name="type">The type of shader, given as an OpenGL macro.</param>
	/// <param name="source">The source code of the shader as a string - NOT the file path of the shader!</param>
	unsigned int compile_shader(unsigned int type, const std::string &source);

	/// <summary>
	/// Changes a uniform integer in a given program.
	/// </summary>
	void modify_uniform_1i(const unsigned int *program, const char *uniform_name, int val);
	/// <summary>
	/// Changes a uniform float in a given program.
	/// </summary>
	void modify_uniform_1f(const unsigned int *program, const char *uniform_name, float val);
	/// <summary>
	/// Changes a uniform vec2 in a given program.
	/// </summary>
	void modify_uniform_2fv(const unsigned int *program, const char *uniform_name, glm::vec2 val);
	/// <summary>
	/// Changes a uniform vec3 in a given program.
	/// </summary>
	void modify_uniform_3fv(const unsigned int *program, const char *uniform_name, glm::vec3 val);
	/// <summary>
	/// Changes a uniform vec4 in a given program.
	/// </summary>
	void modify_uniform_4fv(const unsigned int *program, const char *uniform_name, glm::vec4 val);
	/// <summary>
	/// Changes a uniform mat4 in a given program.
	/// </summary>
	void modify_uniform_4m(const unsigned int *program, const char *uniform_name, glm::mat4 val);

#pragma endregion
#pragma region Buffer objects

	/// <summary>
	/// A gearworks vertex array object for use by OpenGl.
	/// </summary>
	class vertex_array_object;
	/// <summary>
	/// A gearworks vertex buffer object for use by OpenGl.
	/// </summary>
	class vertex_buffer_object;
	/// <summary>
	/// A gearworks index buffer object for use by OpenGl.
	/// </summary>
	class index_buffer_object;

#pragma endregion
#pragma region Textures

	/// <summary>
	/// A 2D texture object. To load the texture with a given path, call load.
	/// </summary>
	class texture_2d;

#pragma endregion

#pragma endregion
#pragma region Input

	/// <summary>
	/// Class for an instance manager.
	/// </summary>
	class input_manager;

#pragma endregion
#pragma region Shapes

	/// <summary>
	/// A rectangle object. To create it using a solid colour, use create().
	/// </summary>
	class rectangle;
	/// <summary>
	/// A triangle object. To create it using a solid colour, use create().
	/// </summary>
	class triangle;

#pragma endregion

#pragma region Nonstatic

	/// <summary>
	/// Class for all user logic to be referenced in.
	/// Note the 'renderer_handle' variable can be used to reference the renderer that this engine object is associated with.
	/// </summary>
	class engine;

	/// <summary>
	/// Behaviour class that includes all necessary non-static members. Be sure to inherit from it in your files whenever needed.
	/// </summary>
	class gwehaviour;

#pragma endregion
}

// This file defines the classes in the gearworks namespace.
// (It doesn't define each member of the classes - it just declares them. Those are defined in their own files, like imp_input.cpp or imp_shapes.cpp)
#include "../source/lib/defs.h"

#endif