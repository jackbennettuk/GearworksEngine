#ifndef R_SHADER_H
#define R_SHADER_H

#include <gearworks.h>

struct gearworks::shader {
private:
	unsigned int shader_program_id = 0;
public:
	/// <summary>
	/// Constructor that creates, parses, compiles, and links a given shader.
	/// A new shader program is also created if needed.
	/// </summary>
	/// <param name="path">The path to the source file for the shader</param>
	/// <param name="type">The type of shader, given as an OpenGL macro</param>
	/// <param name="program">A handle to the program the shader should be linked to</param>
	shader(const std::string &path, unsigned int type, unsigned int program);

	/// <returns>the handle to the shader program that this shader is bound to</returns>
	inline unsigned int *get_shaderprogramid() { return &shader_program_id; }
};

#endif // header guard