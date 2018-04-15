# Features

### Display
* Configurable display modes
  * Anti-aliasing
  * Refresh rate
  * Resolution
  * Vsync
  * Windowed vs. full screen
* Multi split-screen
* Switching between windowed and full screen

### Input Handling
* Keyboard
* Mouse (LMB, MMB and RMB are supported)

### [File Formats](https://github.com/matt77hias/MAGE/blob/master/meta/file-formats.md)
* Fonts
  * .FONT (Sprite Font) **[MAGE Dedicated Format]**
* Models, Meshes and Materials
  * .MDL  (Model) **[MAGE Dedicated Format]**
  * .MSH  (Mesh)  **[MAGE Dedicated Format]**
  * .MTL  (Material) **[MAGE Customized Format]**
  * .OBJ  (Wavefront OBJ) **[MAGE Customized Format]**
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

### GUI
* ImGui integration

### Rendering
* AA (for HDR, normal and depth buffer)
  * No AA
  * FXAA (using Max3 tone mapping)
  * MSAA (using Max3 tone mapping)
  * SSAA (using Max3 tone mapping)
* BRDFs (single BRDF/camera)
  * Lambertian
  * Cook-Torrance, Frostbite:
     * D component: Beckmann, Ward-Duer, Blinn-Phong, Trowbridge-Reitz/GGX/GTR2, Berry/GTR1
     * G|V component: Implicit, Ward, Neumann, Ashikhmin-Premoze, Kelemann, Cook Torrance, (Correlated) GGX, Smith GGX, Smith Schlick-GGX, Smith Beckmann, Smith Schlick-Beckmann
     * F component: None, Schlick, Cook-Torrance
* Color spaces
  * All separate colors from material files are expressed in sRGB color space.
  * All separate colors from color pickers (i.e. ImGui) are expressed in sRGB color space.
  * All separate textures (inc. fonts) are expressed in linear or sRGB color space.
  * All internally stored separate colors are expressed in linear color space (for both C++ and HLSL).
    Exceptions: All internally stored separate colors of ImGui are expressed in sRGB color space. 
    All internally stored separate colors of the voexelization are expressed in LogLuv color space.
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
  * Omni lights (shadow cube maps) and spotlights (shadow maps)
* Sky Domes
  * Non-uniform stretching in looking direction
* Sprites
  * Fonts, images, ImGui
* Transparency
  * ~~Alpha-to-Coverage~~ (*not integrated any more*)
  * Single layer Alpha Blending

### Resource Management
* Fonts
* Models
* Shaders: Vertex, Domain, Hull, Geometry, Pixel, Compute
* Textures

### Scene
* Camera
  * Orthographic
  * Perspective
* Light
  * Ambient
  * Directional
  * Omni (with or without shadow cube mapping)
  * Spot (with or without shadow mapping)
* Model
  * Non-emissive
  * Emissive (direct illumination supported using VCT)
* Sprite
  * Image
  * Text
  
### Scripting
* Custom scripts by overriding `mage::BehaviorScript`
* [Standard scripts](standard-scripts.md)

### Transformations
* Scene hierarchies
* Normal transformations
* Sprite transformations
* Texture transformations
