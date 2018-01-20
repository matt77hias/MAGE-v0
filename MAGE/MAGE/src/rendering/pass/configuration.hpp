#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of the different render modes.

	 This contains:
	 @c None,
	 @c Forward, 
	 @c Deferred,
	 @c Solid, 
	 @c BaseColor,
	 @c BaseColorCoefficient,
	 @c BaseColorTexture,
	 @c Material,
	 @c MaterialCoefficient,
	 @c MaterialTexture,
	 @c NormalTexture,
	 @c UVTexture,
	 @c Distance,
	 @c ShadingNormal, and
	 @c TSNMShadingNormal.
	 */
	enum class RenderMode : U8 {
		// Rendering
		None                 = 0,  // No shading.
		Forward              = 1,  // Forward shading.
		Deferred             = 2,  // Deferred shading.
		Solid                = 3,  // Solid shading.             
		
		// Material
		BaseColor            = 4,  // Base Color (coefficient + texture).
		BaseColorCoefficient = 5,  // Base Color coefficient.
		BaseColorTexture     = 6,  // Base Color texture.
		Material             = 7,  // Material (coefficient + texture).
		MaterialCoefficient  = 8,  // Material coefficient.
		MaterialTexture      = 9,  // Material texture.
		NormalTexture        = 10, // Normal texture.
		
		UVTexture            = 11, // UV parametrization texture.
		Distance             = 12, // The distance towards the eye.
		ShadingNormal        = 13, // The shading normal.
		TSNMShadingNormal    = 14  // The TSNM shading normal.
	};

	/**
	 An enumeration of the different render layers.

	 This contains:
	 @c None,
	 @c Wireframe, and
	 @c AABB.
	 */
	enum class RenderLayer : U32 {
		None      = 0, // No layer.
		Wireframe = 1, // Wirframe layer.
		AABB      = 2, // AABB layer.
	};
}