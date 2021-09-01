#include <gearworks.h>

gearworks::rectangle rect;
gearworks::triangle tri;

void gearworks::engine::initialize() {
	rect.create(renderer, vec3(0, 0, 500), vec2(400, 250), "resources/textures/crate.png");
	rect.rotate(0, 90, 0);

	vec3 vertices[3] = {
		vec3(-100, -200, 0),
		vec3(0, 200, 0),
		vec3(100, -200, 0)
	};

	tri.create(renderer, vertices, "resources/textures/wall.jpeg");
	tri.translate(0, 0, 500);
}
void gearworks::engine::update() {
	rect.rotate(0, 1, 0);
	tri.rotate(0, -2, 0);

	if (input->get_key(GLFW_KEY_W)) { renderer->view_matrix = glm::rotate(renderer->view_matrix, glm::radians(1.0f), vec3(1, 0, 0)); }
	if (input->get_key(GLFW_KEY_A)) { renderer->view_matrix = glm::rotate(renderer->view_matrix, glm::radians(-1.0f), vec3(0, 1, 0)); }
	if (input->get_key(GLFW_KEY_S)) { renderer->view_matrix = glm::rotate(renderer->view_matrix, glm::radians(-1.0f), vec3(1, 0, 0)); }
	if (input->get_key(GLFW_KEY_D)) { renderer->view_matrix = glm::rotate(renderer->view_matrix, glm::radians(1.0f), vec3(0, 1, 0)); }
}
void gearworks::engine::render() {
	// Clears the screen to a dark grey colour.
	gearworks::clear_screen(gearworks::col_verydarkgray);

	tri.render();
	rect.render();
}
void gearworks::engine::clean() 
{}

int main() {
	// Base gearworks behaviour object that handles all the behind-the-scenes logic
	gearworks::engine game;

	// Set the base object's initial shaders
	game.vertex_shader_path = "resources/shaders/vert.glsl";
	game.fragment_shader_path = "resources/shaders/frag.glsl";

	// Initialize the base game
	game.behaviour_initialize();

	// Update the base game (This function runs every frame until the window is closed)
	game.behaviour_update();

	// Destroy the base game when the window is closed
	game.behaviour_destroy();

	// End the application successfully
	return 0;
}