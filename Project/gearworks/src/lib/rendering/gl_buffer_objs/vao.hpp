#pragma once

#include "gwutility.h"

// Not a buffer object, but its stored in this folder anyway. :/
class VertexArrayObject {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int rendererID;
public:
	/// <summary>
	/// <para>The VertexArrayObject constructor that generates a VAO.</para>
	/// <para>The VAO is unbound by default - to bind it, call VertexArrayObject.Bind().</para>
	/// </summary>
	inline VertexArrayObject() {
		// Generate the vertex array
		GL_CALL(glGenVertexArrays(1, &rendererID));
		// Bind it by default
		GL_CALL(glBindVertexArray(rendererID));
	}
	inline ~VertexArrayObject() {
		// Delete the vertex array with rendererID
		GL_CALL(glDeleteVertexArrays(1, &rendererID));
	}

	/// <summary>
	/// <para>Binds this instance as the used vertex array</para>
	/// </summary>
	inline void Bind() {
		// Bind the vertex array
		GL_CALL(glBindVertexArray(rendererID));
	}
	/// <summary>
	/// <para>Binds 0 as the vertex array, overriding this instance</para>
	/// </summary>
	inline void Unbind() {
		// Unbind the vertex array by overriding it with 0
		GL_CALL(glBindVertexArray(0));
	}
};