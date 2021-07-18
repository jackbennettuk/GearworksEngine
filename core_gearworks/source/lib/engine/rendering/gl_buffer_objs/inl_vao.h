#ifndef VAO_H
#define VAO_H

class gw_vertex_array_object {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int renderer_id = 0;
public:
	// rendererID getter
	inline unsigned int get_rendererid() { return renderer_id; }

	/// <summary>
	/// <para>The default constructor for the VAO. IMPORTANT: This constructor does NOT generate a VAO! To do that, you must call vertex_array_object.initialize()!</para>
	/// </summary>
	inline gw_vertex_array_object() {}

	/// <summary>
	/// <para>Initializes the VAO.</para>
	/// </summary>
	inline void initialize() {
		// Generate the vertex array
		GL_CALL(glGenVertexArrays(1, &renderer_id));
	}

	/// <summary>
	/// <para>Binds the vertex array object</para>
	/// </summary>
	inline void bind() {
		// Binds the vertex array to rendererID
		GL_CALL(glBindVertexArray(renderer_id));
	}
	/// <summary>
	/// <para>Unbinds the vertex array object, overriding it with '0'.</para>
	/// </summary>
	inline void unbind() {
		// Binds the vertex array to 0
		GL_CALL(glBindVertexArray(0));
	}

	/// <summary>
	/// <para>Adds a vertexattrib to a given vertex buffer with given parameters rather than a pre-made Vertex Buffer Layout.</para>
	/// <para>For parameter information please see the official documentation for the glVertexAttribPointer() OpenGL method.</para>
	/// </summary>
	inline void add_vb_attrib(gw_vertex_buffer_object &vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
		// Bind this VAO
		bind();
		// Bind the given VBO first
		vbo.bind();

		GL_CALL(glEnableVertexAttribArray(index));
		GL_CALL(glVertexAttribPointer(index, size, type, normalized, stride, pointer));

		// Unbind the VAO
		unbind();
		// Unbind the VBO and delete it via its deconstructor
		vbo.unbind();
	}
};

#endif