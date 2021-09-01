#include <gearworks.h>

gearworks::triangle tri;
gearworks::rectangle rect;
gearworks::cuboid cube;

void gearworks::engine::initialize() {
	rect.create(renderer, "resources/textures/crate.png", vec3(0, 0, -500), vec2(100));
	tri.create(renderer, GEAR_EQUILATERAL_TRI, "resources/textures/wall.jpeg", vec3(0, 0, -500), vec2(100, 150));

	cube.create(renderer, "resources/textures/crate.png", vec3(0, 0, 500), vec3(100, 10, 100), vec3(45, 45, 0));
}
void gearworks::engine::update() {
	tri.properties.rotation.y -= 2;
	rect.properties.rotation.y += 2;

	cube.rotate(2, 2, 0);

	if (input->get_key(GLFW_KEY_W)) { renderer->view_matrix = glm::rotate(renderer->view_matrix, glm::radians(-2.0f), vec3(1, 0, 0)); }
	if (input->get_key(GLFW_KEY_A)) { renderer->view_matrix = glm::rotate(renderer->view_matrix, glm::radians( 2.0f), vec3(0, 1, 0)); }
	if (input->get_key(GLFW_KEY_S)) { renderer->view_matrix = glm::rotate(renderer->view_matrix, glm::radians( 2.0f), vec3(1, 0, 0)); }
	if (input->get_key(GLFW_KEY_D)) { renderer->view_matrix = glm::rotate(renderer->view_matrix, glm::radians(-2.0f), vec3(0, 1, 0)); }
}
void gearworks::engine::render() {
	// Clears the screen to a dark grey colour.
	gearworks::clear_screen(gearworks::col_verydarkgray);

	rect.render();
	tri.render();
	cube.render();
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