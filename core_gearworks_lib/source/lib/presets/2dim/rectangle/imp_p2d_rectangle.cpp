#include "p2d_rectangle.h"

void gearworks::rectangle::create(gearworks::renderer *renderer, glm::vec3 position, glm::vec3 scale, std::string texture_path, glm::vec4 blend_colour) {
	// Specify that the type of primitive here is rectangle, or 1.
	primitive_type = 1;

	// Allocate texture object pointer
	texture_object = new gearworks::texture_2d();

	// Initialize variables here, except this time with parameters
	renderer_handle = renderer;
	colour = blend_colour;

	// This float array is the data to be set for the vbo.
	// It stores the position data by converting the given vec2s to one unified standard float array.
	// These positions are in order: bottom_left, bottom_right, top_right, top_left.
	// It also stores the texture coordinates in the same order.
	float vbo_data[] = {
		// Position coordinates												// Texture coordinates
		position.x - (scale.x / 2), position.y - (scale.y / 2), 0.0f,		0.0f, 0.0f,
		position.x + (scale.x / 2), position.y - (scale.y / 2), 0.0f,		1.0f, 0.0f,
		position.x + (scale.x / 2), position.y + (scale.y / 2), 0.0f,		1.0f, 1.0f,
		position.x - (scale.x / 2), position.y + (scale.y / 2), 0.0f,		0.0f, 1.0f
	};

	// Initialize the VAO
	vao.initialize();
	// Initialize a new VBO
	vertex_buffer_object vbo;
	vbo.initialize(20, vbo_data);
	// Initialize the IBO
	ibo.initialize(6, indices);

	// Enable and define the position attribute for the position vertex buffer
	vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	// Enable and define the texture coordinate attribute
	vao.add_vb_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	// Create and initially bind the texture
	texture_object->load(texture_path);
	texture_object->bind();
}

#pragma endregion