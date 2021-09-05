#ifndef E_DEFAULT_H
#define E_DEFAULT_H

#define GW_NOINCLUDE_ELEM_DEFS
#include <gearworks.h>
#undef GW_NOINCLUDE_ELEM_DEFS

class elem_default {
private:
	// A struct that holds properties of the shape.
	struct shape_properties_struct {
		// Constructor for a shape_properties_struct object.
		shape_properties_struct();

		/// <summary>
		/// The blending colour of the shape.
		/// </summary>
		vec3 colour;
		/// <summary>
		/// The opacity of the shape.
		/// </summary>
		float opacity;

		/// <summary>
		/// The path to the texture of the shape.
		/// </summary>
		string texture;

		/// <summary>
		/// Basic transformation value of the shape.
		/// </summary>
		vec3 position, rotation, scale;
	};
protected:
	// This function applies any outstanding transformations to the shape.
	// It is only ever run in the base render() function, and so it can be private.
	// In order to publicly transform the primitive, use the translate(), scale(), and rotate() functions.
	virtual void apply_transformations(gearworks::renderer *renderer);
public:
	/// <summary>
	/// The properties of the shape, like colour, texture, etc.
	/// </summary>
	shape_properties_struct properties;

#pragma region Transformation methods
	/// <summary>
	/// Translates, or moves, the shape by a given distance.
	/// </summary>
	/// <param name="x">Value to move on the X axis.</param>
	/// <param name="y">Value to move on the Y axis.</param>
	/// <param name="z">Value to move on the Z axis.</param>
	inline void translate(float x, float y, float z) { properties.position += vec3(x, y, z); }
	/// <summary>
	/// Translates, or moves, the shape by a given distance.
	/// </summary>
	/// <param name="vect">Value to move on the 3 axes stored as a glm::vec3.</param>
	inline void translate(vec3 vect) { properties.position += vect; }

	/// <summary>
	/// Rotates the shape by a given amount.
	/// </summary>
	/// <param name="x">Value to rotate on the X axis.</param>
	/// <param name="y">Value to rotate on the Y axis.</param>
	/// <param name="z">Value to rotate on the Z axis.</param>
	inline void rotate(float x, float y, float z) { properties.rotation += vec3(x, y, z); } // subtracted to rotate clockwise by default
	/// <summary>
	/// Rotates the shape by a given amount.
	/// </summary>
	/// <param name="vect">Value to rotate the shape on the 3 axes stored as a glm::vec3.</param>
	inline void rotate(vec3 vect) { properties.rotation += vect; } // subtracted to rotate clockwise by default

	/// <summary>
	/// Scales the shape by a given amount.
	/// </summary>
	/// <param name="x">Value to scale on the X axis.</param>
	/// <param name="y">Value to scale on the Y axis.</param>
	/// <param name="z">Value to scale on the Z axis.</param>
	inline void scale(float x, float y, float z) { properties.scale += vec3(x, y, z); }
	/// <summary>
	/// Scales the shape by a given amount.
	/// </summary>
	/// <param name="vect">Value to scale by on the 3 axes stored as a glm::vec3.</param>
	inline void scale(vec3 vect) { properties.scale += vect; }
	/// <summary>
	/// Scales the shape by a given amount.
	/// </summary>
	/// <param name="val">Value to scale on all axes.</param>
	inline void scale(float val) { properties.scale += vec3(val); }
#pragma endregion
};

#endif