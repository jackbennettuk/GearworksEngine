#pragma once

#include "gwrendering.h"

#include <depGL/glm/glm.hpp>

struct Rectangle {
private:
	// The rectangle's vertex buffer object
	VertexBufferObject *vbo;
	// The rectangle's index buffer object
	IndexBufferObject *ibo;

	// The default-used indices
	unsigned int indices[6] = { 0, 1, 2, 0, 3, 2 };
public:
	/// <summary>
	/// <para>Creates a Rectangle struct and its appropriate VBO and IBO.</para>
	/// <para>Make sure to call this AFTER creating and binding a VAO!</para>
	/// </summary>
	/// <param name="position">The position coordinate of the rectangle primitive.</param>
	/// <param name="scale">The scale values of the rectangle primitive.</param>
	Rectangle(glm::vec2 position, glm::vec2 scale);
	~Rectangle();

	/// <summary>
	/// <para>Renders the Rectangle primitive via glDrawElements.</para>
	/// </summary>
	void Render();
};