#ifndef ENGINE_H
#define ENGINE_H

class engine {
private:
	// Handle to the renderer
	gw_renderer *renderer_handle; 
public:
	/// <summary>
	/// <para>Creates an engine object with a given renderer.</para>
	/// </summary>
	/// <param name="_renderer">The renderer to `bind` this engine object to.</param>
	engine(gw_renderer *_renderer);
	~engine();

	/// <summary>
	/// <para>Initializes the engine.</para>
	/// </summary>
	void initialize();

	/// <summary>
	/// <para>Update logic for the engine. It is run before render().</para>
	/// </summary>
	void update();

	/// <summary>
	/// <para>Rendering for the engine. It is run after Update().</para>
	/// </summary>
	void render();

	/// <summary>
	/// <para>This function deletes any pointer variables and then sets their dangling pointers to NULL.</para>
	/// <para>Call this when the program ends.</para>
	/// </summary>
	void clean();
};

#endif