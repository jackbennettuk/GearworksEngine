#include <gearworks.h>

gearworks::rectangle paddle_1;
gearworks::rectangle paddle_2;
gearworks::cuboid testcube;

bool fps = false;

void gearworks::engine::initialize() {
	paddle_1.create(renderer, "", true, vec3(70, 0, 0), vec3(2, 23, 1), vec3(0));
	paddle_2.create(renderer, "", true, vec3(-70, 0, 0), vec3(2, 23, 1), vec3(0));

	testcube.create(renderer, "../GWSDK/default/sprite/default_image_tile.png", true, vec3(0), vec3(20));
}
void gearworks::engine::update() {
	if (input->get_key_down(GLFW_KEY_ESCAPE)) {
		if (fps) {
			fps = false;
			glfwSetInputMode(renderer->get_currentwindowinstance()->get_glfwinstance(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			input->center_cursor();
		} else {
			fps = true;
			glfwSetInputMode(renderer->get_currentwindowinstance()->get_glfwinstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	if (fps) {
		// First-person movement
		if (input->get_key(GLFW_KEY_SPACE))	camera->properties.position += vec3(0, 1, 0);
		if (input->get_key(GLFW_KEY_LEFT_SHIFT)) camera->properties.position -= vec3(0, 1, 0);
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
	} else {
		if (input->get_key(GLFW_KEY_UP))	paddle_1.translate(0, 1, 0);
		if (input->get_key(GLFW_KEY_DOWN))	paddle_1.translate(0, -1, 0);
		if (input->get_key(GLFW_KEY_W))		paddle_2.translate(0, 1, 0);
		if (input->get_key(GLFW_KEY_S))		paddle_2.translate(0, -1, 0);
	}

	testcube.rotate(1, 2, 0);
}
void gearworks::engine::render() {
	// Clears the screen to a blue colour
	gearworks::clear_screen(gearworks::col_black);

	paddle_1.render();
	paddle_2.render();
	testcube.render();
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