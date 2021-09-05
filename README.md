---

<img src="https://svgshare.com/i/ZNn.svg">

---

## Gearworks: An open-source rendering and physics engine 

The Gearworks Engine is the name of my first rendering / physics / game engine. It is, then, pretty basic - it is mostly for learning and experience. For reference, it uses the following APIs and dependencies
- [OpenGL](https://opengl.org), loaded with [glad](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [stb_image](https://github.com/nothings/stb)
- [glm](https://github.com/g-truc/glm)

I'm currently still in school so I don't have too much time for it. I try to keep it as organized and professional as a personal project should be :).

I have tried integrating CMake for a better project setup, but have gone back to simple Visual Studio solution files and builds, just because it's easier and I'd rather spend more time coding the actual program. I'm also very lazy.

## Changelog
The Gearworks Engine changelog has been moved to its own file. You can read it in the [`CHANGELOG.md`](CHANGELOG.md) file.

## Getting Started

:heavy_check_mark: *This guide was last updated as of version `dev-v3.4.0` and is verified to still be working.*

### `Main function`
In the file that contains your `main()` function, put the following code in. This is all you need in most cases in this file, even in larger projects.

```C++
// Include the Gearworks Engine library with its gearworks.h header file
#include <gearworks.h>

// The main function
int main() {
    // This object is the main game process.
    gearworks::engine game;
    
    // Set the game's initial shaders
    game.vertex_shader_path = "resources/shaders/vert.glsl";
    game.fragment_shader_path = "resources/shaders/frag.glsl";

    // Initialize your game
    game.initialize();

    // Update your game (This function runs every frame until the window is closed)
    game.update();

    // Terminate your game's process when the window is closed
    game.destroy();

    // End the application successfully
    return 0;
}
```

### `Engine implementation`
In another file (or the main file), you can implement the library's `engine` class for your own game logic. Keep in mind that, even in a blank project, you need to implement these functions. If you don't have any logic in them, leave them blank but keep the function definition there.

```C++
// Include the gearworks file here
#include <gearworks.h>

void gearworks::engine::initialize() {
    // Put all of your initialization logic here
}

void gearworks::engine::update() {
    // Put all of your updating logic (updating variables etc) here
}

void gearworks::engine::render() {
    // Clears the screen to a bright red colour
    gearworks::clear_screen(gearworks::col_brightred);

    // Put any of your rendering code here
}

void gearworks::engine::clean() {
    // If you have any members that need to be deleted, do that here
}
```

### `Shader files`
Finally, you need to write the shaders of the program yourself - this is here so you can have them work however you want. They are used by OpenGL and so are written in GLSL. The code for a very basic vertex shader is below:

```GLSL
// Using GLSL version 3.3 (core). You may need to DELETE this comment in your own file - there may be parsing issues otherwise.
#version 330 core

// l_Position stores the position of the vertex.
layout(location = 0) in vec4 l_Position;
// l_TexCoord stores the positions of the texture coordinates. You won't need to worry about this when using Gearworks as it is all abstracted away.
layout(location = 1) in vec2 l_TexCoord;

// Varying variable v_TexCoord sends the above texture coordinates to the fragment shader to be used.
out vec2 v_TexCoord;

// The model matrix - once again, you won't normally need to worry about this if you are not confident in OpenGL.
uniform mat4 u_ModelViewProjMat;

void main() {
    // Set the actual position of the variable on the u_ModelViewProjMat matrix.
    gl_Position = u_ModelViewProjMat * l_Position;

    // Set the texture coordinates varying variable.
    v_TexCoord = l_TexCoord;
}
```

Here is the fragment shader, which you also need:

```GLSL
// Using GLSL version 3.3 (core). You may need to DELETE this comment in your own file - there may be parsing issues otherwise.
#version 330 core

// The l_Colour variable stores the colour of the pixels.
layout(location = 0) out vec4 l_Colour;

// Texture coordinates, passed here by the vertex shader.
in vec2 v_TexCoord;

// The given texture.
uniform sampler2D u_Texture;
// The given blending colour.
uniform vec4 u_Colour;

void main() {
    // Get the colour of the pixel from the texture, using the texture coordinates.
    vec4 texColour = texture(u_Texture, v_TexCoord) * u_Colour;

    // Apply the colour.
    l_Colour = texColour;
}
```
