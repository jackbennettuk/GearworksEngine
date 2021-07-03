#include "Engine.h"

#include "gwrendering.h"

// Set any variables here.
// If they require other libraries that have not yet been loaded, initialize the variables in the Initialize function
Rectangle *rect;

Engine::Engine(unsigned int *_mainShaderProgram)
	: mainShaderProgam(_mainShaderProgram) {
}
Engine::~Engine() {}

// Initialization logic here
void Engine::Initialize() {
	// Rectangle
	rect = new Rectangle(glm::vec2(0, 0), glm::vec2(200, 200));
}

// Updating variables etc
void Engine::Update() {

}

// Rendering shapes etc
void Engine::Render() {
	rect->Render();
}

// Pointer deletion
void Engine::Clean() {
	delete rect;
	rect = NULL;
}