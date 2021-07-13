#include "Rectangle.h"

// NOTE: The way the shader attributes are added to the vertex buffers is stupid, but other tested ways didn't seem to work.
	  // And I would know, by the way, because I spent THREE DAYS trying to figure it out. Why didn't it work????

// Texture constructor
Rectangle::Rectangle(VertexArrayObject *_vao, unsigned int *program, glm::vec2 position, glm::vec2 scale, std::string _texture)
	: colour(NULL), mainShaderProgram(program), vao(_vao) {
	// This float array is the data to be set for the position VBO (or 'posVBO') variable.
	// It stores the position data by converting the given vec2s to one unified standard float array.
	// These positions are in order: bottom_left, bottom_right, top_right, top_left.
	// NOTE: the origin of the rectangle is IN THE CENTER.
	float posVBO_Data[] = {
		position.r - (scale.r / 2), position.g - (scale.g / 2),
		position.r + (scale.r / 2), position.g - (scale.g / 2),
		position.r + (scale.r / 2), position.g + (scale.g / 2),
		position.r - (scale.r / 2), position.g + (scale.g / 2)
	};
	// This float array is the data for the texture VBO (or 'texVBO') variable.
	// It stores the texture coordinates in order: bottom_left, bottom_right, top_right, top_left.
	float texVBO_Data[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	// Create the position VBO
	posVBO = new VertexBufferObject(8, posVBO_Data);
	// Create the texture VBO
	texVBO = new VertexBufferObject(8, texVBO_Data);

	// Create the IBO
	ibo = new IndexBufferObject(6, indices);

	// Enable and define the position attribute for the position vertex buffer
	vao->AddVertexBufferAttrib(*posVBO, 0, 2, GL_FLOAT, GL_FALSE, 8, 0);
	// Enable and define the texture coordinate attribute for the texture vertex buffer
	vao->AddVertexBufferAttrib(*texVBO, 1, 2, GL_FLOAT, GL_FALSE, 8, 0);

	// Create the texture as a pointer
	texture = new Texture2D(_texture);
	texture->Unbind();

	// Make sure the texture is being used
	Shader::ModifyUniform1i(mainShaderProgram, "u_UsingTexture", 1);
	// Set uniform `u_Texture` to 0, as the texture has been bound to slot 0.
	Shader::ModifyUniform1i(mainShaderProgram, "u_Texture", 0);
}

// Colour constructor
Rectangle::Rectangle(VertexArrayObject *_vao, unsigned int *program, glm::vec2 position, glm::vec2 scale, glm::vec4 _colour)
	: texture(nullptr), colour(_colour), texVBO(nullptr), mainShaderProgram(program), vao(_vao) {
	// This float array is the data to be set for the position VBO (or 'posVBO') variable.
	// It stores the position data by converting the given vec2s to one unified standard float array.
	// These positions are in order: bottom_left, bottom_right, top_right, top_left.
	// NOTE: the origin of the rectangle is IN THE CENTER.
	float posVBO_Data[] = {
		position.r - (scale.r / 2), position.g - (scale.g / 2),
		position.r + (scale.r / 2), position.g - (scale.g / 2),
		position.r + (scale.r / 2), position.g + (scale.g / 2),
		position.r - (scale.r / 2), position.g + (scale.g / 2)
	};

	// Create the position VBO
	posVBO = new VertexBufferObject(8, posVBO_Data);

	// Create the IBO
	ibo = new IndexBufferObject(6, indices);

	// Enable and define the position attribute for the position vertex buffer
	vao->AddVertexBufferAttrib(*posVBO, 0, 2, GL_FLOAT, GL_FALSE, 8, 0);

	// Make sure any textures are NOT being used
	Shader::ModifyUniform1i(mainShaderProgram, "u_UsingTexture", 0);
	// Apply the colour to the rectangle by modifying the appropriate uniform variable
	Shader::ModifyUniform4fv(mainShaderProgram, "u_Colour", colour);
}

Rectangle::~Rectangle() {
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

void Rectangle::Render() {
	// Bind VAO and IBO
	vao->Bind();
	ibo->Bind();

	// Bind the texture
	if (texture) texture->Bind();

	// Draw the rectangle
	GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}