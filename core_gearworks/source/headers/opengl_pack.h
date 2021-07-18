#ifndef OPENGL_PACK_H
#define OPENGL_PACK_H

// iostream is included for functions in this file.
#include <iostream>

// Glad and GLFW loaders for OpenGL and window handling respectively.
#include <opengl/Glad/glad.h>
#include <opengl/GLFW3/glfw3.h>

// Defining this macro means that glm and a lot of its functions will not be loaded.
// Make sure to define it if you do not need glm in a source file in order to make compilation time quicker.
#ifndef GW_GLM_INCLUDED
#include <opengl/glm/glm.hpp>
#include <opengl/glm/gtc/matrix_transform.hpp>
#endif

/// <summary>
/// <para>Loads GLFW.</para>
/// </summary>
#define GW_INIT_GLFW()\
std::cout << "[GW] Loading GLFW... ";\
if (!glfwInit()) {\
	std::cout << "Error loading GLFW: the function \"glfwInit()\" does not exist or work!\n";\
} else {\
	std::cout << "Successful!\n";\
}

/// <summary>
/// <para>Initializes the Glad OpenGl loader.</para>
/// </summary>
#define GW_INIT_GLAD()\
std::cout << "[GW] Loading Glad... ";\
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {\
	std::cout << "Error loading Glad: the function gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) does not exist or work!\n\n";\
} else {\
	std::cout << "Successful!\n\n";\
}

#endif