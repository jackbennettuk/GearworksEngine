#include "Renderer.h"

// Constructor implementation
Renderer::Renderer() : shaderProgramID(0), window(nullptr), modelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))) {}

// Destructor implementation
Renderer::~Renderer() {
	// Delete the window variable as it was heap allocated
	DELETE_HALLOC(window);
}

// UpdateRendererInstance() implementation
void Renderer::UpdateRendererInstance() {
	// Update the window size variables
	window->UpdateWindowProperties();

	// Update the viewport size so it is resized with the window
	glViewport(0, 0, window->GetWindowSizeX(), window->GetWindowSizeY());

	// Create the projection matrix and update it so it is also resized along with window/viewport resize
	glm::mat4 projMat = glm::ortho((float)-window->GetWindowSizeX(), (float)window->GetWindowSizeX(), (float)-window->GetWindowSizeY(), (float)window->GetWindowSizeY(), -1.0f, 1.0f);
	// Create the view matrix
	glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	// Multiply these matrices together to create the ModelViewProjection matrix (MVP)
	glm::mat4 mvpMat = projMat * viewMat * modelMat;

	// Apply this matrix via the vertex shader
	Shader::ModifyUniformmat4(&shaderProgramID, "u_ModelViewProjMat", mvpMat);
}

// gwCreateWindow() implementation
void Renderer::gwCreateWindow(std::string title, int sizeX, int sizeY) {
	// Assign the window pointer
	window = new Window(title, sizeX, sizeY);
}

// InitializeShaders() implementation
void Renderer::InitializeShaders() {
	// Create the main shader program
	shaderProgramID = glCreateProgram();

	// Necessary shaders - they are destroyed when outside the InitializeShaders scope
	Shader vertexShader("resources/shaders/.vert", GL_VERTEX_SHADER, shaderProgramID);		// Vertex shader
	Shader fragmentShader("resources/shaders/.frag", GL_FRAGMENT_SHADER, shaderProgramID);	// Fragment shader

	// Bind the shader program
	BindShaderProgram();
}

// static EnableTransparentBlending() implementation
void Renderer::EnableTransparentBlending() {
	// Enable blending for transparency
	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

// static ClearScreen() implementation
void Renderer::ClearScreen(glm::vec4 colour) {
	// Change the background colour to a dark gray
	GL_CALL(glClearColor(colour.r, colour.g, colour.b, colour.a));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

// Bind and unbind function implementation 
void Renderer::BindShaderProgram() { GL_CALL(glUseProgram(shaderProgramID)); }
void Renderer::UnbindShaderProgram() { GL_CALL(glUseProgram(0)); }