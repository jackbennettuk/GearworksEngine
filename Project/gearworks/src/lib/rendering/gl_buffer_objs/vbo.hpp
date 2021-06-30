#pragma once

#include "gwutility.h"

#include <depGL/Glad/glad.h>

class VertexBufferObject {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int rendererID;
public:
	/// <summary>
	/// <para>The VertexBufferObject constructor that generates a VBO with the given size and data</para>
	/// <para>The VBO is unbound by default - to bind it, call VertexBufferObject.Bind().</para>
	/// </summary>
	/// <param name="count">The amount of items in the array "data"</param>
	/// <param name="data">The array of positions, given as floats, for the VBO</param>
	inline VertexBufferObject(unsigned int count, float data[]) {
		// Initialize rendererID as a newly-generated buffer object
		GL_CALL(glGenBuffers(1, &rendererID));
		// Bind the buffer so that the following functions work
		Bind();

		// Set the data of the VBO based on count and data
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW));

		// Enable the position attribute by enabling the attribute at index 0 (position is at index 0)
		GL_CALL(glEnableVertexAttribArray(0));
		// Specify how to read the position attribute (read it as positions in 2D space)
		GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

		// Initially unbind the buffer so that it is bound through the VAO at render-time
		Unbind();
	}
	inline ~VertexBufferObject() {
		// Delete the buffer with rendererID
		GL_CALL(glDeleteBuffers(1, &rendererID));
	}

	/// <summary>
	/// <para>Binds the Vertex Buffer Object to GL_ARRAY_BUFFER</para>
	/// </summary>
	inline void Bind() {
		// Bind rendererID to the GL_ARRAY_BUFFER constant
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	}
	/// <summary>
	/// <para>Binds 0 to GL_ARRAY_BUFFER, overriding the Vertex Buffer Object</para>
	/// </summary>
	inline void Unbind() {
		// Unbinds this buffer by binding 0 to GL_ARRAY_BUFFER, effectively overriding rendererID
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
};