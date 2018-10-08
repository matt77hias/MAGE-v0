<img align="left" src="https://github.com/matt77hias/MAGE-Meta/blob/master/res/MAGE.png" width="120px"/>

[![Build status][s1]][av] [![Code Quality][s2]][co] [![Documentation][s3]][do] [![License][s4]][li] [![Join the chat][s5]][gi]
<a href="https://twitter.com/intent/follow?screen_name=matt77hias"><img src="https://img.shields.io/twitter/follow/matt77hias.svg?style=social" alt="follow on Twitter"></a>

[s1]: https://ci.appveyor.com/api/projects/status/ike880pg85pupdj6?svg=true
[s2]: https://api.codacy.com/project/badge/Grade/9d2719c91eb445fd916fd07bdeff098d
[s3]: https://img.shields.io/badge/docs-doxygen-blue.svg
[s4]: https://img.shields.io/badge/license-GPL%203.0-blue.svg
[s5]: https://badges.gitter.im/MatthiasAdvancedGameEngine/Lobby.svg

[av]: https://ci.appveyor.com/project/matt77hias/MAGE
[co]: https://www.codacy.com/app/matt77hias/MAGE?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=matt77hias/MAGE&amp;utm_campaign=Badge_Grade
[do]: https://matt77hias.github.io/MAGE-Doc/MAGE-Doc
[li]: https://raw.githubusercontent.com/matt77hias/MAGE/master/LICENSE.txt
[gi]: https://gitter.im/MatthiasAdvancedGameEngine/Lobby

# MAGE - Matthias Advanced Game Engine

**AppVeyor Builds fail due to outdated Windows SDK version**

## About
Game and rendering engine featuring both forward and deferred PBR pipelines with optional indirect illumination using Voxel Cone Tracing.

<p align="center"><img src="https://github.com/matt77hias/MAGE-Meta/blob/master/res/Example.png"></p>
<p align="center"><img src="https://github.com/matt77hias/MAGE-Meta/blob/master/res/Example 4.png"></p>
<p align="center"><img src="https://github.com/matt77hias/MAGE-Meta/blob/master/res/Example 2.png" width="436"><img src="https://github.com/matt77hias/MAGE-Meta/blob/master/res/Example 3.png" width="436"></p>

## Index
* [Code Guidelines](meta/code-guidelines.md)
* [Documentation](https://matt77hias.github.io/MAGE-Doc/MAGE-Doc/html/index.html)
* [FAQ](meta/faq.md)
* [Features](meta/features.md)
* [File Formats](meta/file-formats.md)
* [Iterations](meta/iterations.md)
* [License](https://raw.githubusercontent.com/matt77hias/MAGE/master/LICENSE.txt)
* [References](meta/references.md)
* [Standard Scripts](meta/standard-scripts.md)

## Development
* **Platform**: Windows 10 32 Bit and 64 Bit (Windows API + Direct3D 11)
* **Engine Programming Language**: ISO C++ Latest Draft Standard (> C++17)
* **Scripting Language**: ISO C++ Latest Draft Standard (> C++17)
* **Shading Language**: HLSL (Shader Model 5.0)
* **Dependencies**:
  * [d3d11.lib](https://msdn.microsoft.com/en-us/library/windows/desktop/ff476080(v=vs.85).aspx)
  * [dxgi.lib](https://msdn.microsoft.com/en-us/library/windows/desktop/hh404534(v=vs.85).aspx)
  * [dinput8.lib](https://msdn.microsoft.com/en-us/library/windows/desktop/ee416842(v=vs.85).aspx)
  * dxguid.lib
  * ([d3dcompiler.lib](https://msdn.microsoft.com/en-us/library/windows/desktop/dd607340(v=vs.85).aspx))
* **Compiler**: MSVC++ 15.8.6
* **IDE**: Visual Studio 2017

<p align="center">Copyright © 2016-2018 Matthias Moulin. All Rights Reserved.</p>
