#ifndef U_GWEHAVIOUR_H
#define U_GWEHAVIOUR_H

#include <gearworks.h>

class gearworks::gwehaviour {
public:
	/// <summary>
	/// The main renderer used for the program.
	/// </summary>
	gearworks::renderer *renderer = nullptr;
	/// <summary>
	/// The main input manager used for the program.
	/// </summary>
	gearworks::input_manager *input = nullptr;
	/// <summary>
	/// The main engine instance used for the program.
	/// </summary>
	gearworks::engine *main_engine = nullptr;

	// Destructor
	~gwehaviour();

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
	/// Function to initialize the program.
	/// Run it in the main function before update().
	/// </summary>
	void initialize();

	/// <summary>
	/// Function to update the program.
	/// Run it in the main function. To add your own logic, edit the engine class's update and render functions.
	/// </summary>
	void update();

	/// <summary>
	/// Function to destroy the program (deleting heap-allocated members or other memory-related logic).
	/// Run it in the main function before the return 0 statement.
	/// </summary>
	void destroy();
};

#endif // header guard