#pragma once

#include "gwutility.h"

#include <depGL/Glad/glad.h>
#include <depGL/glm/glm.hpp>

#include <iostream>

class Shader {
private:
	unsigned int programID = 0;

	/// <summary>
	/// <para>Takes a file path of a shader and returns the source code of the shader from that file as a string.</para>
	/// </summary>
	/// <param name="path">The path to the source code of the shader</param>
	static std::string ParseShader(const std::string &path);

	/// <summary>
	/// <para>Compiles a shader with OpenGL error handling.</para>
	/// </summary>
	/// <param name="type">The type of shader, given as an OpenGL macro</param>
	/// <param name="source">The source code of the shader as a string - NOT the file path of the shader!</param>
	static unsigned int CompileShader(unsigned int type, const std::string &source);
public:
	/// <summary>
	/// <para>Constructor that creates, parses, compiles, and links a given shader.</para>
	/// <para>A new shader program is also created if needed.</para>
	/// </summary>
	/// <param name="_path">The path to the source file for the shader</param>
	/// <param name="_type">The type of shader, given as an OpenGL macro</param>
	/// <param name="_program">A handle to the program the shader should be linked to</param>
	Shader(const std::string &_path, unsigned int _type, unsigned int _program);

	/// <summary>
	/// <para>Changes a uniform vec3 in a given program.</para>
	/// </summary>
	static inline void ModifyUniformv3(const unsigned int *program, const char *uniformName, glm::vec3 val) {
		GL_CALL(glUniform3f(glGetUniformLocation(*program, uniformName), val.r, val.g, val.b));
	}
	/// <summary>
	/// <para>Changes a uniform mat4 in a given program.</para>
	/// </summary>
	static inline void ModifyUniformmat4(const unsigned int *program, const char *uniformName, glm::mat4 val) {
		GL_CALL(glUniformMatrix4fv(glGetUniformLocation(*program, uniformName), 1, GL_FALSE, &val[0][0]));
	}
};