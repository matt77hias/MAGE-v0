<img align="left" src="res/MAGE.png" width="120px"/>

[![Build status][s1]][av] [![Documentation][s2]][do] [![License][s3]][li] [![Join the chat at https://gitter.im/WickedEngine/Lobby][s4]][gi]
<a href="https://twitter.com/intent/follow?screen_name=matt77hias"><img src="https://img.shields.io/twitter/follow/matt77hias.svg?style=social" alt="follow on Twitter"></a>

[s1]: https://ci.appveyor.com/api/projects/status/ike880pg85pupdj6?svg=true
[s2]: https://img.shields.io/badge/docs-doxygen-blue.svg
[s3]: https://img.shields.io/badge/licence-No%20Licence-blue.svg
[s4]: https://badges.gitter.im/MatthiasAdvancedGameEngine/Lobby.svg

[av]: https://ci.appveyor.com/project/matt77hias/MAGE
[do]: https://matt77hias.github.io/MAGE-Doc/MAGE-Doc/html/index.html
[gi]: https://gitter.im/MatthiasAdvancedGameEngine/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
[li]: https://raw.githubusercontent.com/matt77hias/MAGE/master/LICENSE.txt

# MAGE - Matthias Advanced Game Engine

## About

<p align="center"><img src="res/Example.png"></p>

<p align="center">
<img src="res/Example 2.png" width="214">
<img src="res/Example 3.png" width="214">
<img src="res/Example 4.png" width="214">
<img src="res/Example 5.png" width="214">
</p>

<p align="center"><img src="meta/Pipeline.png"></p>

**License**: Currently, MAGE is licensed under a [No License](https://raw.githubusercontent.com/matt77hias/MAGE/master/LICENSE.txt), since we do not allow diverging from the base version yet in this early stage of development.  

## Development
* **Platform**: (minimum) Windows 10 32 Bit and 64 Bit (Windows API + Direct3D 11)
* **Engine Programming Language**: ISO C++ Latest Draft Standard (> C++17)
* **Shading Model**: Shader Model 5.0
* **Scripting Language**: ISO C++ Latest Draft Standard (> C++17)
* **Dependencies**:
  * d3d11.lib
  * dxgi.lib
  * dinput8.lib
  * dxguid.lib
  * (d3dcompiler.lib)
* **Compiler**: MSVC++ 15.0
* **IDE**: Visual Studio 2017

## Use

### How to build the sample project?
1. Open the Solution file `MAGE\MAGE\MAGE.sln` in Visual Studio 2015 (or higher).
2. Build the Solution (Platform: `x64|x86`, Configuration: `Debug|Release`).
3. Reposition the [assets directory](https://github.com/matt77hias/MAGE-Assets) and all of its contents to the `MAGE\MAGE\FPS\bin\<Platform>\<Configuration>\assets` directory. This is required for running the .exe from inside and outside Visual Studio.
4. Run `MAGE\MAGE\FPS\bin\<Platform>\<Configuration>\FPS.exe` from inside or outside Visual Studio.
5. Have fun!
 * Sample scene - buttons:
   * mouse: camera
   * arrows (or WASD): movement
   * left shift: vertical down movement
   * right shift: vertical up movement
   * c: switch scene
   * F1: terminate

## Index
* [Code Guidelines](meta/code-guidelines.md)
* [Documentation](https://matt77hias.github.io/MAGE-Doc/MAGE-Doc/html/index.html)
* [FAQ](meta/faq.md)
* [Features](meta/features.md)
* [File Formats](meta/file-formats.md)
* [Iterations](meta/iterations.md)
* [References](meta/references.md)
* [Standard Scripts](meta/standard-scripts.md)

<p align="center">Copyright © 2016-2017 Matthias Moulin. All Rights Reserved.</p>
