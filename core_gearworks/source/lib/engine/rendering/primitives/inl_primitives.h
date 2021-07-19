#ifndef PRIMITIVES_H
#define PRIMITIVES_H

class gw_primitive {
private:
	// Vectors to cache transformations that have not yet been applied.
	// These get released in the private apply_transformations() function, which is run directly before glDrawElements().
	glm::vec3 active_translation;
	glm::vec3 active_scaling;
	glm::vec3 active_rotation;

	// This function applies any outstanding transformations to the primitive.
	// It is only ever run in the base render() function, and so it can be private.
	// In order to publicly transform the primitive, use the translate(), scale(), and rotate() functions.
	void apply_transformations() {
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
protected:
	// Pointer to renderer object
	gw_renderer *renderer_handle;

	// IBO and VAO
	gw_vertex_array_object vao;
	gw_index_buffer_object ibo;

	// Primitive type:- (for some functions in render())
	//	 0 = triangle
	//	 1 = rectangle
	unsigned int primitive_type;
public:
	// The colour of the primitive
	glm::vec4 colour;
	// Texture used for the primitive
	texture_2d texture_object;

	// The constructor's contents have been moved to create() to avoid usage of the 'new' keyword.
	/// <summary>
	/// <para>Default constructor. Note: to actually create the primitive with vertex coordinates etc, use the create() function.</para>
	/// </summary>
	gw_primitive() :
		renderer_handle(nullptr), 
		colour(NULL),
		texture_object(),
		vao(),
		ibo(),
		primitive_type(0),
		active_rotation(glm::vec3(0.0f)),
		active_scaling(glm::vec3(1.0f)),		// The matrix begins at 1x - default - size.
		active_translation(glm::vec3(0.0f))
	{}
	// Destructor
	~gw_primitive() {}

	/// <summary>
	/// <para>Renders the primitive via glDrawElements.</para>
	/// </summary>
	void render() {
		// Bind VAO and IBO
		vao.bind();
		ibo.bind();

		// Bind the texture if it was given
		texture_object.bind();

		// Set the texture and colour uniform
		shader_mgmt::modify_uniform_1i(renderer_handle->get_currentshaderprogram(), "u_Texture", 0);
		shader_mgmt::modify_uniform_4fv(renderer_handle->get_currentshaderprogram(), "u_Colour", colour);

		// Draw the triangle
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
				std::cout << "[GW] Error: invalid primitive_type given in file inl_primitives!\n";
				break;
		}

		// Apply outstanding transformations.
		apply_transformations();
		GL_CALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));

		// Unbind the VAO
		vao.unbind();

		// Unbind the texture object
		texture_object.unbind();
	}

	/// <summary>
	/// <para>Translates, or moves, the primitive by a given distance.</para>
	/// </summary>
	/// <param name="transformation">The distance to move by in x, y, and z.</param>
	void translate(glm::vec3 transformation) { active_translation += transformation; }				// cache a translation to be applied in render()

	/// <summary>
	/// <para>Rotates the primitive by a given amount.</para>
	/// </summary>
	/// <param name="scaling">The amount to rotate by in degrees.</param>
	/// <param name="axes">The axes to rotate around.</param>
	void rotate(glm::vec3 rotation) { active_rotation += + glm::radians(rotation); }	// cache a rotation amount to be applied in render()

	/// <summary>
	/// <para>Scales the primitive by a given amount.</para>
	/// </summary>
	/// <param name="scaling">The amount to scale by.</param>
	void scale(glm::vec3 scaling) { active_scaling += scaling; }									// cache an amount to be scaled by
};

#endif