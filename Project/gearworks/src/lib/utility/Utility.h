#pragma once

#include <depGL/Glad/glad.h>

#include <iostream>

#pragma region Macros
/// <summary>
/// <para>Checks to see if a given function, variable, or other object exists.</para>
/// <para>If it does not, debug-break the program.</para>
/// </summary>
#define ASSERT(x)\
if (!x) {\
__debugbreak;\
return -1;\
}

/// <summary>
/// <para>Same functionality as macro ASSERT, however CONASSERT prints its output to the console rather than debug-breaking it.</para>
/// </summary>
#define CONASSERT(x)\
if (!x) {\
std::cout << "Error: " << #x << " does not exist!" << std::endl;\
return -1;\
} else {\
std::cout << "Successful!" << std::endl;\
}

/// <summary>
/// <para>Checks an OpenGL function for errors - if there is one, output the line and file-path at which the error occurs to the console.</para>
/// </summary>
#define GL_CALL(x)\
glClearError();\
x;\
__pragma(warning(push));\
__pragma(warning(disable:4566));\
glLogCall(#x, __FILE__, __LINE__);\
__pragma(warning(pop))

// Stops the program if there is an error
static void glClearError() {
	while (glGetError() != GL_NO_ERROR);
}
// Logs any errors in the console; ASSERT this function so that, if it logs any errors, the program is broken
static void glLogCall(const char *fun, const char *path, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL] Error " << error << " found in file " << path << " at line " << line << "!" << std::endl;
	}
}
#pragma endregion

class util {
public:
	/// <summary>
	/// <para>GLFW error callback that outputs any errors to console.</para>
	/// </summary>
	/// <param name="error">The error number given by GLFW</param>
	/// <param name="description">The error description allocated to error</param>
	static void glfwErrorCallback(int error, const char *description);

	/// <summary>
	/// <para>Gets the current bound VAO</para>
	/// </summary>
	static int GetCurrentBoundVAO();

	struct coord {
		/// <summary>
		/// <para>Initializes the global coordinate system.</para>
		/// <para></para>
		/// </summary>
		/// <param name="program"></param>
		static void InitWorldCoordSystem(unsigned int *program, float maxVal);
	};

	/// <summary>
	/// <para>Struct to convert from RGBA-255 to RGBA-float (0-1)</para>
	/// </summary>
	struct ColourRGBA255 {
		float r, g, b, a;

		/// <summary>
		/// <para>Constructor for ColourRGBA255 that converts from RGBA-255 to RGBA-float (0-1) by dividing the given values by 255.</para>
		/// </summary>
		/// <param name="_r">Red value</param>
		/// <param name="_g">Green value</param>
		/// <param name="_b">Blue value</param>
		/// <param name="_a">Alpha value</param>
		ColourRGBA255(float _r, float _g, float _b, float _a);
	};
};