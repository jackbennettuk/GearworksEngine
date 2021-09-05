#include "p2d_triangle.h"

void gearworks::triangle::create(gearworks::renderer *renderer, unsigned int type, string texture_path, vec3 position, vec3 scale, vec3 rotation, vec3 vertices[3], vec3 blend_colour, float blend_opacity) {
	// Specify that the type of primitive here is triangle, or 0.
	primitive_type = 0;

	// Allocate texture object pointer
	texture_object = new gearworks::texture_2d();

	// Initialize variables here, except this time with parameters
	renderer_handle = renderer;
	properties.colour = blend_colour;
	properties.opacity = blend_opacity;

	// This float array is the data to be set for the vbo.
	// It stores the position data by converting the given vec2s to one unified standard float array.
	// These positions are in order: bottom_left, top, bottom_right
	// It also stores the texture coordinates in the same order.
	float *vbo_data;

	switch (type) {
		case GEAR_EQUILATERAL_TRI:
			vbo_data = new float[] {
				// Position coordinates			// Texture coordinates
				-0.5f, -0.5f, 0.0f,						0.0f, 0.0f,
				 0.0f,  0.5f, 0.0f,						0.5f, 1.0f,
				 0.5f, -0.5f, 0.0f,						1.0f, 0.0f
			};

			if (vertices != nullptr)
				std::cout << "  Vertices were given to an equilateral triangle - these have not been used.\n";
			break;
		case GEAR_SCALENE_TRI:
			if (vertices != nullptr) {
				vbo_data = new float[] {
					// Position coordinates							// Texture coordinates :: TODO: make these dynamic
					vertices[0].x, vertices[0].y, vertices[0].z,	0.0f, 0.0f,
					vertices[1].x, vertices[1].y, vertices[1].z,	0.5f, 1.0f,
					vertices[2].x, vertices[2].y, vertices[2].z,	1.0f, 0.0f
				};
			} else {
				std::cout << "  The type of triangle given was scalene, but no vertices were given. The triangle has not been rendered.\n";
				// Actually, draw the triangle, just with no size at all.
				vbo_data = new float[] {
					// Position coordinates		// Texture coordinates
					0.0f, 0.0f, 0.0f,			0.0f, 0.0f,
					0.0f, 0.0f, 0.0f,			0.0f, 0.0f,
					0.0f, 0.0f, 0.0f,			0.0f, 0.0f,
				};
			}
			break;
		case GEAR_RIGHTANGLE_TRI:
			vbo_data = new float[] {
				// Position coordinates			// Texture coordinates
				-0.5f, -0.5f, 0.0f,				0.0f, 0.0f,
				 0.5f,  0.5f, 0.0f,				1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f,				1.0f, 0.0f
			};

			if (vertices != nullptr)
				std::cout << "  Vertices were given to an right-angle triangle - these have not been used.\n";
			break;
		default:
			std::cout << "  The type of triangle given was invalid; the triangle has not been rendered to avoid further errors.\n";
			// Actually, draw the triangle, just with no size at all.
			vbo_data = new float[] {
				// Position coordinates			// Texture coordinates
				0.0f, 0.0f, 0.0f,				0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,				0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,				0.0f, 0.0f,
			};
			break;
	}
	// Set the properties to the given values
	properties.position = position;
	properties.scale = scale;
	properties.rotation = rotation;

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
	if (texture_path != "") {
		texture_object->load(texture_path);
	} else {
		texture_object->load("../GWSDK/default/sprite/default_image_pixel_0.png");
	}
	texture_object->bind();
}