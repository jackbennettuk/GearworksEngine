#include "Rectangle.h"

Rectangle::Rectangle(glm::vec2 position, glm::vec2 scale) {
	// Variable created to store the vertices as floats in their correct order as an array
	float vertFloats[8] = {};

	// Convert the vertices vectors to a standard float array so that the vbo constructor can use them
	vertFloats[0] = position.r; vertFloats[1] = position.g;
	vertFloats[2] = position.r; vertFloats[3] = position.g - scale.g;
	vertFloats[4] = position.r + scale.r; vertFloats[5] = position.g - scale.g;
	vertFloats[6] = position.r + scale.r; vertFloats[7] = position.g;

	// Clear out any old vbos and ibos
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	// Initialize vbo and ibo with the 'new' keyword, unfortunately
	vbo = new VertexBufferObject(8, vertFloats);		// VAO MUST be bound by this point!
	ibo = new IndexBufferObject(6, indices);
}
Rectangle::~Rectangle() {
	// Delete the VBO and set the dangling pointer to null
	vbo->Unbind();
	delete vbo;
	vbo = NULL;

	// Delete the IBO and set the dangling pointer to null
	ibo->Unbind();
	delete ibo;
	ibo = NULL;
}

void Rectangle::Render() {
	// Bind the IBO
	ibo->Bind();

	// Draw the triangle
	GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}