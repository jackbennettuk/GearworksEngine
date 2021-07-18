#version 330 core

// l_Colour: vec4 at location 0
layout(location = 0) out vec4 l_Colour;

// Texture coordinates, passed here by the vert shader
in vec2 v_TexCoord;

// Boolean to switch between texture and colour usage
uniform int u_UsingTexture;
// Texture if it is being used
uniform sampler2D u_Texture;
// Colour if it is being used
uniform vec4 u_Colour;

void main() {
	// Get the colour of the pixel with the texture coordinates
	vec4 texColour = texture(u_Texture, v_TexCoord);
	
	// Set the colour of the pixel accordingly
	if (u_UsingTexture == 1) {
		l_Colour = texColour;
	} else {
		l_Colour = u_Colour;
	}
}