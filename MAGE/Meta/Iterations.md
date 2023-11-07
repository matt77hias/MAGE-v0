# Iterations

## Current iteration' TODOs
* Depth-of-Field (WIP: Bokeh)
* Post-processing: God rays
* Displacement Maps, Parallax Occlusion Maps
* TAA
* Cascaded and Variance Shadow Mapping
* SSAO: GBuffer -> low resolution SSAO map -> edge preserving blur (k times) -> Deferred Shading
* SSR
* Tiled and Clustered Shading
* Billboarding (Ry camera-dependent)
* Particles (Rx+Ry+Rz camera-dependent)
* Environment Mapping
* SSS

## Further iterations
* Collision Detection, Ray Casting, Picking
* Physics
* Audio
* Animation
  * Each animated model has an associated mesh and skeleton. The skeleton is a hierarchy of bones with child-parent relationships and *bone-to-parent* transformation matrices. Furthermore, each bone has a *bind-to-bone* transformation matrix expressing the relationship between the mesh and the bones of the skeleton.
  * Each animated model has *A* animation clips (e.g. running, jumping), wich have *K* associated key frames. Each key frame has a timestamp and a *bone-to-parent* transformation matrix for each bone. For a given animation clip at a given timestamp, the *bone-to-parent* transformation matrices of the closest key frames need to be interpolated (e.g. lerp or slerp). 
  * The vertices of the mesh contain at most 4 weights and 4 indices to a buffer containing all *bind-to-root* transformation matrices. The vertex position and normal are calculated as a weighted sum (vertex blending).
  * The *bind-to-parent* and *bone-to-parent* matrices contain only translation, rotation and uniform scaling components to avoid the need for handling normals differently while transforming.
* Network

<p align="center">Copyright © 2016-2024 Matthias Moulin. All Rights Reserved.</p>