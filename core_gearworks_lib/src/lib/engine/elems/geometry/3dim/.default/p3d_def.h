#ifndef P3D_DEFAULT_H
#define P3D_DEFAULT_H

// Include main header, but without the preset classes as they inherit from this class
#define GW_NOINCLUDE_ELEM_DEFS
#include <gearworks.h>
#undef GW_NOINCLUDE_ELEM_DEFS

#include "../../../.default/e_default.h"

class defshape3d : public elem_default {
protected:
	// Pointer to renderer object
	gearworks::renderer *renderer_handle;

	// IBO and VAO
	gearworks::vertex_array_object vao;
	gearworks::index_buffer_object ibo;

	// Shape type:- (for some functions in render())
	// | 0 = cube
	unsigned int shape_type;

	// Texture used for the shape faces
	gearworks::texture_2d *texture_object;
public:
	/// <summary>
	/// Default constructor. Note: to actually create the shape with vertex coordinates etc, use the create() function.
	/// </summary>
	defshape3d();
	// Destructor
	~defshape3d();

	/// <summary>
	/// Renders the shape via glDrawElements.
	/// </summary>
	void render();
};

#endif // header guard