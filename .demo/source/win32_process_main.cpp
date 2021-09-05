#include <gearworks.h>

gearworks::rectangle rect;
gearworks::cuboid cube;

void gearworks::engine::initialize() {
	rect.create(renderer, "resources/textures/crate.png", vec3(50, 0, 30), vec3(20), vec3(0), gearworks::col_orange);
	cube.create(renderer, "resources/textures/crate.png", vec3(0, 0, 30), vec3(20), vec3(45, 45, 0), gearworks::col_brightblue);
}
void gearworks::engine::update() {
	rect.properties.rotation.z += 2;
	cube.rotate(1, 2, 0);
	
	if (input->get_key_down(GLFW_KEY_SPACE)) {
		if (glfwGetInputMode(renderer->get_currentwindowinstance()->get_glfwinstance(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
			glfwSetInputMode(renderer->get_currentwindowinstance()->get_glfwinstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		} else if (glfwGetInputMode(renderer->get_currentwindowinstance()->get_glfwinstance(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
			glfwSetInputMode(renderer->get_currentwindowinstance()->get_glfwinstance(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	// First-person movement
	if (input->get_key(GLFW_KEY_W))	camera->properties.position -= camera->properties.forward;
	if (input->get_key(GLFW_KEY_S))	camera->properties.position -= camera->properties.back;
	if (input->get_key(GLFW_KEY_A))	camera->properties.position += camera->properties.left;
	if (input->get_key(GLFW_KEY_D))	camera->properties.position += camera->properties.right;

	// Rotation
	camera->rotate(input->get_cursoroffset().x * -0.1f, input->get_cursoroffset().y * 0.1f, 0.0f);

	if (camera->properties.pitch > 89.0f)
		camera->properties.pitch = 89.0f;
	if (camera->properties.pitch < -89.0f) {
		camera->properties.pitch = -89.0f;
	}
}
void gearworks::engine::render() {
	// Clears the screen to a dark grey colour.
	gearworks::clear_screen(gearworks::col_verydarkgray);

	rect.render();
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