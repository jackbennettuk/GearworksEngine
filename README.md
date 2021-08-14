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
You can read the changelog in the file `CHANGELOG.md`, linked [here](CHANGELOG.md).

## Getting Started

| :warning: This guide is confirmed to work  as of version **d3.1.1**. It may be wrong in future updates; in this case, it will be updated. |
|---------------------------------------------------------------------------------------------------------------------------------|

### `Main function`
In the file that contains your `main()` function, put the following code in. This is all you need in most cases in this file, even in larger projects.

```
// Include the Gearworks Engine library with its gearworks.h header file
#include <gearworks.h>

// The main function
int main() {
    // Base gearworks behaviour object that handles all the behind-the-scenes logic
    gearworks::gwehaviour baseobj;

    // Set the base object's initial shaders
    baseobj.vertex_shader_path = "resources/shaders/vert.glsl";
    baseobj.fragment_shader_path = "resources/shaders/frag.glsl";

    // Initialize the base object
    baseobj.initialize();

    // Update the base object (This function runs every frame until the window is closed)
    baseobj.update();

    // Destroy the base object when the window is closed
    baseobj.destroy();

    // End the application successfully
    return 0;
}
```

### `Engine implementation file`
In another file (or the main file), you can implement the library's `engine` class to put your own logic. Keep in mind that, even in a blank project, you need to implement these functions. If you don't have any logic in them, leave them blank but keep the function definition there.

```
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
    gearworks::clear_screen(glm::vec3(0.97f, 0.11f, 0.11f));

    // Put any of your rendering code here
}

void gearworks::engine::clean() {
    // If you have any members that need to be deleted, do that here
}
```

### `Shader files`
Finally, you need to write the shaders of the program yourself - this is here so you can have them work however you want. They are used by OpenGL and so are written in GLSL. The code for a very basic vertex shader is below:

```
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

```
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
