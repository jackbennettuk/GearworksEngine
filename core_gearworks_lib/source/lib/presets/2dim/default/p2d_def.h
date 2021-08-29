#ifndef P2D_DEFAULT_H
#define P2D_DEFAULT_H

// Include main header, but without the preset classes as they inherit from this class
#define GW_NOINCLUDE_PRESET_DEFS
#include <gearworks.h>
#undef GW_NOINCLUDE_PRESET_DEFS

class defshape {
private:
	// Vectors to cache transformations that have not yet been applied.
	// These get released in the private apply_transformations() function, which is run directly before glDrawElements().
	glm::vec3 active_translation;
	glm::vec3 active_scaling;
	glm::vec3 active_rotation;

	// This function applies any outstanding transformations to the shape.
	// It is only ever run in the base render() function, and so it can be private.
	// In order to publicly transform the primitive, use the translate(), scale(), and rotate() functions.
	void apply_transformations();
protected:
	// Pointer to renderer object
	gearworks::renderer *renderer_handle;

	// IBO and VAO
	gearworks::vertex_array_object vao;
	gearworks::index_buffer_object ibo;

	// Primitive type:- (for some functions in render())
	//	 0 = triangle
	//	 1 = rectangle
	unsigned int primitive_type;

	// Texture used for the primitive
	gearworks::texture_2d *texture_object;
public:
	/// <summary>
	/// The blending colour of the shape
	/// </summary>
	glm::vec4 colour;
	/// <summary>
	/// The path to the texture of the shape
	/// </summary>
	std::string texture;

	/// <summary>
	/// Default constructor. Note: to actually create the rectangle with vertex coordinates etc, use the create() function.
	/// </summary>
	defshape();
	// Destructor
	~defshape();

	/// <summary>
	/// Renders the shape via glDrawElements.
	/// </summary>
	void render();

	/// <summary>
	/// Translates, or moves, the shape by a given distance.
	/// </summary>
	/// <param name="transformation">The distance to move by in x, y, and z.</param>
	inline void translate(glm::vec3 transformation) { active_translation += transformation; }		// cache a translation to be applied in render()
	/// <summary>
	/// Rotates the shape by a given amount.
	/// </summary>
	/// <param name="scaling">The amount to rotate by in degrees.</param>
	/// <param name="axes">The axes to rotate around.</param>
	inline void rotate(glm::vec3 rotation) { active_rotation -= glm::radians(rotation); }			// cache a rotation amount to be applied in render() (subtracted to go clockwise by default)
	/// <summary>
	/// Scales the shape by a given amount.
	/// </summary>
	/// <param name="scaling">The amount to scale by.</param>
	inline void scale(glm::vec3 scaling) { active_scaling += scaling; }								// cache an amount to be scaled by in render()
};

#endif // header guard