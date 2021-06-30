#include "Utility.h"

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

// ColourRGBA255 struct
util::ColourRGBA255::ColourRGBA255(float _r, float _g, float _b, float _a) {
	r = _r / 255;
	g = _g / 255;
	b = _b / 255;
	a = _a / 255;
}