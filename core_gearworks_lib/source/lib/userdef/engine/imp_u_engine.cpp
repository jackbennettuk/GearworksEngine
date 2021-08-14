#include "u_engine.h"

gearworks::engine::engine()
	: renderer_handle(nullptr) {
}

void gearworks::engine::create(gearworks::renderer *_renderer) {
	// Updates private pointer to the renderer to the user-given renderer.
	renderer_handle = _renderer;
}