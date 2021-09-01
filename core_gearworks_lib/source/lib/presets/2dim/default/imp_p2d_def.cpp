#include "p2d_def.h"

defshape::shape_properties_struct::shape_properties_struct() :
	colour(NULL),
	opacity(255),
	position(vec3(0)),
	rotation(vec3(0)),
	scale(vec3(1))
{}

void defshape::apply_transformations() {
	// Create an identity matrix to store the applied transformations
	mat4 applied_transformation = mat4(1.0f);

	// Add the active translation to the stored transformations variable
	applied_transformation = glm::translate(applied_transformation, properties.position);

	// Add the active rotation to the stored transformations variable, with the given axes being affected
	if (properties.rotation.z != 0) applied_transformation = glm::rotate(applied_transformation, -glm::radians(properties.rotation.z), vec3(0, 0, 1));
	if (properties.rotation.y != 0) applied_transformation = glm::rotate(applied_transformation, -glm::radians(properties.rotation.y), vec3(0, 1, 0));
	if (properties.rotation.x != 0) applied_transformation = glm::rotate(applied_transformation, -glm::radians(properties.rotation.x), vec3(1, 0, 0));

	// Add the active scale to the stored transformations variable
	applied_transformation = glm::scale(applied_transformation, properties.scale);

	// Apply these changes to the renderer by setting its model matrix and then updating it
	renderer_handle->model_matrix = applied_transformation;
	renderer_handle->update_renderer();

	// Reset the translation of the model matrix back to 0
	// This step ensures that the object rotates around its local origin, rather than the world space origin
	applied_transformation = glm::translate(applied_transformation, vec3(0.0f));

	// Then apply this change to the renderer.
	renderer_handle->model_matrix = applied_transformation;
	renderer_handle->update_renderer();
}

defshape::defshape() :
	renderer_handle(nullptr),
	vao(),
	ibo(),
	primitive_type(0),
	texture_object(nullptr)
{}
defshape::~defshape() {
	DELETE_HALLOC(texture_object);
}

void defshape::render() {
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
	switch (primitive_type) {
		case 0:		// triangle
			count = 3;
			break;
		case 1:		// rectangle
			count = 6;
			break;
		default:
			count = 0;
			std::cout << "  Error: invalid primitive_type given in file inl_primitives!\n";
			break;
	}
	
	// Update transformation with variables and user input
	apply_transformations();

	// Draw the rectangle
	GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	// Unbind the VAO
	vao.unbind();

	// Unbind the texture object
	texture_object->unbind();
}

#pragma endregion