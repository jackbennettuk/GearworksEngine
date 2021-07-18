// This file includes all project-related headers. The implementations for each of
// these headers, if it exists, is named the same but with a prefix of "imp_".

// Inline headers should be named with a prefix of "inl_".

#ifndef GEARWORKS_H
#define GEARWORKS_H

// General files - rendering, utility, etc.
#include "../lib/engine/rendering/.main/renderpl.h"							// renderpl.h					[render pipeline]
#include "../lib/engine/utility/utils.h"									// utils.h						[utility]
#include "../lib/engine/rendering/shader_interpretation/shader_mgmt.h"		// shader_mgmt.h				[shader management]

// Buffer objects and array objects
#include "../lib/engine/rendering/gl_buffer_objs/inl_vbo.h"					// inl_vbo.h					[(inline) vbo]
#include "../lib/engine/rendering/gl_buffer_objs/inl_ibo.h"					// inl_ibo.h					[(inline) ibo]
#include "../lib/engine/rendering/gl_buffer_objs/inl_vao.h"					// inl_vao.h					[(inline) vao]

// Textures
#include "../lib/engine/textures/texture_2d.h"								// texture.h					[texture]

// Primitive shapes
#include "../lib/engine/rendering/primitives/inl_triangle_primitive.h"		// inl_triangle_primitive.h		[(inline) triangle 2D primitive]
#include "../lib/engine/rendering/primitives/inl_rectangle_primitive.h"		// inl_rectangle_primitive.h	[(inline) rectangle 2D primitive]

// Engine header
#include "../lib/engine/.main/engine.h"										// engine.h						[engine]

#endif