#include "texture_2d.h"

#include <gearworks.h>

#include <stb/stb_image.h>

texture_2d::texture_2d() 
	: renderer_id(0), width(0), height(0), bits_per_pixel(0) {}

void texture_2d::load_texture(std::string _path) {
	// Initialize the local path variable.
	path = _path;

	// Flips the texture vertically
	// This is because the way OpenGL expects textures is vertically opposite the way Gearworks expects them
	stbi_set_flip_vertically_on_load(1);

	// Loads the texture with references to width, height, bpp
	// In this case, store the texture image to the new localBuffer variable
	unsigned char *local_buffer = stbi_load(path.c_str(), &width, &height, &bits_per_pixel, 4);

	// Check if there was an error when loading the texture
	if (stbi_failure_reason()) {
		std::cout << "[stbi] Error: " << stbi_failure_reason() << "\n";
	}

	// Generates and binds the texture buffer
	GL_CALL(glGenTextures(1, &renderer_id));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, renderer_id));

	// This parameter defines how the texture will be scaled down
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	// This parameter defines how the texture will be scaled up
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// Thess parameter defines how the texture will be wrapped
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// Assign the image at [path] to be set to the GL_TEXTURE_2D
	// Also move the texture data to the GPU for use by the fragment shader
	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));
	// Generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture by default afterwards
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	// Free the image from the localBuffer variable
	if (local_buffer) {
		stbi_image_free(local_buffer);
	}
}

void texture_2d::bind(unsigned int slot) {
	// Set the active texture slot to the parameter if it was given
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	// Bind the renderer id
	GL_CALL(glBindTexture(GL_TEXTURE_2D, renderer_id));
}

void texture_2d::unbind() {
	// Unbind any textures
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}