#ifndef P2D_TRIANGLE_H
#define P2D_TRIANGLE_H

#include "../.default/p2d_def.h"

class gearworks::triangle : public defshape {
private:
	// The default-used indices
	unsigned int indices[3] = { 0, 1, 2 };
public:
	// Use the default shape constructor
	using defshape::defshape;
	/// <summary>
	/// Creates a Triangle struct and its appropriate VBOs and IBO.
	/// If you are creating a scalene triangle, it is recommended that all your vertices to be at or below 1, so scaling is more intuitive. This isn't mandated, however.
	/// </summary>
	/// <param name="renderer">The renderer that the triangle will be 'bound' to.</param>
	/// <param name="type">The type of triangle, e.g. GEAR_EQUILATERAL_TRI represents an equilateral triangle.</param>
	/// <param name="texture_path">The texture to use for the triangle.</param>
	/// <param name="position">The starting position of the triangle. vec3(0) is the center of the world (keep in mind that zNear is 0.5)</param>
	/// <param name="scale">The starting size of the triangle in 2D space.</param>
	/// <param name="rotation">The starting rotation of the triangle.</param>
	/// <param name="vertices">The starting vertex coordinates to use. Leave this as nullptr if you are creating an equilateral triangle.</param>
	/// <param name="blend_colour">The colour to render the triangle. Default is white.</param>
	/// <param name="blend_opacity">The opacity of the shape.</param>
	void create(gearworks::renderer *renderer, unsigned int type, string texture_path, vec3 position = vec3(0), vec2 scale = vec2(1), vec3 rotation = vec3(0), vec3 vertices[3] = nullptr, vec3 blend_colour = vec3(255, 255, 255), float blend_opacity = 255);
};

#endif // header guard