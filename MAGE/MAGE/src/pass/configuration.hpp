#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of the different render modes.

	 This contains:
	 @c None,
	 @c Default,
	 @c Solid,
	 @c DiffuseTexture,
	 @c UVTexture,
	 @c ShadingNormal,
	 @c TSNMShadingNormal, and
	 @c Distance.
	 */
	enum struct RenderMode {
		None = 0,			// No shading.
		Default,			// The normal shading (with lighting).
		Solid,				// Solid white shading (with lighting).
		DiffuseTexture,		// The diffuse texture (without lighting).
		UVTexture,			// The UV parametrization texture (without lighting). 
		ShadingNormal,		// The shading normal.
		TSNMShadingNormal,	// The TSNM shading normal.
		Distance			// The distance towards the eye.
	};

	/**
	 An enumeration of the different render layers.

	 This contains:
	 @c None,
	 @c Wireframe, and
	 @c AABB.
	 */
	enum struct RenderLayer {
		None      = 0,		// No layer.
		Wireframe = 1,		// Wirframe layer.
		AABB      = 2,		// AABB layer.
	};
}