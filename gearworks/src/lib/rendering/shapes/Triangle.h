#pragma once

#include "gwrendering.h"

#include <depGL/glm/glm.hpp>

struct Triangle {
private:
	// Shader program
	unsigned int *mainShaderProgram;

	// The IBO and VBOs
	VertexBufferObject *texVBO, *posVBO;
	IndexBufferObject *ibo;

	// The default-used indices
	unsigned int indices[3] = { 0, 1, 2 };

	// The texture of the rectangle (if not given, it is not used)
	Texture2D *texture;
	// The colour of the rectangle as a vec4 (if not given, it is not used)
	glm::vec4 colour;
public:
	/// <summary>
	/// <para>Creates a Triangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A solid colour can be given to this overload.</para>
	/// </summary>
	/// <param name="vao">The vertex array object to attach the VBOs and IBO to.</param>
	/// <param name="program">The shader program on which to modify the colour uniform.</param>
	/// <param name="vertices">The coordinates of the 3 vertices in vec2s.</param>
	/// <param name="colour">The colour to render the triangle with (solid colour).</param>
	Triangle(VertexArrayObject *vao, unsigned int *program, glm::vec2 vertices[3], glm::vec4 _colour);
	/// <summary>
	/// <para>Creates a Triangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A solid colour can be given to this overload.</para>
	/// </summary>
	/// <param name="vao">The vertex array object to attach the VBOs and IBO to.</param>
	/// <param name="program">The shader program on which to modify the colour uniform.</param>
	/// <param name="vertices">The coordinates of the 3 vertices in vec2s.</param>
	/// <param name="colour">The colour to render the triangle with (solid colour).</param>
	Triangle(VertexArrayObject *vao, unsigned int *program, glm::vec2 vertices[3], std::string _texture);

	// Destructor
	~Triangle();

	/// <summary>
	/// <para>Renders the Triangle primitive via glDrawElements.</para>
	/// </summary>
	void Render();
};