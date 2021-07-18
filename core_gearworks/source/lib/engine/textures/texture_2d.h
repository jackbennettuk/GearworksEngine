#pragma once

#include <iostream>

class texture_2d {
private:
	// Renderer ID
	unsigned int renderer_id;

	// Path to the image file
	std::string path;

	// Texture properties - width, height, and bits-per-pixel.
	int width, height, bits_per_pixel;
public:
	/// <summary>
	/// <para>Default constructor for texture - DOES NOT CREATE A TEXTURE! For that, use create_texture().</para>
	/// <para>This is so the `new` keyword does not have to be used on texture creation. We hate the `new` keyword.</para>
	/// </summary>
	texture_2d();

	/// <summary>
	/// <para>Create the texture with a given path.</para>
	/// </summary>
	/// <param name="path">The path of the texture as a string.</param>
	void load_texture(std::string _path);

	/// <summary>
	/// Binds the texture at a (optional) given slot.
	/// </summary>
	/// <param name="slot">(Optional) the texture slot to bind the texture to.</param>
	void bind(unsigned int slot = 0);

	/// <summary>
	/// Unbinds the texture.
	/// </summary>
	void unbind();

	inline int get_width() const { return width; };
	inline int get_height() const { return height; };
};