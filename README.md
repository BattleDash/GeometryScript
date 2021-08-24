<h1 align="center">Geometry Script</h1>

<h4 align="center">The JavaScript plugin manager for Geometry Dash.</h4>

<p align="center">
  <a href="https://twitter.com/BattleDashBR"><img src="https://img.shields.io/badge/Twitter-@BattleDashBR-1da1f2.svg?logo=twitter"></a>
</p>

------

<p align="center">
  <a href="#development">Development</a> •
  <a href="#examples">Examples</a> •
  <a href="#usage">Usage</a> •
  <a href="#api">API</a> •
  <a href="#credits">Credits</a>
</p>

## Development

This project is currently a work-in-progress in my free time, and I'm currently debugging issues with the V8 JavaScript engine and embedding Node.js, as the docs are really quite bad. It is not usable yet, and I only started working on it a week or two ago.

Since Visual Studio has issues mixing Filters and Folders, I'm exclusively using filters for this project, which is why the actual source structure looks a bit messy. Trust me, it's very neat and tidy once you load it up in VS!

Will be migrated from a VS project to cmake in the future.

Source Structure:
```
GeometryScript/
├── Geometry Dash/
│   └── The initializer, which starts things like the Renderer and NodeManager
├── Globals/
│   └── A single header defining build constants
├── Hooks/
│   └── The trampoline hooking manager
├── Logging/
│   └── The log macros, which stream into <dllname>.log
├── Node Engine/
│   └── The V8 and Node.JS engine code, currently a work-in-progress
├── OpenGL/
│   ├── Renderer/
│   │   └── The ImGUI renderer, which hooks wglSwapBuffers to display our windows
│   └── Window/
│       └── Windows/
│           ├── Various ImGUI window definitions
│           └── Main/
│               ├── The Main Window
│               └── Categories/
│                   └── The definitions for menu bar categories
├── Source Files/
│   └── Dllmain and Program, which start the main threads and initialize everything
├── Third Party/
│   └── Headers for all of the external libraries used, like MinHook, ImGUI, and V8
└── Utilities/
    ├── Directory/
    │   └── Directory utilities for finding paths
    ├── Error Handling/
    │   └── Macros for quickly exiting the program and displaying an error
    └── Platform/
        └── Various Platform utilities, like AOB Pattern Scanning (sigscanning)
 ```

## Examples

TBD

## Usage

TBD

## API

TBD

## Credits

This project was made in some way with the following projects:

- [MinHook](https://github.com/TsudaKageyu/minhook)
- [ImGUI](https://github.com/ocornut/imgui)
- [Node.JS](https://github.com/nodejs/node)
- [V8](https://v8.dev)
- [ReShade](https://github.com/crosire/reshade)
