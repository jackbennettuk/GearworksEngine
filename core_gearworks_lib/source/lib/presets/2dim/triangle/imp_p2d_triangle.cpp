#include "p2d_triangle.h"

void gearworks::triangle::create(gearworks::renderer *renderer, glm::vec2 vertices[3], std::string texture_path, glm::vec4 blend_colour) {
	// Specify that the type of primitive here is triangle, or 0.
	primitive_type = 0;

	// Allocate texture object pointer
	texture_object = new gearworks::texture_2d();

	// Initialize variables here, except this time with parameters
	renderer_handle = renderer;
	colour = blend_colour;

	// This float array is the data to be set for the vbo.
	// It stores the position data by converting the given vec2s to one unified standard float array.
	// These positions are in order: bottom_left, top, bottom_right
	// It also stores the texture coordinates in the same order.
	float vbo_data[] = {
		// Position coordinates						// Texture coordinates
		vertices[0].x, vertices[0].y, 0.0f,			0.0f, 0.0f,
		vertices[1].x, vertices[1].y, 0.0f,			0.5f, 1.0f,
		vertices[2].x, vertices[2].y, 0.0f,			1.0f, 0.0f
	};

	// Initialize the VAO
	vao.initialize();

	// Initialize a new VBO
	vertex_buffer_object vbo;
	vbo.initialize(15, vbo_data);
	// Initialize the IBO
	ibo.initialize(3, indices);

	// Enable and define the position attribute for the position vertex buffer
	vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	// Enable and define the texture coordinate attribute
	vao.add_vb_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	// Create and initially bind the texture
	texture_object->load(texture_path);
	texture_object->bind();
}