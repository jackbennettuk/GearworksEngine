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
}

/// <summary>
/// <para>Same functionality as macro ASSERT, however CONASSERT prints its output to the console rather than debug-breaking it.</para>
/// </summary>
#define CONASSERT(x)\
if (!x) {\
std::cout << "Error: " << #x << " does not exist!" << std::endl;\
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

#define DELETE_PTR(x)\
delete x;\
x = NULL

#pragma endregion

class util {
public:
	/// <summary>
	/// Returns the size, as an unsigned int, of each OpenGL type
	/// </summary>
	/// <param name="type"></param>
	static unsigned int GetSizeOfType(unsigned int type);
};

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