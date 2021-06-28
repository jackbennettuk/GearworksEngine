#include "Utility.h"

void util::glfwErrorCallback(int error, const char *description) {
	std::cout << std::endl << "[GLFW] Error (" << error << "): " << description << std::endl;
}