#pragma once

#include "../lib/rendering/shader_interpretation/ShaderInterpreter.h"

#include "../lib/rendering/gl_buffer_objs/vbo.hpp"
#include "../lib/rendering/gl_buffer_objs/ibo.hpp"
#include "../lib/rendering/gl_buffer_objs/vertexbufferlayout.hpp"

#include "../lib/rendering/gl_buffer_objs/vao.hpp"

#include "../lib/rendering/shapes/Rectangle.h"
#include "../lib/rendering/shapes/Triangle.h"

#include <depGL/Glad/glad.h>
#include <depGL/GLFW3/glfw3.h>
#include <depGL/glm/glm.hpp>
#include <depGL/glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>

class GWRenderer {
private:
	unsigned int shaderProgramID;
public:
	// Shader program ID getter
	inline unsigned int *GetShaderProgramID() { return &shaderProgramID; }

	/// <summary>
	/// <para>Initialises the global orthographic matrices as larger spaces than just -1.0 - 1.0.</para>
	/// </summary>
	inline void InitializeOrthoProjection() {
		glm::mat4 modelMat = glm::ortho((float)-500, (float)500, (float)-500, (float)500, -1.0f, 1.0f);

		Shader::ModifyUniformmat4(&shaderProgramID, "u_ModelMat", modelMat);
	}

	/// <summary>
	/// Binds the shader program.
	/// </summary>
	inline void BindShaderProgram() { GL_CALL(glUseProgram(shaderProgramID)); }
	/// <summary>
	/// Unbinds the shader program.
	/// </summary>
	inline void UnbindShaderProgram() { GL_CALL(glUseProgram(0)); }

	/// <summary>
	/// <para>Initializes the global:</para>
	/// <para>  - vertex shader</para>
	/// <para>  - fragment shader</para>
	/// <para>and binds them.</para>
	/// </summary>
	inline void InitializeShaders() {
		// Create the main shader program
		shaderProgramID = glCreateProgram();

		// Necessary shaders - they are destroyed when outside the InitializeShaders scope
		Shader vertexShader("resources/shaders/.vert", GL_VERTEX_SHADER, shaderProgramID);		// Vertex shader
		Shader fragmentShader("resources/shaders/.frag", GL_FRAGMENT_SHADER, shaderProgramID);	// Fragment shader

		// Bind the shader program
		BindShaderProgram();
	}

	/// <summary>
	/// <para>Sets up blending to allow for transparent pixels or textures.</para>
	/// </summary>
	inline void EnableTransparentBlending() {
		// Enable blending for transparency
		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	/// <summary>
	/// <para>Clears the screen of the window assigned to the current OpenGL context.</para>
	/// </summary>
	/// <param name="colour">The colour of the screen to clear. If not given, the screen will be cleared to black.</param>
	static inline void ClearScreen(glm::vec4 colour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) {
		// Change the background colour to a dark gray
		GL_CALL(glClearColor(colour.r, colour.g, colour.b, colour.a));
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	/// <summary>
	/// Struct that holds a GLFW window along with its size and title
	/// </summary>
	struct GWWindow {
	private:
		// GLFW handle to this window instance
		GLFWwindow *glfwPtr;

		// Window properties
		int winSizeX, winSizeY;
		std::string winTitle;
	public:
		// GLFW pointer getter
		inline GLFWwindow *GetGLFWInstance() { return glfwPtr; }

		// Window dimension getters
		inline int GetWindowSizeX() { return winSizeX; }
		inline int GetWindowSizeY() { return winSizeY; }

		// Window title getter and setter
		inline std::string GetWindowTitle() { return winTitle; }
		inline void SetWindowTitle(std::string str) { winTitle = str; glfwSetWindowTitle(glfwPtr, winTitle.c_str()); }

		/// <summary>
		/// <para>Constructor to initialize a GLFW window with a given title.</para>
		/// </summary>
		/// <param name="title">The title of the window to initialize.</param>
		/// <param name="sizeX">The optional width of the window - default is 720.</param>
		/// <param name="sizeY">The optional height of the window - default is 480.</param>
		inline GWWindow(std::string title, int sizeX = 720, int sizeY = 480) {
			// Set default window size as the private static int.
			// This variable will be updated whenever the window is resized and can be accessed outside the class by a getter.
			winSizeX = sizeX;
			winSizeY = sizeY;

			// Create the window and assert it through the console
			std::cout << "[GW] Initializing: Creating the window... ";
			glfwPtr = glfwCreateWindow(winSizeX, winSizeY, title.c_str(), NULL, NULL);
			CONASSERT(glfwPtr);

			GLFWimage icon[1] = {};
			// Load the icon into the 'icon' variable, declared above, using stb_image
			icon[0].pixels = stbi_load("resources/textures/window/icon.png", &icon[0].width, &icon[0].height, 0, 4);
			// Set the window icon to this loaded image
			glfwSetWindowIcon(glfwPtr, 1, icon);
			// Now free the image from the variable
			stbi_image_free(icon[0].pixels);

			// Set this window to be the current OpenGL context
			glfwMakeContextCurrent(glfwPtr);

			// Set the OpenGL swap interval to 1
			glfwSwapInterval(1);
		}

		/// <summary>
		/// <para>Swaps front and back buffers and polls any window events.</para>
		/// </summary>
		inline void UpdateWindow() {
			// Swap buffers
			glfwSwapBuffers(glfwPtr);
			// Poll window events
			glfwPollEvents();
		}
	};
};