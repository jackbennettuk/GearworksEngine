# Gearworks Engine

<img src="github/logo.svg" width=200 align=right>

## What is the Gearworks Engine?
The Gearworks Engine is the name of my first rendering / physics / game engine. It is, then, pretty basic - it is mostly for learning and experience. For reference, it uses the following APIs and dependencies:
- OpenGL, loaded with [glad](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [stb_image](https://github.com/nothings/stb)

I'm currently still in school so I don't have too much time for it. I try to keep it as organized and professional as a personal project should be :).

I have tried integrating CMake for a better project setup, but have gone back to simple Visual Studio solution files and builds, just because it's easier and I'd rather spend more time coding the actual program.

Finally, I'm proud to say it is, and always will be, **completely open-source**, along with any other large projects I make in the future.

## Change log
You can read the development log in the file `CHANGELOG.md`, linked [here](CHANGELOG.md).

## Commit guidelines
When committing to this project, do the following:
- Name the commit after the most up-to-date version included in that commit, e.g. `Version d1.4.1`.
- In the commit description, summarize the additions clearly with correct grammar and spelling because hey, this is my repo, so I get to be pedantic!
- Make sure to include any additions to the [`CHANGELOG.md`](CHANGELOG.md) file.

Whenever you update the `__PROG_VERSION_MAJOR__` or `__PROG_VERSION_MINOR__` macros, commit your changes. On the flip side: whenever you commit your changes, update the `__PROG_VERSION_MAJOR__` or `__PROG_VERSION_MINOR__` macros.

When committing a .md file, do whatever, unless it's a complete overhaul, in which case you should say something like `A complete overhaul of [this file]`. Really, just leave it as the default `Update [this file].md`.
