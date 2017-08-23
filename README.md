<img align="left" src="res/MAGE.png" width="120px"/>

[![Build status][s1]][av] [![License][s2]][li] [![Join the chat at https://gitter.im/WickedEngine/Lobby][s3]][gi]

[s1]: https://ci.appveyor.com/api/projects/status/ike880pg85pupdj6?svg=true
[s2]: https://img.shields.io/badge/licence-No%20Licence-blue.svg
[s3]: https://badges.gitter.im/MatthiasAdvancedGameEngine/Lobby.svg
[av]: https://ci.appveyor.com/project/matt77hias/MAGE
[gi]: https://gitter.im/MatthiasAdvancedGameEngine/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
[li]: https://raw.githubusercontent.com/matt77hias/MAGE/master/LICENSE.txt

# MAGE - Matthias Advanced Game Engine

## About

<p align="center"><img src="res/Example.png"></p>

<p align="center">
<img src="res/RenderModes/Solid+AABB+Wireframe.png" width="214">
<img src="res/RenderModes/DiffuseTexture.png" width="214">
<img src="res/RenderModes/ReferenceTexture.png" width="214">
<img src="res/RenderModes/TSNMShadingNormal.png" width="214">
</p>
<p align="center">
<img src="res/Material/Lambertian.png" width="214">
<img src="res/Material/TSNM+Lambertian.png" width="214">
<img src="res/Material/WardDuer.png" width="214">
<img src="res/Material/TSNM+WardDuer.png" width="214">
</p>

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
* **IDE**: Visual Studio 2017

## Use

### How to build the sample project?
1. Open the Solution file `MAGE\MAGE\MAGE.sln` in Visual Studio 2015 (or higher).
2. Build the Solution (Platform: `x64|x86`, Configuration: `Debug|Release`).
3. Reposition the `MAGE\MAGE\assets\` directory and all of its contents to the `MAGE\MAGE\FPS\bin\<Platform>\<Configuration>\assets` directory. This is required for running the .exe from inside and outside Visual Studio.
4. Run `MAGE\MAGE\FPS\bin\<Platform>\<Configuration>\FPS.exe` from inside or outside Visual Studio.
5. Have fun!

## Index
* [Codebase](meta/codebase.md)
* [Code Guidelines](meta/code-guidelines.md)
* [Documentation](https://matt77hias.github.io/MAGE-Doc/MAGE-Doc/html/index.html)
* [File Formats](meta/file-formats.md)
* [Iterations](meta/iterations.md)
* [Standard Scripts](meta/standard-scripts.md)

<p align="center">Copyright © 2016-2017 Matthias Moulin. All Rights Reserved.</p>
