#pragma once

#include <depGL/Glad/glad.h>

class VertexBufferObject {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int rendererID;
public:
	/// <summary>
	/// The VertexBufferObject constructor that generates a VBO with the given size and data
	/// </summary>
	/// <param name="count">The amount of items in the array "data"</param>
	/// <param name="data">The array of positions, given as floats, for the VBO</param>
	inline VertexBufferObject(unsigned int count, float data[]) {
		// Initialize rendererID as a newly-generated buffer object
		glGenBuffers(1, &rendererID);
		// Bind rendererID to the GL_ARRAY_BUFFER constant
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);

		// Set the data of the VBO based on count and data
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);

		// Enable the position attribute by enabling the attribute at index 0 (position is at index 0)
		glEnableVertexAttribArray(0);
		// Specify how to read the position attribute (read it as positions in 2D space)
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	}
	inline ~VertexBufferObject() {
		// Delete the buffer with rendererID
		glDeleteBuffers(1, &rendererID);
	}

	/// <summary>
	/// Binds the Vertex Buffer Object to GL_ARRAY_BUFFER
	/// </summary>
	inline void Bind() {
		// Bind rendererID to the GL_ARRAY_BUFFER constant
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}
	/// <summary>
	/// Binds 0 to GL_ARRAY_BUFFER, overriding the Vertex Buffer Object
	/// </summary>
	inline void Bind() {
		// Unbinds this buffer by binding 0 to GL_ARRAY_BUFFER, effectively overriding rendererID
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};