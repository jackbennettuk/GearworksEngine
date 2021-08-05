#include "defs.h"

#pragma region Rectangle

void gearworks::rectangle::apply_transformations() {
	// Variable to store the affected rotation axes
	glm::vec3 _active_rotation_axes = glm::vec3(0, 0, 0);

	// Get the affected axes for rotation
	// x/r axis
	if ((int)active_rotation.x != 1)
		_active_rotation_axes.x = 1;		// if the x value of active_rotation is being changed, then the x axis is being affected.
	else
		_active_rotation_axes.x = 0;		// if not, set that axis to 0.

	// y/g axis
	if ((int)active_rotation.y != 1)
		_active_rotation_axes.y = 1;		// if the y value of active_rotation is being changed, then the y axis is being affected.
	else
		_active_rotation_axes.y = 0;		// if not, set that axis to 0.

	// z/b axis
	if ((int)active_rotation.z != 1)
		_active_rotation_axes.z = 1;		// if the z value of active_rotation is being changed, then the z axis is being affected.
	else
		_active_rotation_axes.z = 0;		// if not, set that axis to 0.

	// Create an identity matrix to store the applied transformations
	glm::mat4 applied_transformation = glm::mat4(1.0f);

	// Add the active translation to the stored transformations variable
	applied_transformation = glm::translate(applied_transformation, active_translation);

	// Add the active rotation to the stored transformations variable, with the given axes being affected
	if (_active_rotation_axes.x != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.x, glm::vec3(_active_rotation_axes.x, 0, 0));
	if (_active_rotation_axes.y != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.y, glm::vec3(0, _active_rotation_axes.y, 0));
	if (_active_rotation_axes.z != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.z, glm::vec3(0, 0, _active_rotation_axes.z));

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

gearworks::rectangle::rectangle() :
	renderer_handle(nullptr),
	colour(NULL),
	texture_object(),
	vao(),
	ibo(),
	active_rotation(glm::vec3(0.0f)),
	active_scaling(glm::vec3(1.0f)),		// The matrix begins at 1x - default size.
	active_translation(glm::vec3(0.0f))
{}

void gearworks::rectangle::create(gearworks::renderer *renderer, glm::vec3 position, glm::vec3 scale, std::string texture_path, glm::vec4 blend_colour) {
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
	vertex_buffer_object vbo;
	vbo.initialize(20, vbo_data);
	// Initialize the IBO
	ibo.initialize(6, indices);

	// Enable and define the position attribute for the position vertex buffer
	vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	// Enable and define the texture coordinate attribute
	vao.add_vb_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	// Create and initially bind the texture
	texture_object.load(texture_path);
	texture_object.bind();
}

void gearworks::rectangle::render() {
	// Bind VAO and IBO
	vao.bind();
	ibo.bind();

	// Bind the texture if it was given
	texture_object.bind();

	// Set the texture and colour uniform
	modify_uniform_1i(renderer_handle->get_currentshaderprogram(), "u_Texture", 0);
	modify_uniform_4fv(renderer_handle->get_currentshaderprogram(), "u_Colour", colour);

	// Apply outstanding transformations.
	apply_transformations();

	// Draw the rectangle
	GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	// Unbind the VAO
	vao.unbind();

	// Unbind the texture object
	texture_object.unbind();
}

#pragma endregion
#pragma region Triangle

void gearworks::triangle::apply_transformations() {
	// Variable to store the affected rotation axes
	glm::vec3 _active_rotation_axes = glm::vec3(0, 0, 0);

	// Get the affected axes for rotation
	// x/r axis
	if ((int)active_rotation.x != 1)
		_active_rotation_axes.x = 1;		// if the x value of active_rotation is being changed, then the x axis is being affected.
	else
		_active_rotation_axes.x = 0;		// if not, set that axis to 0.

	// y/g axis
	if ((int)active_rotation.y != 1)
		_active_rotation_axes.y = 1;		// if the y value of active_rotation is being changed, then the y axis is being affected.
	else
		_active_rotation_axes.y = 0;		// if not, set that axis to 0.

	// z/b axis
	if ((int)active_rotation.z != 1)
		_active_rotation_axes.z = 1;		// if the z value of active_rotation is being changed, then the z axis is being affected.
	else
		_active_rotation_axes.z = 0;		// if not, set that axis to 0.

	// Create an identity matrix to store the applied transformations
	glm::mat4 applied_transformation = glm::mat4(1.0f);

	// Add the active translation to the stored transformations variable
	applied_transformation = glm::translate(applied_transformation, active_translation);

	// Add the active rotation to the stored transformations variable, with the given axes being affected
	if (_active_rotation_axes.x != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.x, glm::vec3(_active_rotation_axes.x, 0, 0));
	if (_active_rotation_axes.y != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.y, glm::vec3(0, _active_rotation_axes.y, 0));
	if (_active_rotation_axes.z != 0) applied_transformation = glm::rotate(applied_transformation, active_rotation.z, glm::vec3(0, 0, _active_rotation_axes.z));

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

gearworks::triangle::triangle() :
	renderer_handle(nullptr),
	colour(NULL),
	texture_object(),
	vao(),
	ibo(),
	active_rotation(glm::vec3(0.0f)),
	active_scaling(glm::vec3(1.0f)),		// The matrix begins at 1x - default size.
	active_translation(glm::vec3(0.0f))
{}

void gearworks::triangle::create(gearworks::renderer *renderer, glm::vec2 vertices[3], std::string texture_path, glm::vec4 blend_colour) {
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
	vertex_buffer_object vbo;
	vbo.initialize(15, vbo_data);
	// Initialize the IBO
	ibo.initialize(3, indices);

	// Enable and define the position attribute for the position vertex buffer
	vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	// Enable and define the texture coordinate attribute
	vao.add_vb_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	// Create and initially bind the texture
	texture_object.load(texture_path);
	texture_object.bind();
}

void gearworks::triangle::render() {
	// Bind VAO and IBO
	vao.bind();
	ibo.bind();

	// Bind the texture if it was given
	texture_object.bind();

	// Set the texture and colour uniform
	gearworks::modify_uniform_1i(renderer_handle->get_currentshaderprogram(), "u_Texture", 0);
	gearworks::modify_uniform_4fv(renderer_handle->get_currentshaderprogram(), "u_Colour", colour);

	// Apply outstanding transformations.
	apply_transformations();

	// Draw the triangle
	GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));

	// Unbind the VAO
	vao.unbind();

	// Unbind the texture object
	texture_object.unbind();
}

#pragma endregion