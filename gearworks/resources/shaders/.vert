// The version in use if GLSL 3.3 core
#version 330 core

// l_Position: vec4 at location 0
layout(location = 0) in vec2 l_Position;
// l_TexCoord: vec2 at location 1
layout(location = 1) in vec2 l_TexCoord;

// Varying variable to pass to frag shader for texture coordinates
out vec2 v_TexCoord;
// Variable to output the position of each vertex in world space
out vec2 v_WorldPos;

// Model matrix for world coordinates
uniform mat4 u_ModelMat;

void main() {
	// Set the worldPos variable
	v_WorldPos = vec4(u_ModelMat * vec4(l_Position, 1.0, 1.0)).xy;

	// Set the position of the vertex, factoring the model matrix in
	gl_Position = u_ModelMat * vec4(l_Position, 1.0, 1.0);

	// Set the texture coordinates.
	// This can be run without texture coords being given: it will just default to { 0.0, 0.0 }
	v_TexCoord = l_TexCoord;
}