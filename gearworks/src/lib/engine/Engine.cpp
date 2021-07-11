#include "Engine.h"

#include "gwrendering.h"

// Set any variables here.
// If they require other libraries that have not yet been loaded, initialize the variables in the Initialize function
Rectangle *rect;

VertexArrayObject rectVAO;

Engine::Engine(GWRenderer *renderer)
	: mainShaderProgram(renderer->GetShaderProgramID()) {
}
Engine::~Engine() {}

// Initialization logic here
void Engine::Initialize() {
	// Rectangle
	rectVAO.Initialize();
	rect = new Rectangle(&rectVAO, mainShaderProgram, glm::vec2(0.0f, 0.0f), glm::vec2(400.0f, 296.0f), "resources/textures/logo.png");
}

// Updating variables etc
void Engine::Update() {

}

// Rendering shapes etc
void Engine::Render() {
	rectVAO.Bind();
	rect->Render();
}

// Pointer deletion
void Engine::Clean() {
	delete rect;
	rect = NULL;

	rectVAO.Unbind();
}