#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <opengl/glm/gtc/type_ptr.hpp>

class gw_primitive {
private:
	// Vectors to cache transformations that have not yet been applied.
	// These get released in the private apply_transformations() function, which is run directly before glDrawElements().
	glm::vec3 active_translation;
	glm::vec3 active_scaling;
	float active_rotation;
	glm::vec3 active_rotation_axes;

	void apply_transformations() {
		glm::mat4 applied_transformation = glm::mat4(1.0f);

		applied_transformation = glm::translate(applied_transformation, active_translation);
		applied_transformation = glm::rotate(applied_transformation, active_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
		applied_transformation = glm::scale(applied_transformation, active_scaling);
		
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
		active_rotation(0.0f),
		active_rotation_axes(glm::vec3(1.0f)),
		active_scaling(glm::vec3(1.0f)),
		active_translation(glm::vec3(1.0f))
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
	void translate(glm::vec3 transformation) { active_translation += transformation; }			// cache a translation to be applied in render()

	/// <summary>
	/// <para>Rotates the primitive by a given amount.</para>
	/// </summary>
	/// <param name="scaling">The amount to rotate by in degrees.</param>
	/// <param name="axes">The axes to rotate around.</param>
	void rotate(float rotation, glm::vec3 axes) { 
		// The rotation is subtracted instead of added so that the object rotates clockwise by default.
		active_rotation -= glm::radians(rotation);												// cache a rotation amount to be applied in render()
		active_rotation_axes = axes;
	}	

	/// <summary>
	/// <para>Scales the primitive by a given amount.</para>
	/// </summary>
	/// <param name="scaling">The amount to scale by.</param>
	void scale(glm::vec3 scaling) { active_scaling += scaling; }								// cache an amount to be scaled by
};

#endif