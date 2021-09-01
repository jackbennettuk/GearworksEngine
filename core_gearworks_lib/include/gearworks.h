// ---------------------------------------------------------------------
// Gearworks Engine: gearworks.h - main library header file
// ---------------------------------------------------------------------
// Include this in your project to make use of the Gearworks game engine
// ---------------------------------------------------------------------

#ifndef GWREND_H
#define GWREND_H

// -------------------------------------------
// Include third-party and system dependencies
// -------------------------------------------

// System
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <Windows.h>		// Library is currently only compatible with Windows.

// GLM
#include <opengl/glm/vec4.hpp>
#include <opengl/glm/mat4x4.hpp>
#include <opengl/glm/gtc/matrix_transform.hpp>

// Glad
#include <opengl/Glad/glad.h>
#include <opengl/GLFW3/glfw3.h>

// stb_image
#include <stb/stb_image.h>

// ----------------------------------------
// Include macro and alias/type-definitions
// ----------------------------------------

#include "../source/lib/prepro.h"
#include "../source/lib/alias.h"

// ----------------------------------------------------------------------
// Declare the main classes of the gearworks namespace for the first time
// ----------------------------------------------------------------------

namespace gearworks {
	// ----------------------------------------
	// Classes related to rendering the project
	// ----------------------------------------

	/// <summary>
	/// Gearworks window that handles window operations via GLFW.
	/// </summary>
	struct window;

	/// <summary>
	/// A gearworks renderer which handles all rendering-related tasks.
	/// </summary>
	class renderer;

	/// <summary>
	/// A gearworks shader for rendering.
	/// </summary>
	struct shader;

	/// <summary>
	/// A gearworks vertex array object for use by OpenGl.
	/// </summary>
	class vertex_array_object;
	/// <summary>
	/// A gearworks vertex buffer object for use by OpenGl.
	/// </summary>
	class vertex_buffer_object;
	/// <summary>
	/// A gearworks index buffer object for use by OpenGl.
	/// </summary>
	class index_buffer_object;

	/// <summary>
	/// A 2D texture object. To load the texture with a given path, call load.
	/// </summary>
	class texture_2d;

	// ------------------------
	// Classes related to input
	// ------------------------

	/// <summary>
	/// Class for an instance manager.
	/// </summary>
	class input_manager;

	// -----------------------
	// Primitive shape classes
	// -----------------------

	/// <summary>
	/// A rectangle object. To create it using a solid colour, use create().
	/// </summary>
	class rectangle;
	/// <summary>
	/// A triangle object. To create it using a solid colour, use create().
	/// </summary>
	class triangle;

	// ------------
	// Engine class
	// ------------

	/// <summary>
	/// Class for all user logic to be referenced in.
	/// Note the 'renderer_handle' variable can be used to reference the renderer that this engine object is associated with.
	/// </summary>
	class engine;
}

// ------------------------------------------------------------------------
// If not otherwise specified, include the definition files for the library
// ------------------------------------------------------------------------

// Utility
#ifndef GW_NOINCLUDE_UTILITY_DEFS
#include "../source/lib/utility/inl_ut_utility.h"
#endif // Utility files 

// Rendering
#ifndef GW_NOINCLUDE_RENDER_DEFS
#include "../source/lib/rendering/shader/r_shader.h"
#include "../source/lib/rendering/bufferobjs/r_bufferobjs.h"
#include "../source/lib/rendering/texture/r_texture.h"
#include "../source/lib/rendering/window/r_window.h"
#include "../source/lib/rendering/renderer/r_renderer.h"
#endif // Rendering files

// Input
#ifndef GW_NOINCLUDE_INPUT_DEFS
#include "../source/lib/input/i_input.h"
#endif // Input files

// Presets
#ifndef GW_NOINCLUDE_PRESET_DEFS
#include "../source/lib/presets/2dim/rectangle/p2d_rectangle.h"
#include "../source/lib/presets/2dim/triangle/p2d_triangle.h"
#endif // Preset shape files

// User-defined classes
#ifndef GW_NOINCLUDE_NONSTATIC_DEFS
#include "../source/lib/userdef/engine/u_engine.h"
#endif // Userdef files

#endif // Header guard