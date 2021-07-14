#pragma once

#include <iostream>

#include "gwrendering.h"
#include "gwutility.h"

class Renderer {
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

	// Handle to the shader program for the renderer
	unsigned int shaderProgramID;
	// The window currently assigned to the renderer
	Window *window;
public:
	// Model matrix for MVP calculation
	glm::mat4 modelMat;

	// Constructor sets:
	// shaderProgramID = 0
	// window = null pointer
	// modelMat = a default (0, 0, 0) translation
	/// <summary>
	/// Constructor for the GW renderer.
	/// </summary>
	Renderer();

	// Destructor
	~Renderer();

	/// <summary>
	/// <para>Updates this instance of the renderer. Make sure to run this function every frame!</para>
	/// <para>Also important: run this function once at program initialization, too.</para>
	/// </summary>
	void UpdateRendererInstance();

	/// <summary>
	/// <para>Creates a GLFW window with given title, size, and any other properties.</para>
	/// </summary>
	/// <param name="title">The title of the window.</param>
	/// <param name="sizeX">The width of the window.</param>
	/// <param name="sizeY">The height of the window.</param>
	void gwCreateWindow(std::string title, int sizeX = 720, int sizeY = 480);

	/// <summary>
	/// <para>Initializes the global:</para>
	/// <para>  - vertex shader</para>
	/// <para>  - fragment shader</para>
	/// <para>and binds them.</para>
	/// </summary>
	void InitializeShaders();

	/// <summary>
	/// <para>Sets up blending to allow for transparent pixels or textures.</para>
	/// </summary>
	static void EnableTransparentBlending();

	/// <summary>
	/// <para>Clears the screen of the window assigned to the current OpenGL context.</para>
	/// </summary>
	/// <param name="colour">The colour of the screen to clear. If not given, the screen will be cleared to black.</param>
	static void ClearScreen(glm::vec4 colour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	/// <summary>
	/// <para>Binds the shader program.</para>
	/// </summary>
	void BindShaderProgram();
	/// <summary>
	/// <para>Unbinds the shader program.</para>
	/// </summary>
	void UnbindShaderProgram();

	// Shader program ID getter
	inline unsigned int *GetShaderProgramID() { return &shaderProgramID; }
	// Window getter
	inline Window *GetCurrentWindow() { return window; }
};