#include "shader_mgmt.h"

#include <sstream>
#include <fstream>

#include <gearworks.h>

#pragma region shader_mgmt (shader_management) implementation
std::string shader_mgmt::parse_shader(const std::string &path) {
	// Get the file associated with the given path
	std::ifstream file(path);

	std::stringstream result;
	std::string line;

	while (getline(file, line)) {
		// Add each line of the source code to the result variable
		result << line << "\n";
	}

	// Convert the result from stringstream to string and then return that
	return result.str();
}
unsigned int shader_mgmt::compile_shader(unsigned int type, const std::string &source) {
	// Set the shader renderer id to a new shader of the given type
	unsigned int id = glCreateShader(type);

	// Convert the source to a const char *
	const char *srcChar = source.c_str();
	// Set the shader's source to the given source
	GL_CALL(glShaderSource(id, 1, &srcChar, nullptr));

	// Compile the shader
	GL_CALL(glCompileShader(id));

	// Get the compile status for compilation
	int status;
	GL_CALL(GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &status)));

	// If there is an error...
	if (status == GL_FALSE) {
		// Get the length of the error message
		int length;
		GL_CALL(GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length)));

		// Allocate the error message pointer variable
		char *errorMessage = (char *)_malloca(length * sizeof(char));

		// Set the error message
		GL_CALL(GL_CALL(glGetShaderInfoLog(id, length, &length, errorMessage)));

		// Log the error message to console
		std::cout << "[OpenGL] Shader compilation error ecnountered: failed to compile shader of type " << type << "!" << std::endl;
		std::cout << errorMessage << std::endl;

		// Delete the shader
		GL_CALL(glDeleteShader(id));
		return 0;
	}

	// Return the now-working shader
	return id;
}
#pragma endregion

#pragma region gw_shader implementation
gw_shader::gw_shader(const std::string &path, unsigned int type, unsigned int program)
	: shader_program_id(program)
{
	// Compile the given source and attach the new shader to the program
	unsigned int shaderID = shader_mgmt::compile_shader(type, shader_mgmt::parse_shader(path));
	GL_CALL(glAttachShader(shader_program_id, shaderID));

	// Link the program
	GL_CALL(glLinkProgram(shader_program_id));

	// Validate the program
	GL_CALL(glValidateProgram(shader_program_id));

	// Delete shaderID
	GL_CALL(glDeleteShader(shaderID));
}

gw_shader::~gw_shader() {}
#pragma endregion