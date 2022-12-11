# Features

## Table of contents
* [Display](#SS-Display)
* [Input Handling](#SS-Input-Handling)
* [File Formats](#SS-File-Formats)
* [GUI](#SS-GUI)
* [Rendering](#SS-Rendering)
* [Resource Management](#SS-Resource-Management)
* [Scene](#SS-Scene)
* [Scripting](#SS-Scripting)
* [Transformations](#SS-Transformations)

## <a name="SS-Display"></a>Display
* Configurable display modes
  * Anti-aliasing
  * Refresh rate
  * Resolution
  * Vsync
  * Windowed vs. full screen
* Multi split-screen
* Switching between windowed and full screen

## <a name="SS-Input-Handling"></a>Input Handling
* Keyboard
* Mouse (LMB, MMB and RMB are supported)

## <a name="SS-File-Formats"></a>[File Formats](FileFormats.md)
* Fonts
  * .FONT (Sprite Font) **[MAGE Dedicated Format]**
* Models, Meshes and Materials
  * .MDL  (Model) **[MAGE Dedicated Format]**
  * .MSH  (Mesh)  **[MAGE Dedicated Format]**
  * .MTL  (Material) **[MAGE Customized Format]**
  * .OBJ  (Wavefront OBJ)
* Texture
  * .BMP, .DIB  (Windows Bitmap Format)
  * .DDS  (DirectDraw Surface) **[preferred]**
  * .GIF  (Graphics Interchange Format 89a)
  * .HDP, .WDP, .JXR  (HD Photo, Windows Media Photo, JPEG-XR)
  * .ICO  (Icon Format)
  * .JPG, .JPEG, .JPE (Joint Photographic Experts Group)
  * .PNG  (Portable Network Graphics)
  * .TIF, .TIFF (Tagged Image File Format)
* Properties
  * .VAR   (Variable Script) **[MAGE Dedicated Format]**

## <a name="SS-GUI"></a>GUI
* ImGui integration

## <a name="SS-Rendering"></a>Rendering

<p align="center"><img src="https://github.com/matt77hias/MAGE-v0-Meta/blob/gh-pages/res/Architecture/Pipeline.png"></p>

* AA (for HDR, normal and depth buffer)
  * No AA
  * FXAA (using Max3 tone mapping)
  * MSAA (using Max3 tone mapping)
  * SSAA (using Max3 tone mapping)
* AO
  * voxel cone tracing (*not integrated*)
* BRDFs (single BRDF/camera)
  * Lambertian
  * Cook-Torrance, Frostbite:
     * D component: Beckmann, Ward-Duer, Blinn-Phong, Trowbridge-Reitz/GGX/GTR2, Berry/GTR1
     * G|V component: Implicit, Ward, Neumann, Ashikhmin-Premoze, Kelemann, Cook Torrance, (Correlated) GGX, Smith GGX, Smith Schlick-GGX, Smith Beckmann, Smith Schlick-Beckmann
     * F component: None, Schlick, Cook-Torrance
* Color spaces
  * All separate colors from material files are expressed in sRGB color space.
  * All separate colors from color pickers (i.e. ImGui) are expressed in sRGB color space.
  * All separate textures (incl. fonts) are expressed in linear or sRGB color space.
  * All internally stored separate colors are expressed in linear color space (for both C++ and HLSL).
    Exceptions: All internally stored separate colors of ImGui are expressed in sRGB color space. 
    All internally stored separate colors of the voxelization are expressed in LogLuv color space.
  * All color calculations (inc. filtering and blending) are performed in linear color space (for both C++ and HLSL).
  * Final outputted colors are expressed in a custom gamma encoded color space (i.e. brightness adjustment).
* Culling
  * Non-hierarchical light and object culling
* Depth buffer
  * Standard and Reversed Z-depth
  * 32bit float for depth buffer
  * 16bit unorm|32bit float for shadow (cube) maps
* (Temporal) Dithering
* Lighting
  * Optional light interaction for materials (i.e. HDR emissive/black body or not)
  * Single pass for all lights (incl. shadow mapping)
  * Physically-based and smooth angular attenuation for point lights (i.e. omni lights and spotlights)
  * Physically-based and smooth distance attenuation for point lights (i.e. omni lights and spotlights)
  * Exponential fog with custom density (avoids popping artifacts)
  * HDR
  * Direct and indirect illumination (voxel cone tracing)
  * Reflections (voxel cone tracing)
* Normal Mapping
  * Tangent-space (without relying on precomputed tangents and bitangents)
  * ~~Object-space~~ (*not supported any more*)
* Post-processing
  * Depth-of-field
  * Tone Mapping
    * AA resolving (SSAA, MSAA, FXAA): Max3, Reinhard
    * Back buffer: None, ACES Filmic, Max3, Reinhard, Uncharted
* Render Layers (multiple render layers/camera)
  * Bounding volumes
  * Wireframes
* Render Modes (single render mode/camera)
  * Forward
  * Deferred
  * False Color, Voxel Grid, Solid, etc.
* Shadow Mapping
  * Optional occluding behavior for models
  * Support for both opaque and transparent models
  * Depth and slope scaled biasing
  * PCF filtering
  * Directional lights (shadow maps), omni lights (shadow cube maps) and spotlights (shadow maps)
* Sky Domes
  * Non-uniform stretching in looking direction
* Sprites
  * Fonts, images, ImGui
* Transparency
  * ~~Alpha-to-Coverage~~ (*not integrated any more*)
  * Single layer Alpha Blending

## <a name="SS-Resource-Management"></a>Resource Management
* Fonts
* Models
* Shaders: Vertex, Domain, Hull, Geometry, Pixel, Compute
* Textures

## <a name="SS-Scene"></a>Scene
* Camera
  * Orthographic
  * Perspective
* Light
  * Ambient
  * Directional (with or without shadow mapping)
  * Omni (with or without shadow cube mapping)
  * Spot (with or without shadow mapping)
* Model
  * Non-emissive
  * Emissive (direct illumination supported using VCT)
* Sprite
  * Image
  * Text
  
## <a name="SS-Scripting"></a>Scripting
* Custom scripts by overriding `mage::BehaviorScript`
* [Standard scripts](StandardScripts.md)

## <a name="SS-Transformations"></a>Transformations
* Scene hierarchies
* Normal transformations
* Sprite transformations
* Texture transformations

We use the following coordinate frames:

### 2D
* (Supersampled) Display
* (Supersampled) Viewport (*camera dependent*)

### 3D
* Box
* Tangent (generic tangent space)
* Object
* World
* Camera (>0)
* Light (>0)
* Projection
* NDC (NDC z = non-linear depth)
* Shading (generic space; e.g., World, Object, Camera, Light, ...)
* View (generic space; e.g., Object, Camera, Light, ...)

### Texture
* UV
* UVW
