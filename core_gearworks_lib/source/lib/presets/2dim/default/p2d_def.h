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

#pragma region Transformation methods
	/// <summary>
	/// Translates, or moves, the shape by a given distance.
	/// </summary>
	/// <param name="x">Value to move on the X axis.</param>
	/// <param name="y">Value to move on the Y axis.</param>
	/// <param name="z">Value to move on the Z axis.</param>
	inline void translate(float x, float y, float z) { active_translation += glm::vec3(x, y, z); }
	/// <summary>
	/// Translates, or moves, the shape by a given distance.
	/// </summary>
	/// <param name="vect">Value to move on the 3 axes stored as a glm::vec3.</param>
	inline void translate(glm::vec3 vect) { active_translation += vect; }

	/// <summary>
	/// Rotates the shape by a given amount.
	/// </summary>
	/// <param name="x">Value to rotate on the X axis.</param>
	/// <param name="y">Value to rotate on the Y axis.</param>
	/// <param name="z">Value to rotate on the Z axis.</param>
	inline void rotate(float x, float y, float z) { active_rotation -= glm::radians(glm::vec3(x, y, z)); } // subtracted to rotate clockwise by default
	/// <summary>
	/// Rotates the shape by a given amount.
	/// </summary>
	/// <param name="vect">Value to rotate the shape on the 3 axes stored as a glm::vec3.</param>
	inline void rotate(glm::vec3 vect) { active_rotation -= glm::radians(vect); } // subtracted to rotate clockwise by default

	/// <summary>
	/// Scales the shape by a given amount.
	/// </summary>
	/// <param name="x">Value to scale on the X axis.</param>
	/// <param name="y">Value to scale on the Y axis.</param>
	/// <param name="z">Value to scale on the Z axis.</param>
	inline void scale(float x, float y, float z) { active_scaling += glm::vec3(x, y, z); }
	/// <summary>
	/// Scales the shape by a given amount.
	/// </summary>
	/// <param name="vect">Value to scale by on the 3 axes stored as a glm::vec3.</param>
	inline void scale(glm::vec3 vect) { active_scaling += vect; }
	/// <summary>
	/// Scales the shape by a given amount.
	/// </summary>
	/// <param name="val">Value to scale on all axes.</param>
	inline void scale(float val) { active_scaling += glm::vec3(val); }
#pragma endregion
};

#endif // header guard