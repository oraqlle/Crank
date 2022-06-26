# Crank Framework

Basic console game and app library used to create cross platform console applications and games.
Built using compiler and platform API's and [CortexLib](https://github.com/oraqlle/CortexLib).
Crank offers modern approaches to building simple 2D games in the console.
Its open-source framework means that people can learning the principles of game development in C++ while having access to the libraries source code to see how the engine operates under the hood.

---

## Download

In order for Crank to work, you'll need a C++ compiler like:

- g++       (from the GNU Comipler Collection)

- clang     (from the LLVM project)

- MSVC      (Microsoft Visual Compiler)

- circle    (Sean Baxter's frontend Compiler)

You'll also need to have a built system install. For linux and OSX this is `make` and on Windows this
is `nmake`. `cmake` is also required to create the nessasry build files for CortexLib and Crank.

Instructions for how to install these compilers are in the COMPILER.md file.

Finally, you'll need to have CortexLib installed and built on your system.
Clone the repository below for CortexLib and read the README.md for build instructions and how to include it in your current project or build.

```git clone https://github.com/oraqlle/Crank```

Once CortexLib is built and you have a compiler installed

```git clone https://github.com/oraqlle/Crank```

## Build

## Include in your own Project

## Usage

This framework is built upon a state stack. Developers built states from the `base_state` class that contains virtual member function prototypes such as `draw()` `update()` `handle_events()` etc.
States are like pages, each page gives a different functionality given by the developer depending on the purpose the page must serve.

eg. A menu page might just render text as menu options and doesn't constantly require a redraw while the main game state would have the screen rerendered every frame.

States can also have additional member functions added to them to provide additional funcionality.

## Usage with Docker
