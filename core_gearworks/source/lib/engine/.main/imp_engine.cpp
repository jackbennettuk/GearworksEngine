#include <gearworks.h>
#include "engine.h"

#include <opengl/glm/gtx/string_cast.hpp>

engine::engine(gw_renderer *_renderer) 
	: renderer_handle(_renderer) {}

engine::~engine() {}

gw_rectangle_prim crate;
gw_triangle_prim triangle;

void engine::initialize() {
	crate.create(renderer_handle, glm::vec2(-200.0f, 0.0f), glm::vec2(400.0f, 400.0f), "resources/textures/crate.png");

	glm::vec2 vertices[3] = {
		glm::vec2(80.0f, -200.0f),
		glm::vec2(300.0f, 200.0f),
		glm::vec2(520.0f, -200.0f)
	};
	triangle.create(renderer_handle, vertices, "resources/textures/wall.jpeg");
}

void engine::update() {
	// Set the renderer model matrix state to factor in the translation of this triangle
	renderer_handle->update_renderer();
}

void engine::render() {
	crate.render();
	triangle.render();
}

void engine::clean() {}