#pragma once

#include "gwrendering.h"

#include <depGL/glm/glm.hpp>

struct Triangle {
private:
	// The triangle's vertex buffer object
	VertexBufferObject *vbo;
	// The triangle's index buffer object
	IndexBufferObject *ibo;

	// The default-used indices
	unsigned int indices[3] = { 0, 1, 2 };
public:
	/// <summary>
	/// <para>Creates a Triangle struct and its appropriate VBO and IBO.</para>
	/// <para>Make sure to call this AFTER creating and binding a VAO!</para>
	/// </summary>
	/// <param name="vertices">The array of vertex coordinates, given as glm::vec2s.</param>
	Triangle(glm::vec2 vertices[3]);
	~Triangle();

	/// <summary>
	/// <para>Renders the Triangle primitive via glDrawElements.</para>
	/// </summary>
	void Render();
};