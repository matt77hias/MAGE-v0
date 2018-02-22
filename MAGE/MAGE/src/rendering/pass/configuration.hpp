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
	 @c VoxelGrid,
	 @c FalseColor_BaseColor,
	 @c FalseColor_BaseColorCoefficient,
	 @c FalseColor_BaseColorTexture,
	 @c FalseColor_Material,
	 @c FalseColor_MaterialCoefficient,
	 @c FalseColor_MaterialTexture,
	 @c FalseColor_Roughness,
	 @c FalseColor_RoughnessCoefficient,
	 @c FalseColor_RoughnessTexture,
	 @c FalseColor_Metalness,
	 @c FalseColor_MetalnessCoefficient,
	 @c FalseColor_MetalnessTexture,
	 @c FalseColor_ShadingNormal,
	 @c FalseColor_TSNMShadingNormal,
	 @c FalseColor_UVTexture,
	 @c FalseColor_Depth, and
	 @c FalseColor_Distance.
	 */
	enum class RenderMode : U8 {
		// Rendering
		None = 0,
		Forward,
		Deferred,
		Solid,            
		
		// Voxelization visualization
		VoxelGrid,

		// False color visualization
		FalseColor_BaseColor,
		FalseColor_BaseColorCoefficient,
		FalseColor_BaseColorTexture,
		FalseColor_Material,
		FalseColor_MaterialCoefficient,
		FalseColor_MaterialTexture,
		FalseColor_Roughness,
		FalseColor_RoughnessCoefficient,
		FalseColor_RoughnessTexture,
		FalseColor_Metalness,
		FalseColor_MetalnessCoefficient,
		FalseColor_MetalnessTexture,
		FalseColor_ShadingNormal,
		FalseColor_TSNMShadingNormal,
		FalseColor_UVTexture,
		FalseColor_Depth,
		FalseColor_Distance
	};

	/**
	 An enumeration of the different render layers.

	 This contains:
	 @c None,
	 @c Wireframe, and
	 @c AABB.
	 */
	enum class RenderLayer : U32 {
		None = 0,  // No layer.
		Wireframe, // Wirframe layer.
		AABB,      // AABB layer.
	};
}