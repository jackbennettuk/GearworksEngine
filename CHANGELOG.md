# Gearworks Engine: Change log
This file details the history in development of the Gearworks Engine.

## Formatting
When adding logs to this file, the following formatting system will be used:

### Use of the date
When logging a new version, the date of the version creation should be noted in **YYYY/MM/DD** format: `2022/07/22`
### Version numbering
- For **development** 🔴 versions, list the version number with a 'd' character before it: `version d1.12`.
- For **release** 🟢 versions, simply list the version number on its own, but note the word "release" before "version": `release version 2.3`.
- For **experimental** 🔵 versions, list the **major** number on its own, and include the word "experimental": `experimental version 6`.<sup>1</sup>
### Types of updates
- When a **major** feature has been added, use the symbol `[++]`.
- When a **minor** feature has been added, use the symbol `[+]`.
- When a **bug** has been fixed, use the symbol `[!]`.
- When a **feature** of any type has been removed, use the symbol `[-]`
### Combining this formatting
With this formatting system, a new version log should look like this in the Markdown editor:<sup>2</sup>
```
### 23/07/2022 - experimental version `13`:
- \[++] Made the program _really_ good
- \[+] Made the program good
- \[!] Fixed a bug where the program was bad
- \[-] Removed the bad stuff from the program
```
If there are versions of the same type made in the same day, change `experimental version '13'` to `experimental versions '13' - '16'`. However, if the versions are of different types, e.g. release and development, log them seperately. However, any versions of any type that are created on different days should be logged seperately.

## Version history
### 🔴 2021/06/27 - versions `d1.0` - `d1.1`:
- \[++] Started development
- \[+] Implemented shader parsing and compilation.
### 🔴 2021/06/28 - version `d1.2`:
- \[++] Added VertexBufferObject handling
- \[+] Refactored by adding some more comments and summary tags
### 🔴 2021/06/29 - version `d1.3`:
- \[++] Added IndexBufferObject handling
- \[+] Implemented a `GL_CALL` function that checks OpenGL functions for errors
- \[+] Added some bad VAO code
- \[!] Fixed an uncaught OpenGl error in the fragment shader source code
### 🔴 2021/06/30 - versions `d1.3.1` - `d1.4`:
- \[++] Implemented rectangles in the `Rectangle.cpp/.h` files and struct
- \[+] Abstracted triangle programming into the `Triangle.cpp/.h` files and struct
- \[!] Fixed buggy VAO code
### 🔴 2021/07/01 - versions `d1.4.1` - `d1.5`:
- \[++] Converted default Normalized coordinate system to Absolute
- \[+] Changed the console title due to the planned inclusion of a debug prompt in the first release
### 🔴 2021/07/03 - version `d1.5.1`:
- \[++] Converted Absolute coordinate system to World system
- \[+] Abstracted coordinate-related methods to the `util::coord` struct
### 🔴 2021/07/05 - version `d1.5.1.1`:
- \[+] Entirely refactored the Vertex Array system and how they are handled
### 🔴 2021/07/09 - version `d1.6`:
- \[++] Implemented textures!
- \[++] Modified shape structs so that a texture or colour can be given via the constructor
- \[+] When shapes are created, their origin is now in the center rather than the bottom-left.
- \[+] Refactored VAO system again, essentially reverting version d1.5.1.1 `¯\_(ツ)_/¯`
- \[+] Renamed `DEV.md` to `CHANGELOG.md`
### 🔴 2021/07/10 - version `d1.6.1`:
- \[+] Applied all changed to the rectangle (from `d1.6`) to the triangle struct. [Note: textures cannot be applied to triangles as of this version!]
- \[+] Refactored VAO system again. For the final time? I think?
### 🔴 2021/07/11 - version `d1.7`:
- \[++] Added the orange 'gear' window icon
- \[+] Abstracted window management to `gwrendering.h` as part of the `gwrenderer` class
- \[+] Abstracted orthographic initialization to the `gwrenderer` class.
- \[+] Abstracted shader initialization to the `gwrenderer` class.
- \[+] Abstracted blend handling to the `gwrenderer` class.
### 🔴2021/07/12 - version `d1.7.1`:
- \[+] Some more rendering abstraction
### 🔴 2021/07/13 - versions `d1.7.2` - `d1.7.3`:
- \[++] Set up projection and viewports - for window resizing - better, so that more of the world is shown when the window is resized.
- \[++] Updated the model view projection matrix setup
- \[+] Some more various abstraction and refactoring

## Footnotes
- <sup>1</sup> This numbering system is due to the limited number of experimental releases; a major and minor number system is simple not necessary.
- <sup>2</sup> It is important to ensure the back-slashes before the brackets so that links are not created.
