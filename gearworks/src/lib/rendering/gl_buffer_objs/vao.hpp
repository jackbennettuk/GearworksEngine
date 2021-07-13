#pragma once

#include "gwutility.h"

class VertexArrayObject {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int rendererID = 0;
public:
	// rendererID getter
	inline unsigned int GetRendererID() { return rendererID; }

	/// <summary>
	/// <para>The default constructor for the VAO. IMPORTANT: This constructor does NOT generate a VAO! To do that, you must call VertexArrayObject.Initialize()!</para>
	/// </summary>
	inline VertexArrayObject() {}
	inline ~VertexArrayObject() {
		// Delete the vertex array with rendererID
		GL_CALL(glDeleteVertexArrays(1, &rendererID));
	}

	/// <summary>
	/// <para>Initializes the VAO. This method has been put in place so that it can be called after Glad is loaded, instead of in the default constructor.</para>
	/// </summary>
	inline void Initialize() {
		// Generate the vertex array
		GL_CALL(glGenVertexArrays(1, &rendererID));
	}

	/// <summary>
	/// <para>Binds the vertex array object</para>
	/// </summary>
	inline void Bind() {
		// Binds the vertex array to rendererID
		GL_CALL(glBindVertexArray(rendererID));
	}
	/// <summary>
	/// <para>Unbinds the vertex array object, overriding it with '0'.</para>
	/// </summary>
	inline void Unbind() {
		// Binds the vertex array to 0
		GL_CALL(glBindVertexArray(0));
	}

	/// <summary>
	/// <para>Adds a vertexattrib to a given vertex buffer with given parameters rather than a pre-made Vertex Buffer Layout.</para>
	/// <para>For parameter information please see the official documentation for the glVertexAttribPointer() OpenGL method.</para>
	/// </summary>
	inline void AddVertexBufferAttrib(VertexBufferObject &vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
		// Bind this VAO
		Bind();
		// Bind the given VBO first
		vbo.Bind();

		GL_CALL(glEnableVertexAttribArray(index));
		GL_CALL(glVertexAttribPointer(index, size, type, normalized, stride, pointer));

		// Unbind the VAO
		Unbind();
		// Unbind the VBO and delete it via its deconstructor
		vbo.Unbind();
	}
};