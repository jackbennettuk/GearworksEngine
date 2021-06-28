#pragma once

#include <depGL/Glad/glad.h>

#include <iostream>

/// <summary>
/// Checks to see if a given function, variable, or other object exists.
/// If it does not, debug-break the program.
/// </summary>
#define ASSERT(x)\
if (!x) {\
__debugbreak;\
return -1;\
}

/// <summary>
/// Same functionality as macro ASSERT, however CONASSERT prints its output to the console rather than debug-breaking it.
/// </summary>
#define CONASSERT(x)\
if (!x) {\
std::cout << "Error: " << #x << " does not exist!" << std::endl;\
return -1;\
} else {\
std::cout << "Successful!" << std::endl;\
}

class util {
public:
	/// <summary>
	/// GLFW error callback that outputs any errors to console.
	/// </summary>
	/// <param name="error">The error number given by GLFW</param>
	/// <param name="description">The error description allocated to error</param>
	static void glfwErrorCallback(int error, const char *description);
};