# Iterations

## Current iteration' TODOs
* Sky Domes (WIP)
* Shadow Mapping (WIP)
  * Directional lights
* SSAO, HBAO
* Voxel Cone Tracing
* Tiled and Clustered Shading
* Billboarding (Ry camera-dependent)
* Particles (Rx+Ry+Rz camera-dependent)
* Height maps (alpha of normal map) + terrains
* Environment Mapping

## Further iterations
* Collision Detection, Ray Casting, Picking
* Physics
* Audio
* Animation
  * Each animated model has an associated mesh and skeleton. The skeleton is hierarchy of bones with child-parent relationships and *bone-to-parent* transformation matrices. Furthermore, each bone has an *bind-to-bone* transformation matrix expressing the relationship between the mesh and skeleton.
  * Each animated model has *A* animation clips (e.g. running, jumping) wich have *K* associated key frames. Each key frame has a timestamp and a *bone-to-parent* transformation matrix. For a given animation clip at a given timestamp, the *bone-to-parent* transformation matrices of the closest key frames need to be interpolated (e.g. lerp or slerp). 
  * The vertices of the mesh contain at most 4 weights and indices to a buffer containing all *bind-to-root* transformation matrices. The vertex position and normal are calculated as a weighted sum (vertex blending). 
* Network
