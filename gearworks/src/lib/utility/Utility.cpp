#include "Utility.h"

#include "gwrendering.h"

unsigned int util::GetSizeOfType(unsigned int type) {
	// Switch the type
	switch (type) {
		// The size of a float is 4 - if the type is GL_FLOAT, return 4
		case GL_FLOAT: return 4;
		// The size of an unsigned int is 4 - if the type is GL_UNSIGNED_INT, return 4
		case GL_UNSIGNED_INT: return 4;
		// The size of an unsigned char, or unsigned byte, is 1 - if the type is GL_UNSIGNED_BYTE, return 1
		case GL_UNSIGNED_BYTE: return 1;
	}

	// If the type is invalid, return 0
	return 0;
}