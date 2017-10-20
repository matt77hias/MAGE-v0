# Features

### Display
* Configurable display modes
  * MSAA samples
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
  * .BMP  (Windows Bitmap Format)
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
  * ~~MSAA~~~ (*not supported any more (HDR pipeline)*)
* BRDFs (single BRDF/camera)
  * old material pipeline:
    * Lambertian
    * Phong
    * Modified-Phong
    * Blinn-Phong
    * Modified Blinn-Phong
    * Ward
    * Ward-Duer
    * Cook-Torrance (F: Schlick, D: Beckmann, G: Cook-Torrance)
  * new material pipeline:
   * Lambertian
   * Cook-Torrance, Disney:
     * D component: 
        * Beckmann, 
        * Ward-Duer, 
        * Blinn-Phong, 
        * Trowbridge-Reitz/GGX/GTR2
        * Berry/GTR1
     * G|V component: 
        * Implicit
        * Ward
        * Neumann
        * Ashikhmin-Premoze
        * Kelemann
        * Cook Torrance
        * Smith GGX
        * Smith Schlick-GGX
        * Smith Beckmann
        * Smith Schlick-Beckmann
     * F component: 
        * None
        * Schlick
        * Cook-Torrance
* Culling
  * Non-hierarchical
* Gamma Correction
  * All light calculations are performed in linear space.
* Lighting
  * Single pass for all lights (incl. shadow mapping)
  * Linear fog (avoids popping artifacts)
  * HDR
* Normal Mapping
  * Tangent-space (without relying on precomputed tangents and bitangents)
  * ~~Object-space~~ (*not supported any more*)
* Optional occluding behavior for models
* Optional light interaction for materials
* Render Layers (multiple render layers/camera)
  * Bounding volumes
  * Wireframe
* Render Modes (single render mode/camera)
  * Forward
  * Deferred
  * Various material and component visualizations
* Reversed Z-depth
  * 32bit float for depth buffer
  * 16bit unorm|32bit float for shadow (cube) maps
* Shadow Mapping
  * Support for both opaque and transparent models
  * Depth and slope scaled biasing
  * PCF filtering
  * Omni lights and spotlights
* Sky Domes
* Sprites
* Tone Mapping
  * ACES
  * Reinhard
  * Uncharted
* Transparency
  * ~~Alpha-to-Coverage~~ (*not supported any more (HDR pipeline)*)
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
  * Omni
  * Spot
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
