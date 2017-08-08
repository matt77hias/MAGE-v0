# MAGE - Matthias Advanced Game Engine

## About
<p align="center"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Example.png"></p>

<p align="center"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Lambertian.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Blinn-Phong.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Modified Blinn Phong.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Cook Torrance.png" width="215"></p>
<p align="center"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Lambertian + tsnm.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Blinn Phong + tsnm.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Modified Blinn Phong + tsnm.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Cook Torrance + tsnm.png" width="215"></p>

**Provides**: input handling for keyboard and mouse, scripting functionality and standard scripts, resource management (shaders, textures, fonts, models, variables scripts, etc.), sprite rendering (image, text, etc.), scene hierarchies, multiple cameras/lights/models, multiple materials and shaders (Diffuse, Lambertian BRDF, Phong BRDF, Modified Phong BRDF, Blinn-Phong BRDF, Modified Blinn-Phong BRDF, Ward BRDF, Ward-Duer BRDF, Cook-Torrance BRDF, all with or without tangent or object space normal mapping), dynamic and multiple lights (ambient, directional, omni and spotlights) lighting, single layer of transparency, configurable display modes, non-hierarchical view frustum culling, switching between windowed and full screen mode, .MDL (model)/ .MSH (mesh)/ .OBJ (model/mesh)/ .MTL (material)/ .DDS (texture)/ .SPRITEFONT (font)/ .VS (variable script) loaders.

## Development
* **Platform**: (minimum) Windows 8.1 32 Bit and 64 Bit (Windows API + Direct3D 11)
* **Engine Programming Language**: C++14 (will and must change to C++17 since I need `if-constexpr`)
* **Shading Model**: Shader Model 5.0
* **Scripting Language**: C++14
* **Dependencies**:
  * d3d11.lib
  * dxgi.lib
  * dinput8.lib
  * dxguid.lib
  * (d3dcompiler.lib)
* **Compiler**: MSVC++ 14.0
* **IDE**: Visual Studio 2015 (will change to Visual Studio 2017 when "Visual Studio 2017 Color Theme Editor" is released)

## Use

### How to build the sample project?
1. Open the Solution file `MAGE\MAGE\MAGE.sln` in Visual Studio 2015 (or higher).
2. Build the Solution (Platform: `x64|x86`, Configuration: `Debug|Release`).
3. Reposition the `MAGE/MAGE/assets/` directory and all of its contents to the `MAGE\MAGE\FPS\bin\<Platform>\<Configuration>\assets` directory. This is required for running the .exe from inside and outside Visual Studio.
4. Run `MAGE\MAGE\FPS\bin\<Platform>\<Configuration>\FPS.exe` from inside or outside Visual Studio.
5. Have fun!

## Index
* [Codebase](https://github.com/matt77hias/MAGE/blob/master/meta/codebase.md)
* [Code Guidelines](https://github.com/matt77hias/MAGE/blob/master/meta/code-guidelines.md)
* [Documentation](https://matt77hias.github.io/MAGE-Doc/MAGE-Doc/html/index.html)
* [File Formats](https://github.com/matt77hias/MAGE/blob/master/meta/file-formats.md)
* [Iterations](https://github.com/matt77hias/MAGE/blob/master/meta/iterations.md)
* [Standard Scripts](https://github.com/matt77hias/MAGE/blob/master/meta/standard-scripts.md)

<p align="center">Copyright © 2016-2017 Matthias Moulin. All Rights Reserved.</p>
