#ifndef IBO_H
#define IBO_H

class gw_index_buffer_object {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int renderer_id;
public:
	// rendererID getter
	inline unsigned int get_rendererid() { return renderer_id; }

	/// <summary>
	/// <para>The default constructor for the IBO. IMPORTANT: This constructor does NOT generate a IBO! To do that, you must call index_buffer_object.initialize()!</para>
	/// </summary>
	inline gw_index_buffer_object() 
		: renderer_id(NULL) {}

	/// <summary>
	/// <para>Initializes the IBO.</para>
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
	/// <para>Binds the Vertex Buffer Object to GL_ARRAY_BUFFER</para>
	/// </summary>
	inline void bind() {
		// Bind rendererID to the GL_ELEMENT_ARRAY_BUFFER constant
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
	}
	/// <summary>
	/// <para>Binds 0 to GL_ARRAY_BUFFER, overriding the Vertex Buffer Object</para>
	/// </summary>
	inline void unbind() {
		// Unbinds this buffer by binding 0 to GL_ELEMENT_ARRAY_BUFFER, effectively overriding rendererID
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
};

#endif