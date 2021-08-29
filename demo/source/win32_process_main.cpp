#include <gearworks.h>

gearworks::rectangle rect;
gearworks::triangle tri;

void gearworks::engine::initialize() {
	rect.create(renderer_handle, glm::vec3(-300, 0, 0), glm::vec3(400), "resources/textures/crate.png");

	glm::vec2 vertices[3] = {
		glm::vec2(-200, -200),
		glm::vec2(0, 200),
		glm::vec2(200, -200)
	};

	tri.create(renderer_handle, vertices, "resources/textures/wall.jpeg");
	tri.translate(glm::vec3(300, 0, 0));
}
void gearworks::engine::update() {
	tri.rotate(glm::vec3(0, 0, 1));
}
void gearworks::engine::render() {
	// Clears the screen to a dark grey colour.
	gearworks::clear_screen(gearworks::col_verydarkgray);

	rect.render();
	tri.render();
}
void gearworks::engine::clean() 
{}

int main() {
	// Base gearworks behaviour object that handles all the behind-the-scenes logic
	gearworks::gwehaviour baseobj;

	// Set the base object's initial shaders
	baseobj.vertex_shader_path = "resources/shaders/vert.glsl";
	baseobj.fragment_shader_path = "resources/shaders/frag.glsl";

	// Initialize the base object
	baseobj.initialize();

	// Update the base object (This function runs every frame until the window is closed)
	baseobj.update();

	// Destroy the base object when the window is closed
	baseobj.destroy();

	// End the application successfully
	return 0;
}