#ifndef P2D_TRIANGLE_H
#define P2D_TRIANGLE_H

#include "../default/p2d_def.h"

class gearworks::triangle : public defshape {
private:
	// The default-used indices
	unsigned int indices[3] = { 0, 1, 2 };
public:
	// Use the default shape constructor
	using defshape::defshape;
	/// <summary>
	/// Creates a Rectangle struct and its appropriate VBOs and IBO.
	/// A blend colour and a texture may be given.
	/// </summary>
	/// <param name="renderer">The renderer that the triangle will be 'bound' to.</param>
	/// <param name="vertices">The starting vertex coordinates to use.</param>
	/// <param name="texture_path">The texture to use for the rectangle.</param>
	/// <param name="blend_colour">The colour to render the rectangle. Default is white.</param>
	void create(gearworks::renderer *renderer, vec3 vertices[3], string texture_path, vec3 blend_colour = vec3(255, 255, 255), float blend_opacity = 255);
};

#endif // header guard