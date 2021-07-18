#include <opengl_pack.h>

#include "../../utility/utils.h"

#ifndef SHADER_MGMT_H
#define SHADER_MGMT_H

// Class for static functions
class shader_mgmt {
public:
	/// <summary>
	/// <para>Takes a file path of a shader and returns the source code of the shader from that file as a string.</para>
	/// </summary>
	/// <param name="path">The path to the source code of the shader.</param>
	static std::string parse_shader(const std::string &path);

	/// <summary>
	/// <para>Compiles a shader with standard OpenGL error handling.</para>
	/// </summary>
	/// <param name="type">The type of shader, given as an OpenGL macro.</param>
	/// <param name="source">The source code of the shader as a string - NOT the file path of the shader!</param>
	static unsigned int compile_shader(unsigned int type, const std::string &source);

	/// <summary>
	/// <para>Changes a uniform integer in a given program.</para>
	/// </summary>
	static inline void modify_uniform_1i(const unsigned int *program, const char *uniform_name, int val) { GL_CALL(glUniform1i(glGetUniformLocation(*program, uniform_name), val)); }
	/// <summary>
	/// <para>Changes a uniform integer in a given program.</para>
	/// </summary>
	static inline void modify_uniform_1f(const unsigned int *program, const char *uniform_name, float val) { GL_CALL(glUniform1f(glGetUniformLocation(*program, uniform_name), val)); }
	/// <summary>
	/// <para>Changes a uniform vec2 in a given program.</para>
	/// </summary>
	static inline void modify_uniform_2fv(const unsigned int *program, const char *uniform_name, glm::vec2 val) { GL_CALL(glUniform2f(glGetUniformLocation(*program, uniform_name), val.r, val.g)); }
	/// <summary>
	/// <para>Changes a uniform vec3 in a given program.</para>
	/// </summary>
	static inline void modify_uniform_3fv(const unsigned int *program, const char *uniform_name, glm::vec3 val) { GL_CALL(glUniform3f(glGetUniformLocation(*program, uniform_name), val.r, val.g, val.b)); }
	/// <summary>
	/// <para>Changes a uniform vec3 in a given program.</para>
	/// </summary>
	static inline void modify_uniform_4fv(const unsigned int *program, const char *uniform_name, glm::vec4 val) { GL_CALL(glUniform4f(glGetUniformLocation(*program, uniform_name), val.r, val.g, val.b, val.a)); }
	/// <summary>
	/// <para>Changes a uniform mat4 in a given program.</para>
	/// </summary>
	static inline void modify_uniform_4m(const unsigned int *program, const char *uniform_name, glm::mat4 val) { GL_CALL(glUniformMatrix4fv(glGetUniformLocation(*program, uniform_name), 1, GL_FALSE, &val[0][0])); }
};

// Struct to hold a shader
struct gw_shader {
private:
	unsigned int shader_program_id = 0;
public:
	/// <summary>
	/// <para>Constructor that creates, parses, compiles, and links a given shader.</para>
	/// <para>A new shader program is also created if needed.</para>
	/// </summary>
	/// <param name="path">The path to the source file for the shader</param>
	/// <param name="type">The type of shader, given as an OpenGL macro</param>
	/// <param name="program">A handle to the program the shader should be linked to</param>
	gw_shader(const std::string &path, unsigned int type, unsigned int program);
	// Deconstructor
	~gw_shader();

	/// <returns>the handle to the shader program that this shader is bound to</returns>
	unsigned int *get_shaderprogramid() { return &shader_program_id; }
};

#endif