#ifndef RECTANGLE_PRIMITIVE_H
#define RECTANGLE_PRIMITIVE_H

class gw_rectangle_prim {
private:
	// Pointer to renderer object
	gw_renderer *renderer_handle;

	// IBO and VAO
	gw_vertex_array_object vao;
	gw_index_buffer_object ibo;

	// The default-used indices
	unsigned int indices[6] = { 0, 1, 2, 0, 3, 2 };

	// Bool as to whether textures or colours are being used
	bool using_textures;
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
	gw_rectangle_prim()
		: renderer_handle(nullptr), colour(NULL), translation(NULL), using_textures(NULL) {
	}
	// Destructor
	~gw_rectangle_prim() {}

	/// <summary>
	/// <para>Creates a Rectangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A texture can be given.</para>
	/// </summary>
	/// <param name="renderer">The renderer that the rectangle will be 'bound' to.</param>
	/// <param name="position">The STARTING(!) position coordinate of the rectangle primitive, with 0 as its center. (To change the position at runtime, change the translation variable.)</param>
	/// <param name="scale">The scale values of the rectangle primitive.</param>
	/// <param name="_texture_path">The path, as a string, to the texture.</param>
	void create_texture(gw_renderer *renderer, glm::vec2 _position, glm::vec2 scale, std::string _texture_path, bool trans_tex) {
		// Initialize variables here, except this time with parameters
		renderer_handle = renderer;
		translation = _position;

		using_textures = true;

		// This float array is the data to be set for the position VBO (or 'posVBO') variable.
		// It stores the position data by converting the given vec2s to one unified standard float array.
		// These positions are in order: bottom_left, bottom_right, top_right, top_left.
		// For this 'create' type, the texture coordinates are also given in this array.
		float vbo_data[] = {
			// Position coordinates														// Texture coordinates
			translation.r - (scale.r / 2), translation.g - (scale.g / 2), 0.0f,			0.0f, 0.0f,
			translation.r + (scale.r / 2), translation.g - (scale.g / 2), 0.0f,			1.0f, 0.0f,
			translation.r + (scale.r / 2), translation.g + (scale.g / 2), 0.0f,			1.0f, 1.0f,
			translation.r - (scale.r / 2), translation.g + (scale.g / 2), 0.0f,			0.0f, 1.0f
		};

		// Reset translation
		translation = glm::vec2(0);

		// Initialize the VAO
		vao.initialize();

		// Initialize a new VBO
		gw_vertex_buffer_object vbo;
		vbo.initialize(20, vbo_data);
		// Initialize the IBO
		ibo.initialize(6, indices);

		// Enable and define the position attribute
		vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		// Enable and define the texture coordinate attribute
		vao.add_vb_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

		// Create and initially bind the texture
		texture_object.load_texture(_texture_path, trans_tex);
		texture_object.bind();
	}

	/// <summary>
	/// <para>Creates a Rectangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A solid colour can be given.</para>
	/// </summary>
	/// <param name="renderer">The renderer that the rectangle will be 'bound' to.</param>
	/// <param name="position">The STARTING(!) position coordinate of the rectangle primitive, with 0 as its center. (To change the position at runtime, change the translation variable.)</param>
	/// <param name="scale">The scale values of the rectangle primitive.</param>
	/// <param name="_colour">The colour to render the rectangle. Default is pink.</param>
	void create_colour(gw_renderer *renderer, glm::vec2 _position, glm::vec2 scale, glm::vec4 _colour = glm::vec4(1.0, 0.0, 1.0, 1.0)) {
		// Initialize variables here, except this time with parameters
		renderer_handle = renderer;
		colour = _colour;
		translation = _position;

		using_textures = false;

		// This float array is the data to be set for the position VBO (or 'posVBO') variable.
		// It stores the position data by converting the given vec2s to one unified standard float array.
		// These positions are in order: bottom_left, bottom_right, top_right, top_left.
		// NOTE: the origin of the rectangle is IN THE CENTER.
		// There are no texture coordinates that are given in this type of rectangle.
		float vbo_data[] = {
			// Position coordinates
			translation.r - (scale.r / 2), translation.g - (scale.g / 2), 0.0f,
			translation.r + (scale.r / 2), translation.g - (scale.g / 2), 0.0f,
			translation.r + (scale.r / 2), translation.g + (scale.g / 2), 0.0f,
			translation.r - (scale.r / 2), translation.g + (scale.g / 2), 0.0f
		};

		// Reset translation
		translation = glm::vec2(0);

		// Initialize the VAO
		vao.initialize();

		// Initialize a new VBO and the IBO
		gw_vertex_buffer_object vbo; vbo.initialize(12, vbo_data);
		ibo.initialize(6, indices);

		// Enable and define the position attribute for the position vertex buffer
		vao.add_vb_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}

	/// <summary>
	/// <para>Renders the Rectangle primitive via glDrawElements.</para>
	/// </summary>
	void render() {
		// Bind VAO and IBO
		vao.bind();
		ibo.bind();

		// Bind the texture if it was given
		if (using_textures) texture_object.bind();

		// Set the renderer model matrix state to factor in the translation of this triangle
		renderer_handle->model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(translation, 0));
		renderer_handle->update_renderer();

		// Make sure any textures that have been given are being used
		shader_mgmt::modify_uniform_1i(renderer_handle->get_currentshaderprogram(), "u_UsingTexture", (using_textures ? 1 : 0));
		// Set the texture or colour uniform depending on which one is being used
		if (using_textures) shader_mgmt::modify_uniform_1i(renderer_handle->get_currentshaderprogram(), "u_Texture", 0);
		else shader_mgmt::modify_uniform_4fv(renderer_handle->get_currentshaderprogram(), "u_Colour", colour);

		// Draw the triangle
		GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		// Unbind the VAO
		vao.unbind();

		// Unbind the texture
		texture_object.unbind();
	}
};

#endif