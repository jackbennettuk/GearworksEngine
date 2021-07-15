#pragma once

#include <depGL/glm/glm.hpp>

#include "gwassets.h"
#include "gwrendering.h"

struct Rectangle {
private:
	// Renderer pointer
	Renderer *renderer;

	// The IBO and VBOs
	VertexBufferObject *texVBO, *posVBO;
	IndexBufferObject *ibo;
	
	// Pointer to the VAO
	VertexArrayObject *vao;

	// The default-used indices
	unsigned int indices[6] = { 0, 1, 2, 0, 3, 2 };
public:
	// The texture of the rectangle (if not given, it is not used)
	Texture2D *texture;
	// The colour of the rectangle as a vec4 (if not given, it is not used)
	glm::vec4 colour;
	// Translation variable that is set to be the default positions given in the constructor/s
	glm::vec2 translation;

	/// <summary>
	/// <para>Creates a Rectangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A solid colour can be given to this overload.</para>
	/// </summary>
	/// <param name="vao">The vertex array object to attach the VBOs and IBO to.</param>
	/// <param name="program">The shader program on which to modify the colour uniform.</param>
	/// <param name="position">The STARTING(!) position coordinate of the rectangle primitive. (To change the position at runtime, change the translation variable.)</param>
	/// <param name="scale">The scale values of the rectangle primitive.</param>
	/// <param name="colour">The colour to render the rectangle with (solid colour).</param>
	Rectangle(VertexArrayObject *vao, Renderer *_renderer, glm::vec2 _position, glm::vec2 scale, glm::vec4 _colour);
	/// <summary>
	/// <para>Creates a Rectangle struct and its appropriate VBOs and IBO.</para>
	/// <para>A solid colour can be given to this overload.</para>
	/// </summary>
	/// <param name="vao">The vertex array object to attach the VBOs and IBO to.</param>
	/// <param name="program">The shader program on which to modify the colour uniform.</param>
	/// <param name="position">The STARTING(!) position coordinate of the rectangle primitive. (To change the position at runtime, change the translation variable.)</param>
	/// <param name="scale">The scale values of the rectangle primitive.</param>
	/// <param name="colour">The colour to render the rectangle with (solid colour).</param>
	Rectangle(VertexArrayObject *vao, Renderer *_renderer, glm::vec2 _position, glm::vec2 scale, std::string _texture);

	// Destructor
	~Rectangle();

	/// <summary>
	/// <para>Renders the Rectangle primitive via glDrawElements.</para>
	/// </summary>
	void Render();
};