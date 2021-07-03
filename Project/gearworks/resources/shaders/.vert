#version 330 core
// Vertex shader source code

layout(location = 0) in vec4 l_Position;

uniform mat4 u_ModelViewProj;

void main() {
	gl_Position = u_ModelViewProj * l_Position;
}