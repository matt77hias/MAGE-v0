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
* .DDS (texture)
* .MDL (model)
* .MSH (mesh)
* .MTL (material)
* .OBJ (model/mesh)
* .SPRITEFONT (font)
* .VS (variable script)

### Rendering
* AA
  * MSAA
* BRDFs (single BRDF/camera)
  * Lambertian
  * Phong
  * Modified-Phong
  * Blinn-Phong
  * Modified Blinn-Phong
  * Ward
  * Ward-Duer
  * Cook-Torrance (F: Schlick, D: Beckmann)
* Culling
 * Non-hierarchical
* Lighting
 * Single pass for all lights which require and do not require shadow mapping
* Normal Mapping
  * Tangent-space
  * ~~Object-space~~ (*not supported any more*)
  * No precomputed tangent and bitangent vectors
* Optional occluding behavior for models
* Optional light interaction for materials
* Render Layers (multiple render layers/camera)
 * Bounding volumes
 * Wireframe
* Render Modes (single render mode/camera)
 * Forward (with optional early Depth pass)
 * Deferred
 * Various material and component visualizations
* Shadow Mapping
  * Support for both opaque and transparent models
  * Depth and slope biasing
  * PCF filtering
  * Omni lights and spotlights
* Sprites
* Transparency
 * Alpha-to-Coverage (for both forward and deferred shading)
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
* Sptite
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
