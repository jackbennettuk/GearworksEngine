#include "defs.h"

#pragma region Window

gearworks::window::window()
	: window_title(""), window_width(0), window_height(0), aspect_ratio(0), glfw_handle(0)
{}

void gearworks::window::create_window(std::string title, int width, int height) {
	// initialize properties with arguments
	window_title = title;
	window_width = width;
	window_height = height;

	// Set the aspect ratio
	aspect_ratio = (float)window_width / (float)window_height;

	// Create the window
	std::cout << "[GW] Creating window... ";
	glfw_handle = glfwCreateWindow(window_width, window_height, window_title.c_str(), NULL, NULL);

	// Assert the now-created window
	if (!glfw_handle) {
		std::cout << "Error creating the window: the member \"glfw_handle\" does not exist!\n";
	} else {
		std::cout << "Successful!\n";
	}

	// Set this window to be the current OpenGL context
	glfwMakeContextCurrent(glfw_handle);
	// Set the OpenGL swap interval to 1
	glfwSwapInterval(1);
}

void gearworks::window::reevaluate() {
	// Update the window size variables
	glfwGetFramebufferSize(glfw_handle, &window_width, &window_height);
	// Update the aspect ratio
	aspect_ratio = (float)window_width / (float)window_height;
}

void gearworks::window::update_window() {
	// Swap buffers
	glfwSwapBuffers(glfw_handle);
	// Poll window events
	glfwPollEvents();
}

#pragma endregion
#pragma region Renderer

gearworks::renderer::renderer() :
	cur_shader_program_id(0),
	cur_window(),
	project_matrix(NULL),
	view_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	model_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	current_zoom(1.0f)
{}

void gearworks::renderer::update_renderer() {
	// Update the window
	cur_window.reevaluate();

	// Update the viewport size so it is resized with the window
	glViewport(0, 0, cur_window.get_winwidth(), cur_window.get_winheight());

	// Update the projection matrix so it is also resized along with window/viewport resize
	// Also factor in zoom for zooming capabilities.
	project_matrix = glm::ortho(
		(float)-cur_window.get_winwidth() / current_zoom,
		(float)cur_window.get_winwidth() / current_zoom,
		(float)-cur_window.get_winheight() / current_zoom,
		(float)cur_window.get_winheight() / current_zoom
	);

	// Update the model-view-projection matrix
	glm::mat4 mvp_matrix = project_matrix * view_matrix * model_matrix;

	// Apply this matrix via the vertex shader
	gearworks::modify_uniform_4m(&cur_shader_program_id, "u_ModelViewProjMat", mvp_matrix);
}

void gearworks::renderer::create_window(std::string title, int sizeX, int sizeY) {
	// Assign the window pointer
	cur_window.create_window(title, sizeX, sizeY);
}

void gearworks::renderer::initialize_shaders(std::string vertex_shader_path, std::string fragment_shader_path) {
	// Create the main shader program
	cur_shader_program_id = GL_CALL(glCreateProgram());

	// Create the VERTEX shader
	if (vertex_shader_path == GW_NULLSTR)		// if the path was not given, throw a warning in console.
		std::cout << "[GW] Warning: the string \"vertex_shader_path\" (gearworks::renderer::initialize_shaders) is set to ngiven - some things might not work properly.";
	gearworks::shader vertex_shad(vertex_shader_path, GL_VERTEX_SHADER, cur_shader_program_id);

	// Create the FRAGMENT shader
	if (fragment_shader_path == GW_NULLSTR)		// if the path was not given, throw a warning in console.
		std::cout << "[GW] Warning: the string \"fragment_shader_path\" (gearworks::renderer::initialize_shaders) is set to ngiven - some things might not work properly.";
	gearworks::shader fragment_shad(fragment_shader_path, GL_FRAGMENT_SHADER, cur_shader_program_id);

	// Bind program
	gearworks::bind_program(cur_shader_program_id);
}

void gearworks::renderer::zoom_by_value(float amount) {
	// Increase current_zoom before clamping
	current_zoom += amount;
	// Clamp current_zoom
	current_zoom = std::max(min_zoom, std::min(current_zoom, max_zoom));
}

#pragma endregion
#pragma region Shaders

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

#pragma endregion
#pragma region Buffer objects

#pragma region VAO

unsigned int gearworks::vertex_array_object::get_rendererid() { return renderer_id; }

