#ifndef TRIANGLE_PRIMITIVE_H
#define TRIANGLE_PRIMITIVE_H

class gw_triangle_prim {
private:
	// Pointer to renderer object
	gw_renderer *renderer_handle;

	// IBO, VBOs, VAO
	gw_vertex_array_object vao;
	gw_vertex_buffer_object vbo;
	gw_index_buffer_object ibo;

	// The default-used indices
	unsigned int indices[3] = { 0, 1, 2 };
public:
	// The colour of the triangle as a vec4
	glm::vec4 colour;
	// Translation variable that is set to be the default positions given in the constructor
	glm::vec2 translation;

	// (The constructor's contents have been moved to create() to avoid usage of the 'new' keyword.)
	// (Variables are set there so here they are just set to NULL/nullptr.)
	/// <summary>
	/// <para>Default constructor. Note: to actually create the triangle with vertex coordinates etc, use the create() function.</para>
	/// </summary>	
	gw_triangle_prim() 
		: renderer_handle(nullptr), colour(NULL), translation(NULL) {}
	// Destructor
	~gw_triangle_prim() {}

	/// <summary>
	/// <para>Creates a Triangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A solid colour can be given.</para>
	/// </summary>
	/// <param name="renderer">The renderer that the triangle will be 'bound' to.</param>
	/// <param name="vertices">The STARTING(!) vertex coordinates. To change the 'position' of the triangle at runtime, change the public translation variable.</param>
	/// <param name="_colour">The colour to render the triangle. Default is pink.</param>
	void create(gw_renderer *renderer, glm::vec2 vertices[3], glm::vec4 _colour = glm::vec4(1.0, 0.0, 1.0, 1.0)) {
		// Initialize variables here, except this time with parameters
		renderer_handle = renderer;
		colour = _colour;
		translation = glm::vec2(0);

		// Initialize the list of vertices as an array, so that OpenGL can read it
		// Note: the center of the triangle is 0, 0
		float vbo_data[9] = {
			vertices[0].r, vertices[0].g, 0.0f,
			vertices[1].r, vertices[1].g, 0.0f,
			vertices[2].r, vertices[2].g, 0.0f
		};

		// Initialize the VAO
		vao.initialize();

		// Initialize the VBO and IBO
		vbo.initialize(9, vbo_data);
		ibo.initialize(3, indices);

		// Enable and define the position attribute for the position vertex buffer
		vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}

	/// <summary>
	/// <para>Renders the Triangle primitive via glDrawElements.</para>
	/// </summary>
	void render() {
		// Bind VAO and IBO
		vao.bind();
		ibo.bind();

		// Set the renderer model matrix state to factor in the translation of this triangle
		renderer_handle->model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(translation, 0));
		renderer_handle->update_renderer();

		// Update colour uniform
		shader_mgmt::modify_uniform_4fv(renderer_handle->get_currentshaderprogram(), "u_Colour", colour);

		// Draw the triangle
		GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));

		// Unbind the VAO
		vao.unbind();
	}
};

#endif