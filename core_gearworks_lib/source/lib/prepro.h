#ifndef PREPRO_H
#define PREPRO_H

// TODO: this is Windows-only due to the use of backslashes
/// <summary>
/// The name of the file this macro is called from.
/// </summary>
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

/// <summary>
/// Checks an OpenGL function for errors - if there is one, output the line and file-path at which the error occurs to the console.
/// </summary>
#define GL_CALL(x)x;\
__pragma(warning(push));\
__pragma(warning(disable:4566));\
while (GLenum error = glGetError()) {\
std::cout << "  OpenGL Error " << error << " encountered when referencing function '" << #x << "' in file '" << __FILENAME__ << "' at line " << __LINE__ << "." << std::endl;\
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

/// <summary>
/// Prints to the debug console window with a 2-space indent.
/// </summary>
#define printgw(x)\
std::cout << "  " << x;

#endif // Header guard