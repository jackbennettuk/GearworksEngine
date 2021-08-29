#include "p2d_def.h"

void defshape::apply_transformations() {

	// Create an identity matrix to store the applied transformations
	glm::mat4 applied_transformation = glm::mat4(1.0f);

	// Add the active translation to the stored transformations variable
	applied_transformation = glm::translate(applied_transformation, active_translation);

	// Add the active rotation to the stored transformations variable, with the given axes being affected
	if (active_rotation.x != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.x, glm::vec3(1, 0, 0));
	if (active_rotation.y != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.y, glm::vec3(0, 1, 0));
	if (active_rotation.z != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.z, glm::vec3(0, 0, 1));

	// Add the active scale to the stored transformations variable
	applied_transformation = glm::scale(applied_transformation, active_scaling);

	// Apply these changes to the renderer by setting its model matrix and then updating it
	renderer_handle->model_matrix = applied_transformation;
	renderer_handle->update_renderer();

	// Reset the translation of the model matrix back to 0
	// This step ensures that the object rotates around its local origin, rather than the world space origin
	applied_transformation = glm::translate(applied_transformation, glm::vec3(0.0f));

	// Then apply this change to the renderer.
	renderer_handle->model_matrix = applied_transformation;
	renderer_handle->update_renderer();
}

defshape::defshape() :
	renderer_handle(nullptr),
	colour(NULL),
	texture(),
	vao(),
	ibo(),
	active_rotation(glm::vec3(0.0f)),
	active_scaling(glm::vec3(1.0f)),		// The matrix begins at 1x size.
	active_translation(glm::vec3(0.0f)),
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

	// Set the texture and colour uniform
	gearworks::modify_uniform_1i(renderer_handle->get_currentshaderprogram(), "u_Texture", 0);
	gearworks::modify_uniform_4fv(renderer_handle->get_currentshaderprogram(), "u_Colour", colour);

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

	// Apply outstanding transformations.
	apply_transformations();

	// Draw the rectangle
	GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	// Unbind the VAO
	vao.unbind();

	// Unbind the texture object
	texture_object->unbind();
}

#pragma endregion