#ifndef P2D_RECTANGLE_H
#define P2D_RECTANGLE_H

#include "../.default/p2d_def.h"

class gearworks::rectangle : public defshape {
private:
	// The default-used indices
	unsigned int indices[6] = { 0, 1, 2, 0, 3, 2 };
public:
	// Use the default shape constructor
	using defshape::defshape;

	/// <summary>
	/// Creates a Rectangle struct and its appropriate VBOs and IBO.
	/// A blend colour and a texture may be given.
	/// </summary>
	/// <param name="renderer">The renderer that the rectangle will be 'bound' to.</param>
	/// <param name="texture_path">The texture to use for the rectangle.</param>
	/// <param name="position">The starting position coordinate of the rectangle primitive, with 0 as its center.</param>
	/// <param name="scale">The scale values of the rectangle primitive.</param>
	/// <param name="rotation">The starting rotation of the rectangle.</param>
	/// <param name="blend_colour">The colour to render the rectangle. Default is white.</param>
	/// <param name="blend_opacity">The opacity of the shape.</param>
	void create(gearworks::renderer *renderer, string texture_path, vec3 position = vec3(0), vec2 scale = vec2(1), vec3 rotation = vec3(0), vec3 blend_colour = vec3(255, 255, 255), float blend_opacity = 255);
};

#endif // header guard