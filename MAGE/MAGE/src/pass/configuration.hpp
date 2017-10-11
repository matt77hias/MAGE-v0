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
	 @c DepthAndForward,
	 @c Deferred,
	 @c Solid, 
	 @c DepthAndSolid,
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
	enum struct RenderMode {
		// Rendering
		None = 0,                    // No shading.
		Forward,                     // Forward shading.
		DepthAndForward,             // Depth pass + Forward shading.
		Deferred,					 // Deferred shading.
		Solid,                       // Solid shading.
		DepthAndSolid,               // Depth pass + Solid shading.               
		
		// Material
		BaseColor,					 // Base Color (coefficient + texture).
		BaseColorCoefficient,        // Base Color coefficient.
		BaseColorTexture,            // Base Color texture.
		Material,                    // Material (coefficient + texture).
		MaterialCoefficient,         // Material coefficient.
		MaterialTexture,             // Material texture.
		NormalTexture,               // Normal texture.
		
		UVTexture,                   // UV parametrization texture.
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