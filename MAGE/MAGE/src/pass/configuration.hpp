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
	 @c DiffuseColor,
	 @c DiffuseReflectivity,
	 @c DiffuseReflectivityTexture,
	 @c SpecularColor,
	 @c SpecularReflectivity,
	 @c SpecularReflectivityTexture,
	 @c NormalTexture,
	 @c UVTexture,
	 @c Distance,
	 @c ShadingNormal, and
	 @c TSNMShadingNormal.
	 */
	enum struct RenderMode {
		None = 0,                    // No shading.
		Default,                     // The normal shading (with lighting).
		Solid,                       // Solid white shading (with lighting).
		DiffuseColor,                // The diffuse color (reflectivity and reflectivity texture) (without lighting).
		DiffuseReflectivity,         // The diffuse reflectivity (without lighting).
		DiffuseReflectivityTexture,  // The diffuse reflectivity texture (without lighting).
		SpecularColor,               // The specular color (reflectivity and reflectivity texture) (without lighting).
		SpecularReflectivity,        // The specular reflectivity (without lighting).
		SpecularReflectivityTexture, // The specular reflectivity texture (without lighting).
		NormalTexture,               // The normal texture (without lighting).
		UVTexture,                   // The UV parametrization texture (without lighting). 
		Distance,                    // The distance towards the eye.
		ShadingNormal,               // The shading normal.
		TSNMShadingNormal            // The TSNM shading normal.
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