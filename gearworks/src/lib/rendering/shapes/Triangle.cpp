#include "Triangle.h"

// Texture constructor
Triangle::Triangle(VertexArrayObject *vao, unsigned int *program, glm::vec2 vertices[3], std::string _texture)
	: colour(NULL), mainShaderProgram(program) {
	// This float array is the data to be set for the position VBO (or 'posVBO') variable.
	// It stores the positions of each of the vertices.
	float posVBO_Data[] = {
		vertices[0].r, vertices[0].g,
		vertices[1].r, vertices[1].g,
		vertices[2].r, vertices[2].g
	};
	// This float array is the data for the texture VBO (or 'texVBO') variable.
	float texVBO_Data[] = {
		0.0f, 0.0f,
		0.5f, 1.0f,
		1.0f, 0.0f
	};

	// Create the position VBO
	posVBO = new VertexBufferObject(6, posVBO_Data);
	// Create the texture VBO
	texVBO = new VertexBufferObject(6, texVBO_Data);

	// Create the IBO
	ibo = new IndexBufferObject(3, indices);

	// Create the texture as a pointer
	texture = new Texture2D(_texture);
	texture->Unbind();

	// Make sure the texture is being used
	Shader::ModifyUniform1i(mainShaderProgram, "u_UsingTexture", 1);
	// Set uniform `u_Texture` to 0, as the texture has been bound to slot 0.
	Shader::ModifyUniform1i(mainShaderProgram, "u_Texture", 0);
}

// Colour constructor
Triangle::Triangle(VertexArrayObject *vao, unsigned int *program, glm::vec2 vertices[3], glm::vec4 _colour)
	: texture(nullptr), colour(_colour), texVBO(nullptr), mainShaderProgram(program) {
	// This float array is the data to be set for the position VBO (or 'posVBO') variable.
	// It stores the positions of each of the vertices.
	float posVBO_Data[] = {
		vertices[0].r, vertices[0].g,
		vertices[1].r, vertices[1].g,
		vertices[2].r, vertices[2].g
	};

	// Clear out any old vbos and ibos
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	// Create the position VBO
	posVBO = new VertexBufferObject(6, posVBO_Data);

	// Create the IBO
	ibo = new IndexBufferObject(3, indices);

	// Enable and define the position attribute for the position vertex buffer
	vao->AddVertexBufferAttrib(*posVBO, 0, 2, GL_FLOAT, GL_FALSE, 8, 0);

	// Make sure any textures are NOT being used
	Shader::ModifyUniform1i(mainShaderProgram, "u_UsingTexture", 0);
	// Apply the colour to the rectangle by modifying the appropriate uniform variable
	Shader::ModifyUniform4fv(mainShaderProgram, "u_Colour", colour);
}

Triangle::~Triangle() {
	// Unbind the IBO and VBOs
	ibo->Unbind();
	posVBO->Unbind();
	if (texVBO) texVBO->Unbind();

	// Unbind the texture
	if (texture) texture->Unbind();

	// Delete all pointer variables here so the 'new' keyword doesn't ruin my program.
	DELETE_PTR(posVBO);
	DELETE_PTR(texVBO);
	DELETE_PTR(ibo);
	DELETE_PTR(texture);
}

void Triangle::Render() {
	// Bind the IBO
	ibo->Bind();
	// Bind the texture if it was given
	if (texture) texture->Bind();

	// Draw the triangle
	GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
}