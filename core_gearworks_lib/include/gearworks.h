// ---------------------------------------------------------------------
// Gearworks Engine: gearworks.h - main library header file
// ---------------------------------------------------------------------
// Include this in your project to make use of the Gearworks game engine
// ---------------------------------------------------------------------

#ifndef GWREND_H
#define GWREND_H

// -------------------------------------------
// Include third-party and system dependencies
// -------------------------------------------

// System
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <Windows.h>		// Library is currently only compatible with Windows.

// GLM
#include <opengl/glm/vec4.hpp>
#include <opengl/glm/mat4x4.hpp>
#include <opengl/glm/gtc/matrix_transform.hpp>

// Glad
#include <opengl/Glad/glad.h>
#include <opengl/GLFW3/glfw3.h>

// stb_image
#include <stb/stb_image.h>

#pragma region Macros

/// <summary>
/// The maximum amount of keys that GLFW can handle at once.
/// The value '377' is based on the extended ASCII table at https://www.ascii-code.com/.
/// </summary>
#define GLFW_KEY_AMOUNT 377

/// <summary>
/// Checks an OpenGL function for errors - if there is one, output the line and file-path at which the error occurs to the console.
/// </summary>
#define GL_CALL(x)x;\
__pragma(warning(push));\
__pragma(warning(disable:4566));\
while (GLenum error = glGetError()) {\
std::cout << "  OpenGL Error " << error << " found referencing function " << #x << " in file " << __FILE__ << " at line " << __LINE__ << "!" << std::endl;\
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
std::cout << "  Loading GLFW... ";\
if (!glfwInit()) {\
	std::cout << "Error loading GLFW: the function \"glfwInit()\" does not exist or work!\n";\
} else {\
	std::cout << "OK!\n";\
}

/// <summary>
/// Initializes the Glad OpenGl loader.
/// </summary>
#define GW_INIT_GLAD()\
std::cout << "  Loading Glad... ";\
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {\
	std::cout << "Error loading Glad: the function gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) does not exist or work!\n\n";\
} else {\
	std::cout << "OK!\n";\
}

#pragma endregion
#pragma region Aliases

typedef std::string string;

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4 mat4;

#pragma endregion

namespace gearworks {
#pragma region Colours
	const static vec3 col_black = vec3(0, 0, 0);						// Gearworks default: black colour
	const static vec3 col_verydarkgray = vec3(26, 26, 26);			// Gearworks default: very dark gray colour
	const static vec3 col_darkgray = vec3(64, 64, 64);				// Gearworks default: dark gray colour
	const static vec3 col_midgray = vec3(128, 128, 128);				// Gearworks default: 50/50 gray colour
	const static vec3 col_lightgray = vec3(191, 191, 191);			// Gearworks default: light gray colour
	const static vec3 col_verylightgray = vec3(230, 230, 230);		// Gearworks default: very light gray colour
	const static vec3 col_white = vec3(255, 255, 255);				// Gearworks default: white colour

	const static vec3 col_brightred = vec3(255, 0, 0);				// Gearworks default: bright red colour
	const static vec3 col_brightgreen = vec3(0, 255, 0);				// Gearworks default: bright green colour
	const static vec3 col_brightblue = vec3(0, 0, 255);				// Gearworks default: bright blue colour
	const static vec3 col_brightyellow = vec3(255, 255, 0);			// Gearworks default: bright yellow colour
	const static vec3 col_brightmagenta = vec3(255, 0, 255);			// Gearworks default: bright magenta colour
	const static vec3 col_brightcyan = vec3(0, 255, 255);				// Gearworks default: bright cyan colour

	const static vec3 col_orange = vec3(191, 79, 37);					// Gearworks default: orange colour
	const static vec3 col_orangered = vec3(230, 0.28f, 38);			// Gearworks default: orange-red colour
	const static vec3 col_brown = vec3(79, 64, 39);					// Gearworks default: brown colour
#pragma endregion
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
	inline static void config_blending() {
		// Enable blending
		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	/// <summary>
	/// Clears the screen of the window assigned to the current OpenGL context.
	/// </summary>
	/// <param name="colour">The colour of the screen to clear in RGB255 format. If not given, the screen will be cleared to black.</param>
	inline static void clear_screen(vec3 colour = vec3(0)) {
		// Change the background colour to the colour variable
		GL_CALL(glClearColor(colour.r / 255, colour.g / 255, colour.b / 255, 1.0f));
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}
	/// <summary>
	/// Clears the screen of the window assigned to the current OpenGL context.
	/// </summary>
	/// <param name="r">The value for red (0-255). Defaults to 0.</param>
	/// <param name="g">The value for green (0-255). Defaults to 0.</param>
	/// <param name="b">The value for blue (0-255). Defaults to 0.</param>
	inline static void clear_screen(float r = 0, float g = 0, float b = 0) {
		// Change the background colour to the colour variable
		GL_CALL(glClearColor(r / 255, g / 255, b / 255, 1.0f));
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	/// <summary>
	/// Binds a given shader program.
	/// </summary>
	/// <param name="shader_program_id">The shader program to bind.</param>
	inline static void bind_program(unsigned int shader_program_id) {
		// Bind a shader program via its id
		GL_CALL(glUseProgram(shader_program_id));
	}

	/// <summary>
	/// Unbinds all shader programs.
	/// </summary>
	inline static void unbind_program() {
		// Unbind any shader programs
		GL_CALL(glUseProgram(0));
	}

	/// <summary>
	/// Turns wireframe rendering on or off.
	/// </summary>
	/// <param name="wireframe">Either on or off, basically.</param>
	inline static void toggle_wireframe(bool wireframe) {
		// Set the OpenGl polygon mode accordingly.
		if (wireframe) {
			GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		} else {
			GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
	}

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
	string parse_shader(const string &path);

	/// <summary>
	/// Compiles a shader with standard OpenGL error handling.
	/// </summary>
	/// <param name="type">The type of shader, given as an OpenGL macro.</param>
	/// <param name="source">The source code of the shader as a string - NOT the file path of the shader!</param>
	unsigned int compile_shader(unsigned int type, const string &source);

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
	void modify_uniform_2fv(const unsigned int *program, const char *uniform_name, vec2 val);
	/// <summary>
	/// Changes a uniform vec3 in a given program.
	/// </summary>
	void modify_uniform_3fv(const unsigned int *program, const char *uniform_name, vec3 val);
	/// <summary>
	/// Changes a uniform vec4 in a given program.
	/// </summary>
	void modify_uniform_4fv(const unsigned int *program, const char *uniform_name, vec4 val);
	/// <summary>
	/// Changes a uniform mat4 in a given program.
	/// </summary>
	void modify_uniform_4m(const unsigned int *program, const char *uniform_name, mat4 val);

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

#pragma region User-defined

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

// ------------------------------------------------------------------------
// If not otherwise specified, include the definition files for the library
// ------------------------------------------------------------------------

// Rendering
#ifndef GW_NOINCLUDE_RENDER_DEFS

#include "../source/lib/rendering/shader/r_shader.h"
#include "../source/lib/rendering/bufferobjs/r_bufferobjs.h"
#include "../source/lib/rendering/texture/r_texture.h"
#include "../source/lib/rendering/window/r_window.h"
#include "../source/lib/rendering/renderer/r_renderer.h"

#endif // Rendering files

// Input
#ifndef GW_NOINCLUDE_INPUT_DEFS

#include "../source/lib/input/i_input.h"

#endif // Input files

// Presets
#ifndef GW_NOINCLUDE_PRESET_DEFS

#include "../source/lib/presets/2dim/rectangle/p2d_rectangle.h"
#include "../source/lib/presets/2dim/triangle/p2d_triangle.h"

#endif // Preset shape files

// User-defined classes
#ifndef GW_NOINCLUDE_NONSTATIC_DEFS

#include "../source/lib/userdef/engine/u_engine.h"
#include "../source/lib/userdef/gwehaviour/u_gwehaviour.h"

#endif // Userdef files

#endif // Header guard