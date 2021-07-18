#ifndef VBO_H
#define VBO_H

class gw_vertex_buffer_object {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int renderer_id;
public:
	// rendererID getter
	inline unsigned int get_rendererid() { return renderer_id; }

	/// <summary>
	/// <para>The default constructor for the VBO. IMPORTANT: This constructor does NOT generate a VBO! To do that, you must call vertex_buffer_object.initialize()!</para>
	/// </summary>
	inline gw_vertex_buffer_object() 
		: renderer_id(NULL) {}

	/// <summary>
	/// <para>Initializes the VBO.</para>
	/// </summary>
	/// <param name="count">The amount of items in the array "data"</param>
	/// <param name="data">The array of positions, given as floats, for the VBO</param>
	inline void initialize(unsigned int count, float data[]) {
		// Initialize rendererID as a newly-generated buffer object
		GL_CALL(glGenBuffers(1, &renderer_id));

		// Bind the buffer so that the following function works
		bind();
		// Set the data of the VBO based on count and data
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));
		// Initially unbind the buffer so that it is bound through the VAO at render-time
		unbind();
	}

	/// <summary>
	/// <para>Binds the Vertex Buffer Object to GL_ARRAY_BUFFER</para>
	/// </summary>
	inline void bind() {
		// Bind rendererID to the GL_ARRAY_BUFFER constant
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
	}
	/// <summary>
	/// <para>Binds 0 to GL_ARRAY_BUFFER, overriding the Vertex Buffer Object</para>
	/// </summary>
	inline void unbind() {
		// Unbinds this buffer by binding 0 to GL_ARRAY_BUFFER, effectively overriding rendererID
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
};

#endif