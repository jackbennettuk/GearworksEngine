#include "renderpl.h"

#include <gearworks.h>

#pragma region gw_window implementation
gw_window::gw_window(std::string title, int width, int height)
	: window_title(title), window_width(width), window_height(height)
{
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

void gw_window::reevaluate() {
	// Update the window size variables
	glfwGetFramebufferSize(glfw_handle, &window_width, &window_height);
	// Update the aspect ratio
	aspect_ratio = (float)window_width / (float)window_height;
}

void gw_window::update_window() {
	// Swap buffers
	glfwSwapBuffers(glfw_handle);
	// Poll window events
	glfwPollEvents();	
}
#pragma endregion
#pragma region gw_rendering_pl implementation
void gw_rendering_pl::gw_config_blending() {
	// Enable blending for transparency
	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void gw_rendering_pl::gw_clear_screen(glm::vec4 colour) {
	// Change the background colour to the colour variable
	GL_CALL(glClearColor(colour.r, colour.g, colour.b, colour.a));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void gw_rendering_pl::gw_bind_program(unsigned int shader_program_id) {
	// Bind a shader program via its id
	GL_CALL(glUseProgram(shader_program_id));
}

void gw_rendering_pl::gw_unbind_program() {
	// Unbind any shader programs
	GL_CALL(glUseProgram(0));
}
void gw_rendering_pl::gw_toggle_wireframe(bool wireframe) {
	if (wireframe) {
		GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	} else {
		GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	}
}
#pragma endregion
#pragma region gw_renderer implementation
gw_renderer::gw_renderer() 
	: cur_shader_program_id(0), cur_window(nullptr),
	project_matrix(NULL),
	view_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	model_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{}
gw_renderer::~gw_renderer() {
	// Delete the window variable as it was heap allocated
	DELETE_HALLOC(cur_window);
}
void gw_renderer::update_renderer() {
	// Enable wireframe mode
	// TODO: make this optional
	gw_rendering_pl::gw_toggle_wireframe(false);

	// Update the window
	cur_window->reevaluate();

	// Update the viewport size so it is resized with the window
	glViewport(0, 0, cur_window->get_winwidth(), cur_window->get_winheight());

	// Update the projection matrix so it is also resized along with window/viewport resize
	project_matrix = glm::ortho((float)-cur_window->get_winwidth(), (float)cur_window->get_winwidth(), (float)-cur_window->get_winheight(), (float)cur_window->get_winheight(), -1.0f, 1.0f);

	// Update the model-view-projection matrix
	glm::mat4 mvpMat = project_matrix * view_matrix * model_matrix;

	// Apply this matrix via the vertex shader
	shader_mgmt::modify_uniform_4m(&cur_shader_program_id, "u_ModelViewProjMat", mvpMat);
}
void gw_renderer::create_window(std::string title, int sizeX, int sizeY) {
	// Assign the window pointer
	cur_window = new gw_window(title, sizeX, sizeY);
}
void gw_renderer::initialize_shaders() {
	// Create the main shader program
	cur_shader_program_id = GL_CALL(glCreateProgram());

	// Necessary shaders - they are destroyed when outside the initialize_shaders scope
	gw_shader vertexShader("resources/shaders/vert.glsl", GL_VERTEX_SHADER, cur_shader_program_id);		// Vertex shader
	gw_shader fragmentShader("resources/shaders/frag.glsl", GL_FRAGMENT_SHADER, cur_shader_program_id);	// Fragment shader

	// Bind program
	gw_rendering_pl::gw_bind_program(cur_shader_program_id);
}
#pragma endregion