#version 330 core
// Vertex shader source code

layout(location = 0) in vec4 l_Position;

void main() {
	gl_Position = l_Position;
}