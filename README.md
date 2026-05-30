# SandGl

Sand simulation in C++ and OpenGl

## Requirements

- **CMake** (note: `cmake_minimum_required(VERSION 4.2)`)
- A **C++23**
  - Windows: Visual Studio 2022 
  - Linux: GCC 13+ or Clang 16+ 
- **OpenGL**
- **GLFW 3.3**
- **GLM**

This project uses **glad** in `include/glad/` 

## Getting the code

```bash
git clone https://github.com/Olikli55/SandGl.git
cd SandGl
```

## Build (Windows) - using vcpkg


### 1) Install vcpkg

### If you allready have vcpkg installed and in Environment Variables you dont need to install it again

```powershell
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
```
### 2) Install dependencies 64-bit


```powershell
.\vcpkg.exe install glfw3:x64-windows glm:x64-windows
```


### 3) Configure and build

In the `SandGl` folder:

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE= *YOUR_PATH_TO_VCPKG*\scripts\buildsystems\vcpkg.cmake
cmake --build build --config Release
```

Run:

```powershell
.\build\Release\SandGl.exe
```

> Tip: If you previous build failed build, delete the `build/` folder and re-bild.

## Build (Linux)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

Run:

```bash
./build/SandGl
```

## Shaders (auto-generated header)

During the build CMake runs `embed_shaders.cmake` to generate:

- `src/graphics/rendering/shader/generated_shaders.h`

It embeds these shader files:
- `shaders/default.vert`
- `shaders/default.frag`
- `shaders/frameBufferShaders/frameBuffer.vert`
- `shaders/frameBufferShaders/frameBuffer.frag`


## Troubleshooting

### CMake error: cannot find glfw3 / glm

- If using vcpkg, make sure you passed `-DCMAKE_TOOLCHAIN_FILE=...\vcpkg.cmake` and that you installed the right triplet (`x64-windows` vs `x86-windows`).
- If you changed dependency install paths or toolchains, delete `build/` and configure again.
  
