#ifndef UT_UTILITY_H
#define UT_UTILITY_H

#include <gearworks.h>

namespace gearworks {
	// -------
	// Colours
	// -------
#pragma region collapsibleregion
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

	// -------------------------------------
	// Static functions related to rendering
	// -------------------------------------
#pragma region collapsibleregion
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

	// -----------------------------------
	// Static functions related to shaders
	// -----------------------------------
#pragma region collapsibleregion
	/// <summary>
	/// Takes a file path of a shader and returns the source code of the shader from that file as a string.
	/// </summary>
	/// <param name="path">The path to the source code of the shader.</param>
	static string parse_shader(const string &path);

	/// <summary>
	/// Compiles a shader with standard OpenGL error handling.
	/// </summary>
	/// <param name="type">The type of shader, given as an OpenGL macro.</param>
	/// <param name="source">The source code of the shader as a string - NOT the file path of the shader!</param>
	static unsigned int compile_shader(unsigned int type, const string &source);

	/// <summary>
	/// Changes a uniform integer in a given program.
	/// </summary>
	static void modify_uniform_1i(const unsigned int *program, const char *uniform_name, int val) { GL_CALL(glUniform1i(glGetUniformLocation(*program, uniform_name), val)); }
	/// <summary>
	/// Changes a uniform float in a given program.
	/// </summary>
	static void modify_uniform_1f(const unsigned int *program, const char *uniform_name, float val) { GL_CALL(glUniform1f(glGetUniformLocation(*program, uniform_name), val)); }
	/// <summary>
	/// Changes a uniform vec2 in a given program.
	/// </summary>
	static void modify_uniform_2fv(const unsigned int *program, const char *uniform_name, vec2 val) { GL_CALL(glUniform2f(glGetUniformLocation(*program, uniform_name), val.r, val.g)); }
	/// <summary>
	/// Changes a uniform vec3 in a given program.
	/// </summary>
	static void modify_uniform_3fv(const unsigned int *program, const char *uniform_name, vec3 val) { GL_CALL(glUniform3f(glGetUniformLocation(*program, uniform_name), val.r, val.g, val.b)); }
	/// <summary>
	/// Changes a uniform vec4 in a given program.
	/// </summary>
	static void modify_uniform_4fv(const unsigned int *program, const char *uniform_name, vec4 val) { GL_CALL(glUniform4f(glGetUniformLocation(*program, uniform_name), val.r, val.g, val.b, val.a)); }
	/// <summary>
	/// Changes a uniform mat4 in a given program.
	/// </summary>
	static void modify_uniform_4m(const unsigned int *program, const char *uniform_name, mat4 val) { GL_CALL(glUniformMatrix4fv(glGetUniformLocation(*program, uniform_name), 1, GL_FALSE, &val[0][0])); }
#pragma endregion
}

#endif // Header guard