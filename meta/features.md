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
  * .SPRITEFONT (Sprite Font) **[MAGE Dedicated Format]**
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
  * .VS   (Variable Script) **[MAGE Dedicated Format]**

### Rendering
* AA
  * No AA
  * FXAA
  * MSAA
  * SSAA
* BRDFs (single BRDF/camera)
  * Lambertian
  * Cook-Torrance, Frostbite:
     * D component: Beckmann, Ward-Duer, Blinn-Phong, Trowbridge-Reitz/GGX/GTR2, Berry/GTR1
     * G|V component: Implicit, Ward, Neumann, Ashikhmin-Premoze, Kelemann, Cook Torrance, (Correlated) GGX, Smith GGX, Smith Schlick-GGX, Smith Beckmann, Smith Schlick-Beckmann
     * F component: None, Schlick, Cook-Torrance
* Color spaces
  * All separate colors and textures with color data are expressed in sRGB space.
  * All light calculations are performed in linear space.
  * sRGB colors are converted from gamma to linear space by the CPU (*Frostbite*).
  * sRGB textures are converted from gamma to linear space by the GPU hardware support (ensures correct filtering and blending).
  * Optional custom gamma correction before presenting (i.e. brightness adjustment)
* Culling
  * Non-hierarchical
* Depth buffer
  * Standard Z-depth
  * Reversed Z-depth
  * 32bit float for depth buffer
  * 16bit unorm|32bit float for shadow (cube) maps
* Lighting
  * Optional light interaction for materials
  * Single pass for all lights (incl. shadow mapping)
  * Physically-based and smooth angular attenuation (*Frostbite*)
  * Physically-based and smooth distance attenuation (*Frostbite*)
  * Exponential fog with custom density (avoids popping artifacts)
  * HDR
* Normal Mapping
  * Tangent-space (without relying on precomputed tangents and bitangents)
  * ~~Object-space~~ (*not supported any more*)
* Render Layers (multiple render layers/camera)
  * Bounding volumes
  * Wireframe
* Render Modes (single render mode/camera)
  * Forward
  * Deferred
  * Various material and component visualizations
* Shadow Mapping
  * Optional occluding behavior for models
  * Support for both opaque and transparent models
  * Depth and slope scaled biasing
  * PCF filtering
  * Omni lights and spotlights
* Sky Domes
  * Non-uniform stretching in looking direction
* Sprites
* Tone Mapping
  * AA resolving (SSAA, MSAA, FXAA): Max3
  * Back buffer: ACES, Reinhard, Uncharted
* Transparency
  * ~~Alpha-to-Coverage~~ (*not supported any more*)
  * Single layer Alpha Blending

### Resource Management
* Fonts
* Models
* Shaders: Vertex, Domain, Hull, Geometry, Pixel, Compute
* Textures
* Variables Scripts

### Scene
* Camera
  * Orthographic
  * Perspective
* Fog
  * Linear
* Light
  * Ambient
  * Directional
  * Omni (with or without shadow cube mapping)
  * Spot (with or without shadow mapping)
* Model
* Sky
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
