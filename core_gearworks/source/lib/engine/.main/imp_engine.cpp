#include <gearworks.h>
#include "engine.h"

engine::engine(gw_renderer *_renderer) 
	: renderer_handle(_renderer) {}

engine::~engine() {}

gw_rectangle_prim rectangle;
gw_rectangle_prim rectangle1;
gw_rectangle_prim rectangle2;

void engine::initialize() {
	rectangle.create_texture(renderer_handle, glm::vec2(-330.0f, 0.0f), glm::vec2(300.0f, 300.0f), "resources/textures/crate.png");
	rectangle1.create_texture(renderer_handle, glm::vec2(0.0f, 0.0f), glm::vec2(300.0f, 222.0f), "resources/textures/logo.png");
	rectangle2.create_colour(renderer_handle, glm::vec2(330.0f, 0.0f), glm::vec2(300.0f, 300.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void engine::update() {
}

void engine::render() {
	rectangle.render();
	rectangle1.render();
	rectangle2.render();
}

void engine::clean() {}