#include "Texture2D.h"

#include "gwutility.h"

#include "stb/stb_image.h"

// Constructor
Texture2D::Texture2D(std::string _path)
	: rendererID(0), path(_path), width(0), height(0), bitPerPix(0) {
	// Flips the texture vertically
	// This is because the way OpenGL expects textures is vertically opposite the way Gearworks expects them
	stbi_set_flip_vertically_on_load(1);

	// Loads the texture with references to width, height, bpp
	// The reason the desired channels is 4 is because RGBA is being used (r, g, b, a = 4 channels)
	// In this case, store the texture image to the new localBuffer variable
	auto localBuffer = stbi_load(path.c_str(), &width, &height, &bitPerPix, 4);

	// Check if there was an error when loading the texture
	if (stbi_failure_reason()) {
		std::cout << "\n[stb] Error: " << stbi_failure_reason() << "\n";
	}

	// Generates and binds the texture buffer
	GL_CALL(glGenTextures(1, &rendererID));
	Bind();

	// This parameter defines how the texture will be scaled down
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	// This parameter defines how the texture will be scaled up
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// Thess parameter defines how the texture will be wrapped
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// Assign the image at [path] to be set to the GL_TEXTURE_2D
	// Also move the texture data to the GPU for use by the fragment shader
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));

	// Unbind the texture by default afterwards
	Unbind();
	// Free the image from the localBuffer variable
	if (localBuffer) {
		stbi_image_free(localBuffer);
	}
}

// Destructor
Texture2D::~Texture2D() {
	// Delete the texture
	GL_CALL(glDeleteTextures(1, &rendererID));
}

// Bind function
void Texture2D::Bind(unsigned int slot) {
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, rendererID));
}

// Unbind function
void Texture2D::Unbind() {
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}