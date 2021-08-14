#include "r_shader.h"

gearworks::shader::shader(const std::string &path, unsigned int type, unsigned int program)
	: shader_program_id(program) {
	// Compile the given source and attach the new shader to the program
	unsigned int shaderID = gearworks::compile_shader(type, gearworks::parse_shader(path));
	GL_CALL(glAttachShader(shader_program_id, shaderID));

	// Link the program
	GL_CALL(glLinkProgram(shader_program_id));

	// Validate the program
	GL_CALL(glValidateProgram(shader_program_id));

	// Delete shaderID
	GL_CALL(glDeleteShader(shaderID));
}

std::string gearworks::parse_shader(const std::string &path) {
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

unsigned int gearworks::compile_shader(unsigned int type, const std::string &source) {
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

void gearworks::modify_uniform_1i(const unsigned int *program, const char *uniform_name, int val) { GL_CALL(glUniform1i(glGetUniformLocation(*program, uniform_name), val)); }
void gearworks::modify_uniform_1f(const unsigned int *program, const char *uniform_name, float val) { GL_CALL(glUniform1f(glGetUniformLocation(*program, uniform_name), val)); }
void gearworks::modify_uniform_2fv(const unsigned int *program, const char *uniform_name, glm::vec2 val) { GL_CALL(glUniform2f(glGetUniformLocation(*program, uniform_name), val.r, val.g)); }
void gearworks::modify_uniform_3fv(const unsigned int *program, const char *uniform_name, glm::vec3 val) { GL_CALL(glUniform3f(glGetUniformLocation(*program, uniform_name), val.r, val.g, val.b)); }
void gearworks::modify_uniform_4fv(const unsigned int *program, const char *uniform_name, glm::vec4 val) { GL_CALL(glUniform4f(glGetUniformLocation(*program, uniform_name), val.r, val.g, val.b, val.a)); }
void gearworks::modify_uniform_4m(const unsigned int *program, const char *uniform_name, glm::mat4 val) { GL_CALL(glUniformMatrix4fv(glGetUniformLocation(*program, uniform_name), 1, GL_FALSE, &val[0][0])); }