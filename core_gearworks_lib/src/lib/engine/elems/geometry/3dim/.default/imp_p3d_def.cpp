#include "p3d_def.h"

defshape3d::defshape3d() :
	renderer_handle(nullptr),
	vao(),
	ibo(),
	shape_type(0),
	texture_object(nullptr)
{}
defshape3d::~defshape3d() {
	DELETE_HALLOC(texture_object);
}

void defshape3d::render() {
	// Bind VAO and IBO
	vao.bind();
	ibo.bind();

	// Bind the texture if it was given
	texture_object->bind();

	// Set the texture slot
	gearworks::modify_uniform_1i(renderer_handle->get_currentshaderprogram(), "u_Texture", 0);
	// Set the colour vec4
	gearworks::modify_uniform_4fv(renderer_handle->get_currentshaderprogram(), "u_Colour", 
		vec4(
			properties.colour.r / 255, 
			properties.colour.g / 255, 
			properties.colour.b / 255, 
			properties.opacity / 255
		)
	);

	// Draw the shape
	GLsizei count = 0;
	switch (shape_type) {
		case 0:		// cuboid
			count = 36;
			break;
		default:
			count = 0;
			std::cout << "  Error: invalid primitive_type given in file inl_primitives!\n";
			break;
	}
	
	// Update transformation with variables and user input
	apply_transformations(renderer_handle);

	// Draw the shape
	GL_CALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));

	// Unbind the VAO
	vao.unbind();

	// Unbind the texture object
	texture_object->unbind();
}

#pragma endregion