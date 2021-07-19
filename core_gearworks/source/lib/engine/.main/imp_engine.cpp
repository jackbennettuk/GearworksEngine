#include <gearworks.h>
#include "engine.h"

#include <opengl/glm/gtx/string_cast.hpp>

engine::engine(gw_renderer *_renderer) 
	: renderer_handle(_renderer) {}

engine::~engine() {}

gw_rectangle_prim crate;

void engine::initialize() {
	crate.create(renderer_handle, glm::vec3(0.0f, 0.0f, 500.0f), glm::vec3(400.0f, 400.0f, 400.0f), "resources/textures/crate.png");
}

void engine::update() {
	crate.translate(glm::vec3(0.5f, 0.0f, 0.0f));
	crate.rotate(glm::vec3(0.0f, 0.0f, 0.05f));
	crate.scale(glm::vec3(0.0005f));
}

void engine::render() {
	crate.render();
}

void engine::clean() {}