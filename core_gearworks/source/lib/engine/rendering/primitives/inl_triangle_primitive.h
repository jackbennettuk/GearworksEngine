#ifndef TRIANGLE_PRIMITIVE_H
#define TRIANGLE_PRIMITIVE_H

#include "inl_primitives.h"

class gw_triangle_prim : public gw_primitive {
private:
	// The default-used indices
	unsigned int indices[3] = { 0, 1, 2 };
public:
	// Use the base 'primitive' constructor to initialize variables
	using gw_primitive::gw_primitive;

	/// <summary>
	/// <para>Creates a Triangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A colour and a texture may be given.</para>
	/// </summary>
	/// <param name="renderer">The renderer that the triangle will be 'bound' to.</param>
	/// <param name="vertices">The starting vertex coordinates to use.</param>
	/// <param name="texture">The texture to use for the triangle.</param>
	/// <param name="colour">The colour to render the triangle. Default is white.</param>
	void create(gw_renderer *renderer, glm::vec2 vertices[3], std::string texture_path, glm::vec4 blend_colour = glm::vec4(1.0, 1.0, 1.0, 1.0)) {
		// Specify that the type of primitive here is triangle, or 1.
		primitive_type = 0;

		// Initialize variables here, except this time with parameters
		renderer_handle = renderer;
		colour = blend_colour;

		// This float array is the data to be set for the vbo.
		// It stores the position data by converting the given vec2s to one unified standard float array.
		// These positions are in order: bottom_left, top, bottom_right
		// It also stores the texture coordinates in the same order.
		float vbo_data[] = {
			// Position coordinates						// Texture coordinates
			vertices[0].r, vertices[0].g, 0.0f,			0.0f, 0.0f,
			vertices[1].r, vertices[1].g, 0.0f,			0.5f, 1.0f,
			vertices[2].r, vertices[2].g, 0.0f,			1.0f, 0.0f
		};

		// Initialize the VAO
		vao.initialize();

		// Initialize a new VBO
		gw_vertex_buffer_object vbo;
		vbo.initialize(15, vbo_data);
		// Initialize the IBO
		ibo.initialize(3, indices);

		// Enable and define the position attribute for the position vertex buffer
		vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		// Enable and define the texture coordinate attribute
		vao.add_vb_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

		// Create and initially bind the texture
		texture_object.load_texture(texture_path);
		texture_object.bind();
	}
};

#endif