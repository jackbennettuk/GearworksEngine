#include <gearworks.h>
#include "engine.h"

engine::engine(gw_renderer *_renderer) 
	: renderer_handle(_renderer) {}

engine::~engine() {}

gw_rectangle_prim crate;
gw_triangle_prim triangle;

void engine::initialize() {
	crate.create(renderer_handle, glm::vec2(0.0f, 0.0f), glm::vec2(400.0f, 400.0f), "resources/textures/crate.png");

	glm::vec2 vertices[3] = {
		glm::vec2(80.0f, -200.0f),
		glm::vec2(300.0f, 200.0f),
		glm::vec2(520.0f, -200.0f)
	};
	triangle.create(renderer_handle, vertices, "resources/textures/wall.jpeg");
}

void engine::update() {
}

void engine::render() {
	crate.render();
	triangle.render();
}

void engine::clean() {}