#pragma once

#include "../lib/rendering/shader_interpretation/ShaderInterpreter.h"

#include "../lib/rendering/gl_buffer_objs/vbo.hpp"
#include "../lib/rendering/gl_buffer_objs/ibo.hpp"

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
	// Struct to store a window in the renderer along with its properties such as size and title.
	struct Window {
	private:
		// --- WINDOW PROPERTIES ---
		// GLFW handle to this window instance
		GLFWwindow *glfwPtr;

		// Window properties
		int winSizeX, winSizeY;
		float aspectRatio;

		std::string winTitle;

	public:
		// --- WINDOW CONSTRUCTOR ---
		inline Window(std::string title, int sizeX = 720, int sizeY = 480) {
			// Set default window size as the private static int.
			// This variable will be updated whenever the window is resized and can be accessed outside the class by a getter.
			winSizeX = sizeX;
			winSizeY = sizeY;

			// Update the aspect ratio
			aspectRatio = (float)winSizeX / (float)winSizeY;

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

		// --- WINDOW FUNCTIONS ---
		inline void UpdateWindowProperties() {
			// Update the window size variables
			glfwGetFramebufferSize(glfwPtr, &winSizeX, &winSizeY);

			// Update the aspect ratio
			aspectRatio = (float)winSizeX / (float)winSizeY;
		}

		inline void UpdateWindowInstance() {
			glfwSwapBuffers(glfwPtr);		// (swap buffers)
			glfwPollEvents();								// (poll window events)
		}

		// --- WINDOW PROPERTIES GETTERS AND SETTERS ---
		// GLFW pointer getter
		inline GLFWwindow *GetGLFWInstance() { return glfwPtr; }

		// Window dimension getters
		inline int GetWindowSizeX() { return winSizeX; }
		inline int GetWindowSizeY() { return winSizeY; }
		inline float GetAspectRatio() { return aspectRatio; }

		// Window title getter and setter
		inline std::string GetWindowTitle() { return winTitle; }
		inline void SetWindowTitle(std::string str) { winTitle = str; glfwSetWindowTitle(glfwPtr, winTitle.c_str()); }
	};

	// -----------------------------------------------
	// -----------------------------------------------
	// -- Code above can be collapsed in most cases --
	// -----------------------------------------------
	// -----------------------------------------------

	// Handle to the shader program for the renderer
	unsigned int shaderProgramID;
	
	// The window currently assigned to the renderer
	Window *window;
public:
	// Shader program ID getter
	inline unsigned int *GetShaderProgramID() { return &shaderProgramID; }

	// Window getter
	inline Window *GetCurrentWindow() { return window; }

	// Constructor
	inline GWRenderer() : shaderProgramID(0), window(nullptr) {}
	// Destructor
	inline ~GWRenderer() {
		// Delete the window variable as it was heap allocated
		DELETE_PTR(window);
	}

	/// <summary>
	/// <para>Updates this instance of the renderer. Make sure to run this function every frame!</para>
	/// </summary>
	inline void UpdateRendererInstance() {
		// Update the window size variables
		window->UpdateWindowProperties();
		// Initialize the coordinate system
		UpdateOrthoProjection();
	}
	/// <summary>
	/// <para>Updates the global orthographic matrices as larger spaces than just -1.0 - 1.0.</para>
	/// </summary>
	inline void UpdateOrthoProjection() {
		// Update the viewport size so it is resized with the window
		glViewport(0, 0, window->GetWindowSizeX(), window->GetWindowSizeY());

		// Create the projection matrix and update it so it is also resized along with window/viewport resize
		glm::mat4 projMat = glm::ortho((float)-window->GetWindowSizeX(), (float)window->GetWindowSizeX(), (float)-window->GetWindowSizeY(),	(float)window->GetWindowSizeY(), -1.0f,	1.0f);

		// Apply this matrix via the vertex shader
		Shader::ModifyUniformmat4(&shaderProgramID, "u_ProjMat", projMat);
	}

	/// <summary>
	/// <para>Binds the shader program.</para>
	/// </summary>
	inline void BindShaderProgram() { GL_CALL(glUseProgram(shaderProgramID)); }
	/// <summary>
	/// <para>Unbinds the shader program.</para>
	/// </summary>
	inline void UnbindShaderProgram() { GL_CALL(glUseProgram(0)); }

	/// <summary>
	/// <para>Creates a GLFW window with given title, size, and any other properties.</para>
	/// </summary>
	/// <param name="title">The title of the window.</param>
	/// <param name="sizeX">The width of the window.</param>
	/// <param name="sizeY">The height of the window.</param>
	inline void gwCreateWindow(std::string title, int sizeX = 720, int sizeY = 480) {
		// Assign the window pointer
		window = new Window(title, sizeX, sizeY);
	}

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
	static inline void EnableTransparentBlending() {
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
};