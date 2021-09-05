#ifndef U_ENGINE_H
#define U_ENGINE_H

#include <gearworks.h>

class gearworks::engine {
private:
	/// <summary>
	/// All initializing logic here.
	/// </summary>
	void initialize();
	/// <summary>
	/// Updating logic, e.g. variable updates and function calls, goes here.
	/// </summary>
	void update();
	/// <summary>
	/// Rendering logic goes here.
	/// </summary>
	void render();
	/// <summary>
	/// Delete any heap allocated members or anything else here.
	/// </summary>
	void clean();
public:
	engine();
	~engine();

	/// <summary>
	/// The main renderer used for the program.
	/// </summary>
	gearworks::renderer *renderer = nullptr;
	/// <summary>
	/// The main input manager used for the program.
	/// </summary>
	gearworks::input_manager *input = nullptr;
	/// <summary>
	/// The first, default camera.
	/// </summary>
	gearworks::elem_camera *camera = nullptr;

	/// <summary>
	/// Path to the vertex shader to use in the program.
	/// Make sure to set it BEFORE calling initialize()!
	std::string vertex_shader_path;
	/// </summary>
	/// <summary>
	/// Path to the fragment shader to use in the program.
	/// Make sure to set it BEFORE calling initialize()!
	/// </summary>
	std::string fragment_shader_path;

	/// <summary>
	/// Initializes the engine process and its members.
	/// </summary>
	void behaviour_initialize();
	/// <summary>
	/// Updates the engine process and its members.
	/// </summary>
	void behaviour_update();
	/// <summary>
	/// Terminates the engine process and its members.
	/// </summary>
	void behaviour_destroy();
};

#endif // header guard