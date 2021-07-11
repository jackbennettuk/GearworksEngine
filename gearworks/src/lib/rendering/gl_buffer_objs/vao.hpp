#pragma once

#include "gwutility.h"

class VertexArrayObject {
private:
	// The ID that is referred in GL commands such as glGenBuffers
	unsigned int rendererID = 0;
public:
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
	/// <para>Adds a vertex buffer with a given Vertex Buffer Layout.</para>
	/// </summary>
	/// <param name="vbo">The vertex buffer object to add.</param>
	/// <param name="layout">The layout of the vertex buffer object to initialize with.</param>
	void AddVertexBuffer(VertexBufferObject &vbo, VertexBufferLayout &layout) {
		// Bind this VAO
		Bind();
		// Bind the given VBO first
		vbo.Bind();

		// Gets the vector of elements from the given layout
		const auto &elements = layout.GetElementVector();
		// Store the offset of each element which will then be increased in the following for loop
		unsigned int offset = 0;

		for (unsigned int i = 0; i < elements.size(); i++) {
			// Iterate through elements, storing each one in variable 'e' - not 'element' so as to not cause confusion between element and elements variables.
			const auto &e = elements[i];

			// Enables the attribute at position 'i' so each element is enabled in ascending order of attributes in the VBO
			//GL_CALL(glEnableVertexAttribArray(i));
			// Gives a vertex attribute pointer with the given parameters
			//GL_CALL(glVertexAttribPointer(i, e.count, e.glType, e.normalized, layout.GetStride(), (const void *)offset));

			// Add to the offset with count multiplied by the size of the element, or `e`
			offset += e.count * util::GetSizeOfType(e.glType);
		}

		// Unbind the VAO
		Unbind();
	}

	/// <summary>
	/// <para>Adds a vertexattrib to a given vertex buffer with given parameters rather than a pre-made Vertex Buffer Layout.</para>
	/// <para>For parameter information please see the official documentation for the glVertexAttribPointer() OpenGL method.</para>
	/// </summary>
	void AddVertexBufferAttrib(VertexBufferObject &vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
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