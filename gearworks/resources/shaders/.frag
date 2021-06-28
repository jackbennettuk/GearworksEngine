#version 330 core
// Fragment shader source code

layout(location = 0) out vec4 l_Colour;

uniform vec3 u_Colour;

void main() {
	// TODO: use u_Colour here instead of a hard-coded white colour
	l_Colour = vec4(1.0, 1.0, 1.0, 1.0);
}