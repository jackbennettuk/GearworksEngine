#pragma once

#include <string>

class Texture2D {
private:
	unsigned int rendererID;

	std::string path;

	int width, height, bitPerPix;
public:
	/// <summary>
	/// <para>The constructor for Texture2Ds that initializes the texture with the given path.</para>
	/// </summary>
	/// <param name="path">The path of the texture as a string.</param>
	Texture2D(std::string _path);
	~Texture2D();

	/// <summary>
	/// Binds the texture at a (optional) given slot.
	/// </summary>
	/// <param name="slot">(Optional) the texture slot to bind the texture to.</param>
	void Bind(unsigned int slot = 0);

	/// <summary>
	/// Unbinds the texture.
	/// </summary>
	void Unbind();

	inline int GetWidth() const { return width; };
	inline int GetHeight() const { return height; };
};