gearworks::vertex_array_object::vertex_array_object() 
	: renderer_id(NULL)
{}

void gearworks::vertex_array_object::initialize() {
	// Generate the vertex array
	GL_CALL(glGenVertexArrays(1, &renderer_id));
}

void gearworks::vertex_array_object::add_vb_attrib(vertex_buffer_object &vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
	// Bind this VAO
	bind();
	// Bind the given VBO first
	vbo.bind();

	GL_CALL(glEnableVertexAttribArray(index));
	GL_CALL(glVertexAttribPointer(index, size, type, normalized, stride, pointer));

	// Unbind the VAO
	unbind();
	// Unbind the VBO and delete it via its deconstructor
	vbo.unbind();
}

void gearworks::vertex_array_object::bind() {
	// Binds the vertex array to rendererID
	GL_CALL(glBindVertexArray(renderer_id));
}
void gearworks::vertex_array_object::unbind() {
	// Binds the vertex array to 0
	GL_CALL(glBindVertexArray(0));
}

#pragma endregion
#pragma region VBO

unsigned int gearworks::vertex_buffer_object::get_rendererid() { return renderer_id; }

gearworks::vertex_buffer_object::vertex_buffer_object()
	: renderer_id(NULL)
{}

void gearworks::vertex_buffer_object::initialize(unsigned int count, float data[]) {
	// Initialize rendererID as a newly-generated buffer object
	GL_CALL(glGenBuffers(1, &renderer_id));

	// Bind the buffer so that the following function works
	bind();
	// Set the data of the VBO based on count and data
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));
	// Initially unbind the buffer so that it is bound through the VAO at render-time
	unbind();
}

void gearworks::vertex_buffer_object::bind() {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
}
void gearworks::vertex_buffer_object::unbind() {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

#pragma endregion
#pragma region IBO

unsigned int gearworks::index_buffer_object::get_rendererid() { return renderer_id; }

gearworks::index_buffer_object::index_buffer_object()
	: renderer_id(NULL) 
{}

void gearworks::index_buffer_object::initialize(unsigned int count, unsigned int data[]) {
	// Initialize rendererID as a newly-generated index buffer object
	GL_CALL(glGenBuffers(1, &renderer_id));

	// Bind the IBO
	bind();
	// Set the data of the IBO based on count and data
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));
	// Then unbind the IBO so it can be tracked easier
	unbind();
}

void gearworks::index_buffer_object::bind() {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
}
void gearworks::index_buffer_object::unbind() {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

#pragma endregion

#pragma endregion
#pragma region Textures

gearworks::texture_2d::texture_2d() :
	renderer_id(NULL),
	width(NULL),
	height(NULL),
	bits_per_pixel(NULL)
{}

void gearworks::texture_2d::load(std::string _path) {
	// Update the local path variable.
	path = _path;

	// Flips the texture vertically
	// This is because the way OpenGL expects textures is vertically opposite the way Gearworks expects them
	stbi_set_flip_vertically_on_load(1);

	// Loads the texture with references to width, height, bpp
	// In this case, store the texture image to the new localBuffer variable
	unsigned char *local_buffer;
	local_buffer = stbi_load(path.c_str(), &width, &height, &bits_per_pixel, 4);

	// Check if there was an error when loading the texture
	if (stbi_failure_reason()) {
		std::cout << "[stbi] Error: " << stbi_failure_reason() << "\n";
	}

	// Generates and binds the texture buffer
	GL_CALL(glGenTextures(1, &renderer_id));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, renderer_id));

	// This parameter defines how the texture will be scaled down
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	// This parameter defines how the texture will be scaled up
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// Thess parameter defines how the texture will be wrapped
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// Assign the image at [path] to be set to the GL_TEXTURE_2D
	// Also move the texture data to the GPU for use by the fragment shader
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));

	// Generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture by default afterwards
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	// Free the image from the localBuffer variable
	if (local_buffer) {
		stbi_image_free(local_buffer);
	}
}

void gearworks::texture_2d::bind(unsigned int slot) {
	// Set the active texture slot to the parameter if it was given
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	// Bind the renderer id
	GL_CALL(glBindTexture(GL_TEXTURE_2D, renderer_id));
}

void gearworks::texture_2d::unbind() {
	// Unbind any textures
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

#pragma endregion