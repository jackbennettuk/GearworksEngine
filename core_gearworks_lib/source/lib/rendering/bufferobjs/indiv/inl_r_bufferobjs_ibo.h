#ifndef INL_R_BUFFEROBJS_IBO_H
#define INL_R_BUFFEROBJS_IBO_H

class gearworks::index_buffer_object {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int renderer_id;
public:
	/// <returns>the renderer ID of the index buffer.</returns>
	inline unsigned int get_rendererid() { return renderer_id; }

	/// <summary>
	/// The default constructor for the IBO. IMPORTANT: This constructor does NOT generate a IBO! To do that, you must call index_buffer_object.initialize()!
	/// </summary>
	inline index_buffer_object()
		: renderer_id(NULL)
	{}

	/// <summary>
	/// Initializes the IBO.
	/// </summary>
	/// <param name="count">The amount of indices.</param>
	/// <param name="data">The array of indices.</param>
	inline void initialize(unsigned int count, unsigned int data[]) {
		// Initialize rendererID as a newly-generated index buffer object
		GL_CALL(glGenBuffers(1, &renderer_id));

		// Bind the IBO
		bind();
		// Set the data of the IBO based on count and data
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));
		// Then unbind the IBO so it can be tracked easier
		unbind();
	}

	/// <summary>
	/// Binds the Index Buffer Object to GL_ELEMENT_ARRAY_BUFFER
	/// </summary>
	inline void bind() {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
	}

	/// <summary>
	/// Binds 0 to GL_ARRAY_BUFFER, overriding the Index Buffer Object
	/// </summary>
	inline void unbind() {
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
};

#endif // header guard