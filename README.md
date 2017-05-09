# MAGE

## About
<p align="center"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Example.png"></p>

MAGE - Matthias Advanced Game Engine

<p align="center"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Lambertian.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Phong.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Blinn-Phong.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/Modified-Blinn-Phong.png" width="215"></p>
<p align="center"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/TSNM_Lambertian.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/TSNM_Phong.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/TSNM_Blinn-Phong.png" width="215"><img src="https://github.com/matt77hias/MAGE/blob/master/res/Material/TSNM_Modified-Blinn-Phong.png" width="215"></p>

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

## Codebase
*Assets*:
* Crytek Sponza:
  * Marko Dabrovic (original version),
  * Frank Meinl (modified version, [data](http://www.crytek.com/cryengine/cryengine3/downloads)),
  * Morgan McGuire (updated version, [data]((http://graphics.cs.williams.edu/data/meshes.xml))),
  * Matthias Moulin (updated version). 
  
* Utah Teapot: 
  * Martin Newell (original version),
  * Kenzie Lamar (updated version),
  * Morgan McGuire ([data]((http://graphics.cs.williams.edu/data/meshes.xml))),
  * Matthias Moulin (updated version).
  
* [Logo](http://www.deviantart.com/art/Black-Mage-356147620) [[License](https://creativecommons.org/licenses/by-nc-nd/3.0/)]

*Non-substantially* based on:
* [directx-sdk-samples](https://github.com/walbourn/directx-sdk-samples) [[License](https://github.com/walbourn/directx-sdk-samples/blob/master/LICENSE)]
* [directxtk-samples](https://github.com/walbourn/directxtk-samples) [[License](https://github.com/walbourn/directxtk-samples/blob/master/LICENSE)]
* [pbrt-v2](https://github.com/mmp/pbrt-v2): low level, non-pbrt functionality [[License](https://github.com/mmp/pbrt-v2/blob/master/src/LICENSE.txt)]
* [pbrt-v3](https://github.com/mmp/pbrt-v3): low level, non-pbrt functionality [[License](https://github.com/mmp/pbrt-v3/blob/master/LICENSE.txt)]
* [RasterTek: DirectX 11 Tutorials](http://www.rastertek.com/tutdx11.html)
* [RasterTek: DirectX 11 Tutorials - Series 2](http://www.rastertek.com/tutdx11s2.html)
* [VYGE](https://github.com/matt77hias/VYGE)

*Substantially* based on:
* [DirectXTK](https://github.com/Microsoft/DirectXTK) [[License](https://github.com/Microsoft/DirectXTK/blob/master/LICENSE)]

## Current iteration' TODOs
* Frustum culling
* Collision detection
* Optional MSAA

## Further iterations
* Animation
* Audio
* Network
* Physics

<p align="center">Copyright © 2016-2017 Matthias Moulin. All Rights Reserved.</p>
