#include <gearworks.h>
#include "engine.h"

#include <opengl/glm/gtx/string_cast.hpp>

engine::engine(gw_renderer *_renderer) 
	: renderer_handle(_renderer) {}

engine::~engine() {}

gw_rectangle_prim crate;

int amt;

void engine::initialize() {
	crate.create(renderer_handle, glm::vec3(0.0f, 0.0f, 500.0f), glm::vec3(400.0f, 400.0f, 400.0f), "resources/textures/crate.png");
}

void engine::update() {
	renderer_handle->zoom_by_value(0.02f);
}

void engine::render() {
	crate.render();
}

void engine::clean() {}