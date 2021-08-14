#ifndef R_RENDERER_H
#define R_RENDERER_H

#include <gearworks.h>

class gearworks::renderer {
private:
	// Handle to the shader program for the renderer
	unsigned int cur_shader_program_id;
	// The window currently assigned to the renderer
	gearworks::window *cur_window;

	// Zooming values
	float current_zoom;
	const float max_zoom = 2.5f, min_zoom = 0.1f;
public:
	/// <summary>
	/// Matrix used in calculation of the 'ModelViewProjection' or 'MVP' matrix.
	/// </summary>
	glm::mat4 project_matrix, view_matrix, model_matrix;

	/// <summary>
	/// Constructor for the GW renderer.
	/// </summary>
	renderer();
	// Destructor
	~renderer();

	/// <summary>
	/// Updates this instance of the renderer. Make sure to run this function every frame!
	/// Also important: run this function once at program initialization, too.
	/// </summary>
	void update_renderer();

	/// <summary>
	/// Creates a GLFW window with given title, size, and any other properties.
	/// </summary>
	/// <param name="title">The title of the window.</param>
	/// <param name="sizeX">The width of the window.</param>
	/// <param name="sizeY">The height of the window.</param>
	void create_window(std::string title, int sizeX = 720, int sizeY = 480);

	/// <summary>
	/// Initializes the global:
	///   - vertex shader
	///   - fragment shader
	/// and binds them to this renderer.
	/// </summary>
	/// <param name="vertex_shader_path">Path to the vertex shader to use.</param>
	/// <param name="fragment_shader_path">Path to the fragment shader to use.</param>
	void initialize_shaders(std::string vertex_shader_path = GW_NULLSTR, std::string fragment_shader_path = GW_NULLSTR);

	/// <summary>
	/// Zooms in and out by a given amount.
	/// When using this function, keep in mind that the minimum zoom is 0.1 and the maximum zoom is 2.5.
	/// </summary>
	/// <param name="amount">The amount to zoom by. To zoom in, set it to be positive, and to zoom out, set it to be negative.</param>
	void zoom_by_value(float amount);

	/// <returns>the current shader program via its ID.</returns>
	inline unsigned int *get_currentshaderprogram() { return &cur_shader_program_id; }
	/// <returns>the current window.</returns>
	inline gearworks::window *get_currentwindowinstance() { return cur_window; }
};

#endif // header guard