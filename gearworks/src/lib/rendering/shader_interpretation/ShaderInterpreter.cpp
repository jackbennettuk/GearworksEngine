#include "ShaderInterpreter.h"

#include "gwutility.h"

#include <sstream>
#include <fstream>

Shader::Shader(const std::string &_path, unsigned int _type, unsigned int _program) 
	: programID(_program) {
	// Compile the given source and attach the new shader to the program
	unsigned int shaderID = CompileShader(_type, ParseShader(_path));
	GL_CALL(glAttachShader(programID, shaderID));

	// Link the program
	GL_CALL(glLinkProgram(programID));

	// Validate the program
	GL_CALL(glValidateProgram(programID));

	// Delete shaderID
	GL_CALL(glDeleteShader(shaderID));
}

std::string Shader::ParseShader(const std::string &path) {
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

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
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