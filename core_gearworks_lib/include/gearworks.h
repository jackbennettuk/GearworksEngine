// ---------------------------------------------------------------------
// Gearworks Engine: gearworks.h - main library header file
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

namespace gearworks {
#pragma region Colours
	const static glm::vec3 col_black = glm::vec3(0.0f, 0.0f, 0.0f);						// Gearworks default: black colour
	const static glm::vec3 col_verydarkgray = glm::vec3(0.10f, 0.10f, 0.10f);			// Gearworks default: very dark gray colour
	const static glm::vec3 col_darkgray = glm::vec3(0.25f, 0.25f, 0.25f);				// Gearworks default: dark gray colour
	const static glm::vec3 col_midgray = glm::vec3(0.5f, 0.5f, 0.5f);					// Gearworks default: 50/50 gray colour
	const static glm::vec3 col_lightgray = glm::vec3(0.75f, 0.75f, 0.75f);				// Gearworks default: light gray colour
	const static glm::vec3 col_verylightgray = glm::vec3(0.90f, 0.90f, 0.90f);			// Gearworks default: very light gray colour
	const static glm::vec3 col_white = glm::vec3(1.00f, 1.00f, 1.00f);					// Gearworks default: white colour

	const static glm::vec3 col_brightred = glm::vec3(1.00f, 0.00f, 0.00f);				// Gearworks default: bright red colour
	const static glm::vec3 col_brightgreen = glm::vec3(0.00f, 1.00f, 0.00f);			// Gearworks default: bright green colour
	const static glm::vec3 col_brightblue = glm::vec3(0.00f, 0.00f, 1.00f);				// Gearworks default: bright blue colour
	const static glm::vec3 col_brightyellow = glm::vec3(1.00f, 1.00f, 0.00f);			// Gearworks default: bright yellow colour
	const static glm::vec3 col_brightmagenta = glm::vec3(1.00f, 0.00f, 1.00f);			// Gearworks default: bright magenta colour
	const static glm::vec3 col_brightcyan = glm::vec3(0.00f, 1.00f, 1.00f);				// Gearworks default: bright cyan colour

	const static glm::vec3 col_orange = glm::vec3(0.75f, 0.31f, 0.13f);					// Gearworks default: orange colour
	const static glm::vec3 col_orangered = glm::vec3(0.91f, 0.28f, 0.15f);				// Gearworks default: orange-red colour (think Reddit branding)
	const static glm::vec3 col_brown = glm::vec3(0.33f, 0.21f, 0.18f);					// Gearworks default: brown colour
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
		// Enable blending for transparency
		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	/// <summary>
	/// Clears the screen of the window assigned to the current OpenGL context.
	/// </summary>
	/// <param name="colour">The colour of the screen to clear. If not given, the screen will be cleared to black.</param>
	inline static void clear_screen(glm::vec3 colour = glm::vec3(0)) {
		// Change the background colour to the colour variable
		GL_CALL(glClearColor(colour.r, colour.g, colour.b, 1.0f));
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

#endif

// User-defined classes
#ifndef GW_NOINCLUDE_NONSTATIC_DEFS

#include "../source/lib/userdef/engine/u_engine.h"
#include "../source/lib/userdef/gwehaviour/u_gwehaviour.h"

#endif // Userdef files

#endif // Header guard