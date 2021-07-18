#ifndef TRIANGLE_PRIMITIVE_H
#define TRIANGLE_PRIMITIVE_H

class gw_triangle_prim {
private:
	// Pointer to renderer object
	gw_renderer *renderer_handle;

	// IBO, VBOs, VAO
	gw_vertex_array_object vao;
	gw_index_buffer_object ibo;

	// The default-used indices
	unsigned int indices[3] = { 0, 1, 2 };
public:
	// The colour of the triangle as a vec4
	glm::vec4 colour;
	// Texture
	texture_2d texture_object;

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
	/// <para>A colour and a texture may be given.</para>
	/// </summary>
	/// <param name="renderer">The renderer that the triangle will be 'bound' to.</param>
	/// <param name="vertices">The starting vertex coordinates to use.</param>
	/// <param name="texture">The texture to use for the triangle.</param>
	/// <param name="colour">The colour to render the triangle. Default is white.</param>
	void create(gw_renderer *renderer, glm::vec2 vertices[3], std::string texture_path, glm::vec4 blend_colour = glm::vec4(1.0, 1.0, 1.0, 1.0)) {
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

		// Reset translation
		translation = glm::vec2(0);

		// Initialize the VAO
		vao.initialize();

		// Initialize a new VBO
		gw_vertex_buffer_object vbo;
		vbo.initialize(15, vbo_data);
		// Initialize the IBO
		ibo.initialize(3, indices);

		// Enable and define the position attribute for the position vertex buffer
		vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		// Enable and define the texture coordinate attribute
		vao.add_vb_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

		// Create and initially bind the texture
		texture_object.load_texture(texture_path);
		texture_object.bind();
	}

	/// <summary>
	/// <para>Renders the Triangle primitive via glDrawElements.</para>
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

		// Set the renderer model matrix state to factor in the translation of this triangle
		renderer_handle->model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		renderer_handle->update_renderer();

		// Draw the triangle
		GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));

		// Unbind the VAO
		vao.unbind();

		// Unbind the texture object
		texture_object.unbind();
	}
};

#endif