#include "Engine.h"

#include "gwrendering.h"
#include "gwassets.h"

Engine::Engine(Renderer *_renderer)
	: renderer(_renderer) {}
Engine::~Engine() {}

Rectangle *red;
Rectangle *green;
Rectangle *blue;

VertexArrayObject r;
VertexArrayObject g;
VertexArrayObject b;

// Initialization logic here
void Engine::Initialize() {
	r.Initialize();
	g.Initialize();
	b.Initialize();

	red = new Rectangle(&r, renderer, glm::vec2(-240, 0), glm::vec2(200), glm::vec4(1.0, 0.0, 0.0, 1.0));
	green = new Rectangle(&g, renderer, glm::vec2(0, 0), glm::vec2(200), glm::vec4(0.0, 1.0, 0.0, 1.0));
	blue = new Rectangle(&b, renderer, glm::vec2(240, 0), glm::vec2(200), glm::vec4(0.0, 0.0, 1.0, 1.0));
}

// Updating variables etc
void Engine::Update() {}

// Rendering shapes etc
void Engine::Render() {
	red->Render();
	green->Render();
	blue->Render();
}

// Pointer deletion
void Engine::Clean() {
	DELETE_HALLOC(red);
	DELETE_HALLOC(green);
	DELETE_HALLOC(blue);
}