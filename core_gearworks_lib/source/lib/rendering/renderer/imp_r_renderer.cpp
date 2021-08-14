#include "r_renderer.h"

gearworks::renderer::renderer() :
	cur_shader_program_id(0),
	cur_window(),
	project_matrix(NULL),
	view_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	model_matrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	current_zoom(1.0f)
{}
gearworks::renderer::~renderer() {
	DELETE_HALLOC(cur_window);
}

void gearworks::renderer::update_renderer() {
	// Update the window
	cur_window->reevaluate();

	// Update the viewport size so it is resized with the window
	glViewport(0, 0, cur_window->get_winwidth(), cur_window->get_winheight());

	// Update the projection matrix so it is also resized along with window/viewport resize
	// Also factor in zoom for zooming capabilities.
	project_matrix = glm::ortho(
		(float)-cur_window->get_winwidth() / current_zoom,
		(float)cur_window->get_winwidth() / current_zoom,
		(float)-cur_window->get_winheight() / current_zoom,
		(float)cur_window->get_winheight() / current_zoom
	);

	// Update the model-view-projection matrix
	glm::mat4 mvp_matrix = project_matrix * view_matrix * model_matrix;

	// Apply this matrix via the vertex shader
	gearworks::modify_uniform_4m(&cur_shader_program_id, "u_ModelViewProjMat", mvp_matrix);
}

void gearworks::renderer::create_window(std::string title, int sizeX, int sizeY) {
	// Heap-allocate the window variable
	cur_window = new gearworks::window();
	// Assign the window pointer
	cur_window->create_window(title, sizeX, sizeY);
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