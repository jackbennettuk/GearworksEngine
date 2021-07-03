#include "Utility.h"

#include "gwrendering.h"

#include <depGL/glm/gtc/matrix_transform.hpp>

// GLFW error callback function
void util::glfwErrorCallback(int error, const char *description) {
	std::cout << std::endl << "[GLFW] Error (" << error << "): " << description << std::endl;
}

// Current-bound VAO function
int util::GetCurrentBoundVAO() {
	int result;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &result);

	return result;
}

// coord::InitWorldCoordSystem
void util::coord::InitWorldCoordSystem(unsigned int *program, float maxVal) {
	// Initialize the coordinate system to world space.
	// NOTE: The value '0.675' came about in trial and error. This is terrible practice and should be fixed at some point, but it works for now.
	// A conversion between world to screen coordinates or vice versa should also be made sooner or later.
	glm::mat4 projMat = glm::ortho(-maxVal, maxVal, (float)-(maxVal * 0.675f), (float)(maxVal * 0.675f), -1.0f, 1.0f);
	Shader::ModifyUniformmat4(program, "u_ModelViewProj", projMat);
}

// ColourRGBA255 struct
util::ColourRGBA255::ColourRGBA255(float _r, float _g, float _b, float _a) {
	r = _r / 255;
	g = _g / 255;
	b = _b / 255;
	a = _a / 255;
}