#ifndef P2D_DEFAULT_H
#define P2D_DEFAULT_H

// Include main header, but without the preset classes as they inherit from this class
#define GW_NOINCLUDE_ELEM_DEFS
#include <gearworks.h>
#undef GW_NOINCLUDE_ELEM_DEFS

#include "../../../.default/e_default.h"

class defshape : public elem_default {
protected:
	// Pointer to renderer object
	gearworks::renderer *renderer_handle;

	// IBO and VAO
	gearworks::vertex_array_object vao;
	gearworks::index_buffer_object ibo;

	// Primitive type:- (for some functions in render())
	// | 0 = triangle
	// | 1 = rectangle
	unsigned int primitive_type;

	// Texture used for the primitive
	gearworks::texture_2d *texture_object;
public:
	/// <summary>
	/// Default constructor. Note: to actually create the shape with vertex coordinates etc, use the create() function.
	/// </summary>
	defshape();
	// Destructor
	~defshape();

	/// <summary>
	/// Renders the shape via glDrawElements.
	/// </summary>
	void render();
};

#endif // header guard