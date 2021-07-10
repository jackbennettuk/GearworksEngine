#pragma once

#include "gwrendering.h"

class Engine {
private:
	unsigned int *mainShaderProgram;
	VertexArrayObject *vao;
public:
	Engine(unsigned int *_mainShaderProgram, VertexArrayObject *_vao);
	~Engine();

	/// <summary>
	/// <para>Initializes the engine.</para>
	/// </summary>
	void Initialize();

	/// <summary>
	/// <para>Update logic for the engine. It is run before Render().</para>
	/// </summary>
	void Update();

	/// <summary>
	/// <para>Rendering for the engine. It is run after Update().</para>
	/// </summary>
	void Render();

	/// <summary>
	/// <para>This function deletes any pointer variables and then sets their dangling pointers to NULL.</para>
	/// <para>Call this when the program ends.</para>
	/// </summary>
	void Clean();
};