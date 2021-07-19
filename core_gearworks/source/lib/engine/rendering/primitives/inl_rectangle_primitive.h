#ifndef RECTANGLE_PRIMITIVE_H
#define RECTANGLE_PRIMITIVE_H

#include "inl_primitives.h"

class gw_rectangle_prim : public gw_primitive {
private:
	// The default-used indices
	unsigned int indices[6] = { 0, 1, 2, 0, 3, 2 };
public:
	// Use the base 'primitive' constructor to initialize variables
	using gw_primitive::gw_primitive;

	/// <summary>
	/// <para>Creates a Rectangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A colour and a texture may be given.</para>
	/// </summary>
	/// <param name="renderer">The renderer that the rectangle will be 'bound' to.</param>
	/// <param name="position">The starting position coordinate of the rectangle primitive, with 0 as its center.</param>
	/// <param name="scale">The scale values of the rectangle primitive.</param>
	/// <param name="texture">The texture to use for the rectangle.</param>
	/// <param name="trans_tex">Set to true if the texture has transparent pixels; false if it does not.</param>
	/// <param name="colour">The colour to render the rectangle. Default is white.</param>
	void create(gw_renderer *renderer, glm::vec3 position, glm::vec3 scale, std::string texture_path, glm::vec4 blend_colour = glm::vec4(1.0, 1.0, 1.0, 1.0)) {
		// Specify that the type of primitive here is rectangle, or 1.
		primitive_type = 1;

		// Initialize variables here, except this time with parameters
		renderer_handle = renderer;
		colour = blend_colour;

		// This float array is the data to be set for the vbo.
		// It stores the position data by converting the given vec2s to one unified standard float array.
		// These positions are in order: bottom_left, bottom_right, top_right, top_left.
		// It also stores the texture coordinates in the same order.
		float vbo_data[] = {
			// Position coordinates												// Texture coordinates
			position.r - (scale.r / 2), position.g - (scale.g / 2), 0.0f,		0.0f, 0.0f,
			position.r + (scale.r / 2), position.g - (scale.g / 2), 0.0f,		1.0f, 0.0f,
			position.r + (scale.r / 2), position.g + (scale.g / 2), 0.0f,		1.0f, 1.0f,
			position.r - (scale.r / 2), position.g + (scale.g / 2), 0.0f,		0.0f, 1.0f
		};

		// Initialize the VAO
		vao.initialize();
		// Initialize a new VBO
		gw_vertex_buffer_object vbo;
		vbo.initialize(20, vbo_data);
		// Initialize the IBO
		ibo.initialize(6, indices);

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