#include "p3d_cuboid.h"

void gearworks::cuboid::create(gearworks::renderer *renderer, string texture_path, vec3 position, vec3 scale, vec3 rotation, vec3 blend_colour, float blend_opacity) {
	// Specify that the type of primitive here is cuboid, or 0.
	shape_type = 0;

	// Allocate texture object pointer
	texture_object = new gearworks::texture_2d();

	// Initialize variables here, except this time with parameters
	renderer_handle = renderer;
	properties.colour = blend_colour;
	properties.opacity = blend_opacity;

	// The data to be set for the vbo.
	float vbo_data[] = {
		// Front					Tex-coord
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
		// Back						Tex-coord
		-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,
		// Left						Tex-coord
		-0.5f,  0.5f, -0.5f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,		1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,
		// Right					Tex-coord
		 0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,		0.0f, 1.0f,
		// Bottom					Tex-coord
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 1.0f,
		// Top	 					Tex-coord
		 0.5f,  0.5f, -0.5f,		0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,		1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,		0.0f, 1.0f
	};
	// Set the properties to the given values
	properties.position = position;
	properties.scale = scale;
	properties.rotation = rotation;

	// Initialize the VAO
	vao.initialize();

	// Initialize a new VBO
	vertex_buffer_object vbo;
	vbo.initialize(180, vbo_data);
	// Initialize the IBO
	ibo.initialize(36, indices);

	// Enable and define the position attribute for the position vertex buffer
	vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	// Enable and define the texture coordinate attribute
	vao.add_vb_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	// Create and initially bind the texture
	if (texture_path != "") {
		texture_object->load(texture_path);
	} else {
		texture_object->load("../GWSDK/default/sprite/default_image_pixel_0.png");
	}
	texture_object->bind();
}

#pragma endregion