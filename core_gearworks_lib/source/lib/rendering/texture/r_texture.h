#ifndef R_TEXTURE_H
#define R_TEXTURE_H

#include <gearworks.h>

class gearworks::texture_2d {
private:
	// Renderer ID
	unsigned int renderer_id;
	// Path to the image file
	std::string path;
	// Texture properties - width, height, and bits-per-pixel.
	int width, height, bits_per_pixel;
public:
	/// <summary>
	/// Creates an empty texture object.
	/// </summary>
	texture_2d();

	/// <summary>
	/// Load a given image into the texture.
	/// </summary>
	/// <param name="_path">The path of the texture as a string.</param>
	void load(std::string _path);

	/// <summary>
	/// Binds the texture at a (optional) given slot.
	/// </summary>
	/// <param name="slot">(Optional) the texture slot to bind the texture to.</param>
	void bind(unsigned int slot = 0);
	/// <summary>
	/// Unbinds the texture.
	/// </summary>
	void unbind();

	/// <returns>the width of the texture in pixels.</returns>
	inline int get_width() const { return width; };
	/// <returns>the height of the texture in pixels.</returns>
	inline int get_height() const { return height; };
};

#endif // header guard