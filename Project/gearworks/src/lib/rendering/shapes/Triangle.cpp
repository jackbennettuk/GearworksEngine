#include "Triangle.h"

Triangle::Triangle(glm::vec2 vertices[3]) {
	// Variable created to store the vertices as floats in their correct order as an array
	float vertFloats[6] = {};

	// Convert the vertices vectors to a standard float array so that the vbo constructor can use them
	vertFloats[0] = vertices[0].r; vertFloats[1] = vertices[0].g;
	vertFloats[2] = vertices[1].r; vertFloats[3] = vertices[1].g;
	vertFloats[4] = vertices[2].r; vertFloats[5] = vertices[2].g;

	// Clear out any old vbos and ibos
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	// Initialize vbo and ibo with the 'new' keyword, unfortunately
	vbo = new VertexBufferObject(6, vertFloats);		// VAO MUST be bound by this point!
	ibo = new IndexBufferObject(3, indices);
}
Triangle::~Triangle() {
	// Delete the VBO and set the dangling pointer to null
	vbo->Unbind();
	delete vbo;
	vbo = NULL;

	// Delete the IBO and set the dangling pointer to null
	ibo->Unbind();
	delete ibo;
	ibo = NULL;
}

void Triangle::Render() {
	// Bind the IBO
	ibo->Bind();

	// Draw the triangle
	GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
}