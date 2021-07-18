#ifndef UTILS_H
#define UTILS_H

#include <string>

/// <summary>
/// <para>Checks an OpenGL function for errors - if there is one, output the line and file-path at which the error occurs to the console.</para>
/// </summary>
#define GL_CALL(x)\
x;\
__pragma(warning(push));\
__pragma(warning(disable:4566));\
while (GLenum error = glGetError()) {\
std::cout << "[OpenGL] Error " << error << " found referencing function " << #x << " in file " << __FILE__ << " at line " << __LINE__ << "!" << std::endl;\
}\
__pragma(warning(pop))

/// <summary>
/// <para>Deletes a heap-allocated variable. This should not be called often, if at all.</para>
/// </summary>
#define DELETE_HALLOC(x)\
delete x;\
x = NULL

#endif