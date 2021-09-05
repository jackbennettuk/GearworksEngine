#ifndef P3D_CUBOID_H
#define P3D_CUBOID_H

#include "../.default/p3d_def.h"

class gearworks::cuboid : public defshape3d {
private:
	// The default-used indices
	unsigned int indices[36] = {
		// Front face
		0, 3, 2,
		2, 1, 0,
		// Bottom face
		4, 5, 6,
		6, 7 ,4,
		// Left side face
		11, 8, 9,
		9, 10, 11,
		// Right side face
		12, 13, 14,
		14, 15, 12,
		// Bottom face
		16, 17, 18,
		18, 19, 16,
		// Top face
		20, 21, 22,
		22, 23, 20
	};
public:
	// Use the default shape constructor
	using defshape3d::defshape3d;

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
	void create(gearworks::renderer *renderer, string texture_path, vec3 position = vec3(0), vec3 scale = vec3(1), vec3 rotation = vec3(0), vec3 blend_colour = vec3(255, 255, 255), float blend_opacity = 255);
};

#endif // header guard