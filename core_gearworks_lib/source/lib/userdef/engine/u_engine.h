#ifndef U_ENGINE_H
#define U_ENGINE_H

#include <gearworks.h>

class gearworks::engine {
private:
	// Handle to the renderer
	gearworks::renderer *renderer_handle;
public:
	/// <summary>
	/// Constructor for the engine class.
	/// To actually create the object, use the create() function.
	/// </summary>
	engine();

	/// <summary>
	/// Creates an engine object with a given renderer.
	/// Override this with your own code but be sure to set the renderer_handle variable to the given parameter, _renderer.
	/// If you don't do that step, other code likely will not work.
	/// </summary>
	/// <param name="_renderer">The renderer to `bind` this engine object to.</param>
	void create(gearworks::renderer *_renderer);

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
};

#endif // header guard