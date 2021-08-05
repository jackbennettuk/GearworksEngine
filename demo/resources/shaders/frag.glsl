#version 330 core

// l_Colour: vec4 at location 0
layout(location = 0) out vec4 l_Colour;

// Texture coordinates, passed here by the vert shader
in vec2 v_TexCoord;

// Texture
uniform sampler2D u_Texture;
// Colour
uniform vec4 u_Colour;

void main() {
	// Get the colour of the pixel with the texture coordinates
	vec4 texColour = texture(u_Texture, v_TexCoord) * u_Colour;

	// Apply the colour
	l_Colour = texColour;
}