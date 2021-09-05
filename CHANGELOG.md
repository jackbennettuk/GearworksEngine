# Gearworks Engine: Changelog
This file details the history in development of the Gearworks Engine.

---
<img align=right width=80 src="https://svgshare.com/i/_ic.svg"> 
  
## **Release** version history
Currently, there has not been any release versions.

---

<img align=right width=80 src="https://svgshare.com/i/_i0.svg"> 

## **Experimental** version history
Currently, there has not been any experimental versions.

---

<img align=right width=80 src="https://svgshare.com/i/_iK.svg"> 

## **Development** version history
  
<details>
<summary><i>Version dev-v1.x</i></summary>
  
### 2021/06/27 - versions `dev-v1.0` - `dev-v1.1`:
- \[++] Started development
- \[+] Implemented shader parsing and compilation.
### 2021/06/28 - version `dev-v1.2`:
- \[++] Added VertexBufferObject handling
- \[+] Refactored by adding some more comments and summary tags
### 2021/06/29 - version `dev-v1.3`:
- \[++] Added IndexBufferObject handling
- \[+] Implemented a `GL_CALL` function that checks OpenGL functions for errors
- \[+] Added some bad VAO code
- \[!] Fixed an uncaught OpenGl error in the fragment shader source code
### 2021/06/30 - versions `dev-v1.3.1` - `dev-v1.4`:
- \[++] Implemented rectangles in the `Rectangle.cpp/.h` files and struct
- \[+] Abstracted triangle programming into the `Triangle.cpp/.h` files and struct
- \[!] Fixed buggy VAO code
### 2021/07/01 - versions `dev-v1.4.1` - `dev-v1.5`:
- \[++] Converted default Normalized coordinate system to Absolute
- \[+] Changed the console title due to the planned inclusion of a debug prompt in the first release
### 2021/07/03 - version `dev-v1.5.1`:
- \[++] Converted Absolute coordinate system to World system
- \[+] Abstracted coordinate-related methods to the `util::coord` struct
### 2021/07/05 - version `dev-v1.5.1.1`:
- \[+] Entirely refactored the Vertex Array system and how they are handled
### 2021/07/09 - version `dev-v1.6`:
- \[++] Implemented textures!
- \[++] Modified shape structs so that a texture or colour can be given via the constructor
- \[+] When shapes are created, their origin is now in the center rather than the bottom-left.
- \[+] Refactored VAO system again, essentially reverting version dev-v1.5.1.1 `¯\_(ツ)_/¯`
- \[+] Renamed `DEV.md` to `CHANGELOG.md`
- \[-] Removed Vertex Buffer Layouts (?)
### 2021/07/10 - version `dev-v1.6.1`:
- \[+] Applied all changed to the rectangle (from `dev-v1.6`) to the triangle struct. [Note: textures cannot be applied to triangles as of this version!]
- \[+] Refactored VAO system again. For the final time? I think? (note: he was wrong)
### 2021/07/11 - version `dev-v1.7`:
- \[+] Abstracted window management to `gwrendering.h` as part of the `gwrenderer` class
- \[+] Abstracted orthographic initialization to the `gwrenderer` class.
- \[+] Abstracted shader initialization to the `gwrenderer` class.
- \[+] Abstracted blend handling to the `gwrenderer` class.
### 2021/07/12 - version `dev-v1.7.1`:
- \[+] Some more rendering abstraction
### 2021/07/13 - versions `dev-v1.7.2` - `dev-v1.7.3`:
- \[++] Set up projection and viewports - for window resizing - better, so that more of the world is shown when the window is resized.
- \[++] Updated the model view projection matrix setup
- \[+] Some more various abstraction and refactoring
### 2021/07/14 - version `dev-v1.8`:
- \[++] Changed MVP system to allow for rendering of multiple shapes
- \[+] Rearranged file structure
- \[+] Refactored the way the `Renderer` (used to be `GWRenderer`) class is implemented (from inline to with a .cpp file)
- \[-] (temporarily) deleted `Triangle` class as it was far out-dated compared to the `Rectangle` equivalent. A new version of it will be re-added later.

