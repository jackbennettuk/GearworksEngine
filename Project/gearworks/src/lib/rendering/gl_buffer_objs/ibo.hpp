#pragma once

#include "gwutility.h"

#include <depGL/Glad/glad.h>

class IndexBufferObject {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int rendererID;
public:
	/// <summary>
	/// <para>The IndexBufferObject constructor that generates an IBO with the given count and data</para>
	/// <para>The IBO is unbound by default - to bind it, call IndexBufferObject.Bind().</para>
	/// </summary>
	/// <param name="count">The amount of indices</param>
	/// <param name="data">The array of indices</param>
	inline IndexBufferObject(unsigned int count, unsigned int data[]) {
		// Initialize rendererID as a newly-generated index buffer object
		GL_CALL(glGenBuffers(1, &rendererID));
		// Bind rendererID to the GL_ELEMENT_ARRAY_BUFFER constant
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));

		// Set the data of the IBO based on count and data
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));
	}
	inline ~IndexBufferObject() {
		// Delete the buffer with rendererID
		GL_CALL(glDeleteBuffers(1, &rendererID));
	}

	/// <summary>
	/// <para>Binds the Vertex Buffer Object to GL_ARRAY_BUFFER</para>
	/// </summary>
	inline void Bind() {
		// Bind rendererID to the GL_ELEMENT_ARRAY_BUFFER constant
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	}
	/// <summary>
	/// <para>Binds 0 to GL_ARRAY_BUFFER, overriding the Vertex Buffer Object</para>
	/// </summary>
	inline void Unbind() {
		// Unbinds this buffer by binding 0 to GL_ELEMENT_ARRAY_BUFFER, effectively overriding rendererID
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
};