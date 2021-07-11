#pragma once

#include "gwutility.h"

#include <depGL/Glad/glad.h>

#include <vector>

struct VertexBufferLayoutElement {
	// Used for the glVertexAttribPointer() parameter `type`. Given as a GL_TYPE enum.
	unsigned int glType;
	// Used for the glVertexAttribPointer() parameter `count`.
	unsigned int count;
	// Used for the glVertexAttribPointer() parameter `normalized`.
	unsigned int normalized;
};

class VertexBufferLayout {
private:
	// A vector to store all used VertexBufferLayoutElements. It is added to via the Push method.
	std::vector<VertexBufferLayoutElement> elements;

	// The stride of the vertex buffer layout.
	unsigned int stride;
public:
	/// <summary>
	/// <para>Constructor for the VertexBufferLayout class</para>
	/// </summary>
	inline VertexBufferLayout() 
		: stride(0) {}

	// The declaration of the template method "Push" is here. It simply adds - or 'pushes' - a new
	// element to the end of the 'elements' vector variable.
	template<typename T>
	inline void Push(unsigned int count) {
		static_assert(false);
	}
	/// <summary>
	/// <para>Adds an element of type FLOAT to the end of the vertex buffer layout.</para>
	/// </summary>
	/// <param name="count">The count for use in the `glVertexAttribPointer()` method.</param>
	template<>
	inline void Push<float>(unsigned int count) {
		// Add a new element with the given count and type GL_FLOAT.
		// Currently, `normalized` is hard-coded to false.
		// TODO: change this so that `normalized` is not hard-coded in future.
		elements.push_back({
			GL_FLOAT,
			count,
			GL_FALSE
		});

		// Add the size of a float to the stride
		stride += count * sizeof(util::GetSizeOfType(GL_FLOAT));
	}
	/// <summary>
	/// <para>Adds an element of type UNSIGNED INT to the end of the vertex buffer layout.</para>
	/// </summary>
	/// <param name="count">The count for use in the `glVertexAttribPointer()` method.</param>
	template<>
	inline void Push<unsigned int>(unsigned int count) {
		// Add a new element with the given count and type GL_UNSIGNED_INT.
		// Currently, `normalized` is hard-coded to false.
		// TODO: change this so that `normalized` is not hard-coded in future.
		elements.push_back({
			GL_UNSIGNED_INT,
			count,
			GL_FALSE
		});

		// Add the size of an unsigned integer to the stride
		stride += count * sizeof(util::GetSizeOfType(GL_UNSIGNED_INT));
	}
	/// <summary>
	/// <para>Adds an element of type UNSIGNED CHAR to the end of the vertex buffer layout.</para>
	/// </summary>
	/// <param name="count">The count for use in the `glVertexAttribPointer()` method.</param>
	template<>
	inline void Push<unsigned char>(unsigned int count) {
		// Add a new element with the given count and type GL_UNSIGNED_BYTE.
		// Currently, `normalized` is hard-coded to true.
		// TODO: change this so that `normalized` is not hard-coded in future.
		elements.push_back({
			GL_UNSIGNED_BYTE,
			count,
			GL_TRUE
		});

		// Add the size of an unsigned char, or unsigned byte, to the stride
		stride += count * sizeof(util::GetSizeOfType(GL_UNSIGNED_BYTE));
	}

	inline std::vector<VertexBufferLayoutElement> GetElementVector() const { return elements; }
	inline unsigned int GetStride() const { return stride; }
};