</details>
  
<details>
<summary><i>Version dev-v2.x</i></summary>

### 2021/07/18 - versions `dev-v2.0` - `dev-v2.2.1`:
- \[++] Refactored entire project for better quality of life when developing
- \[++] Finally completed the VAO system for better optimization when showing multiple primitives
- \[++] Re-added triangles
- \[+] Added texture-and-colour blending
- \[+] Added MSAA anti-aliasing
- \[+] Changed naming conventions from `camelCase` to `snake_case`
- \[!] Fixed translation distortion bug (detailed in issue [#1](https://github.com/jackbennettuk/GearworksEngine/issues/1))
### 2021/07/19 - version `dev-v2.2.2`:
- \[+] Finalised `translate()`, `scale()`, and `rotate()` functions (affects **model** matrix)
### 2021/07/20 - version `dev-v2.2.3`:
- \[+] Finalised the zooming feature.
### 2021/07/21 - version `dev-v2.3`:
- \[++] Implemented input handling, not completed yet.
  
</details>

<details>
<summary><i>Version dev-v3.x</i></summary>
  
### 2021/08/04 - version `dev-v3.0`:
- \[++] Moved all current code to a static library (now in project `core_gearworks_lib`) rather than an executable
- \[++] Created a demo project to store the demo executable (project `demo`)
- \[++] Created namespace `gearworks` to store all classes and members related to the library
- \[+] Refactored various functions etc
### 2021/08/06 - versions `dev-v3.0.1` - `dev-v3.1.1`:
- \[++] Added default colours to store vector-3s, e.g. `gearworks::col_orangered`
- \[+] Abstracted some update code to the `gwehaviour.update()` function
- \[+] Refactored library code to more seperated, readable files
- \[+] Removed duplicate dependencies from the demo project ([#2](https://github.com/jackbennettuk/GearworksEngine/issues/2)).
- \[+] Ignored warning LNK4098 ([#3](https://github.com/jackbennettuk/GearworksEngine/issues/3))
### 2021/08/29 - versions `dev-v3.1.2` - `dev-v3.1.3`:
- \[+] Minor changes to simplify some functions, e.g. aliases for glm objects
- \[!] Fixed a major rotation bug as detailed in issue [#4](https://github.com/jackbennettuk/GearworksEngine/issues/4)
### 2021/08/30 - version `dev-v3.2.0`:
- \[++] Added the `properties` struct to shapes to better organise attributes such as colour and position
- \[+] Slightly redesigned the way shape transformations are applied every frame
- \[!] Fixed a bug where partially transparent shapes would occasionally not render
### 2021/08/31 - version `dev-v3.2.0.1`:
- \[+] Some minor changes to the file structure
- \[+] Added some aliases for frequently-used functions, e.g. `glm::vec3` -> simply `vec3`
### 2021/09/01 - versions `dev-v3.2.1` - `dev-3.3.0`:
- \[++] Converted most code to work in 3D space
- \[++] Added the cube preset 3D shape and a cube object to `.demo`
- \[+] Finalised basic 3D space
- \[+] Added triangle types, e.g. `GEAR_EQUILATERAL_TRI` and `GEAR_SCALENE_TRI`
- \[+] Added position, rotation, and scale parameters to shapes to further simplify using them
- \[+] Added some "camera" rotation to the demo project using WASD for testing
- \[!] Fixed 3D rotation around the center of objects
### 2021/09/05 - versions `dev-3.4.0` - `dev-v3.4.0.1`:
- \[++] Added a camera class and its transformations
- \[++] Created the Gearworks SDK to include any default resources
- \[+] Added option to textures to choose scaling algorithm between `linear` and `nearest_neighbour`
- \[+] Added a FPS style camera script to .demo
- \[+] Added the `input_manager::center_cursor` function
- \[+] Clamped rotation values to 360 and -360
- \[!] Fixed a heap corruption exception that originally occurred due to reasons related to camera rotation

</details>

---
