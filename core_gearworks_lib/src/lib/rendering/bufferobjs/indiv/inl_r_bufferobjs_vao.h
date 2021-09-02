#ifndef _INL_R_BUFFEROBJS_VAO_H
#define _INL_R_BUFFEROBJS_VAO_H

class gearworks::vertex_array_object {
private:
	// The ID that is referred in GL commands such as glGenVertexArrays
	unsigned int renderer_id;
public:
	/// <returns>The renderer ID associated with this object.</returns>
	inline unsigned int get_rendererid() { return renderer_id; }

	/// <summary>
	/// The default constructor for the VAO. IMPORTANT: This constructor does NOT generate a VAO! To do that, you must call vertex_array_object.initialize()!
	/// </summary>
	inline vertex_array_object()
		: renderer_id(NULL)
	{}

	/// <summary>
	/// Initializes the VAO.
	/// </summary>
	inline void initialize() {
		// Generate the vertex array
		GL_CALL(glGenVertexArrays(1, &renderer_id));
	}

	/// <summary>
	/// Adds a vertexattrib to a given vertex buffer with given parameters rather than a pre-made Vertex Buffer Layout.
	/// For parameter information please see the official documentation for the glVertexAttribPointer() OpenGL method.
	/// </summary>
	inline void add_vb_attrib(vertex_buffer_object &vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
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

	/// <summary>
	/// Binds the Vertex Array Object.
	/// </summary>
	inline void bind() {
		// Binds the vertex array to rendererID
		GL_CALL(glBindVertexArray(renderer_id));
	}

	/// <summary>
	/// Unbinds the Vertex Array Object.
	/// </summary>
	inline void unbind() {
		// Binds the vertex array to 0
		GL_CALL(glBindVertexArray(0));
	}
};

#endif // header guard