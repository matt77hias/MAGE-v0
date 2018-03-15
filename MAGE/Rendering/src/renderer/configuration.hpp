#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\scalar_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// AADescriptor
	//-------------------------------------------------------------------------
	#pragma region

	enum class AADescriptor : U8 {
		None = 0,
		FXAA,
		MSAA_2x,
		MSAA_4x,
		MSAA_8x,
		SSAA_2x,
		SSAA_3x,
		SSAA_4x,
	};

	[[nodiscard]]
	constexpr AADescriptor RetrieveAADescriptor(size_t desc) noexcept {

		switch (desc) {
		
		case static_cast< size_t >(AADescriptor::FXAA):
			return AADescriptor::FXAA;
		case static_cast< size_t >(AADescriptor::MSAA_2x):
			return AADescriptor::MSAA_2x;
		case static_cast< size_t >(AADescriptor::MSAA_4x):
			return AADescriptor::MSAA_4x;
		case static_cast< size_t >(AADescriptor::MSAA_8x):
			return AADescriptor::MSAA_8x;
		case static_cast< size_t >(AADescriptor::SSAA_2x):
			return AADescriptor::SSAA_2x;
		case static_cast< size_t >(AADescriptor::SSAA_3x):
			return AADescriptor::SSAA_3x;
		case static_cast< size_t >(AADescriptor::SSAA_4x):
			return AADescriptor::SSAA_4x;
		default:
			return AADescriptor::None;
		}
	}

	[[nodiscard]]
	constexpr U32 GetSampleMultiplier(AADescriptor desc) noexcept {

		switch (desc) {

		case AADescriptor::MSAA_2x:
			return 2u;
		case AADescriptor::MSAA_4x:
			return 4u;
		case AADescriptor::MSAA_8x:
			return 8u;
		default:
			return 1u;

		}
	}

	[[nodiscard]]
	constexpr U32 GetResolutionMultiplier(AADescriptor desc) noexcept {

		switch (desc) {

		case AADescriptor::SSAA_2x:
			return 2u;
		case AADescriptor::SSAA_3x:
			return 3u;
		case AADescriptor::SSAA_4x:
			return 4u;
		default:
			return 1u;

		}
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// RenderMode
	//-------------------------------------------------------------------------
	#pragma region

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
	 @c FalseColor_Depth,
	 @c FalseColor_Distance, and
	 @c FalseColor_UV.
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
		FalseColor_Depth,
		FalseColor_Distance,
		FalseColor_UV
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// RenderLayer
	//-------------------------------------------------------------------------
	#pragma region

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

	#pragma endregion

	//-------------------------------------------------------------------------
	// BRDFType
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of the different Bidirectional Reflection Distribution 
	 Functions (BRDFs).

	 This contains:
	 @c Default,
	 @c Lambertian,
	 @c BlinnPhong,
	 @c CookTorrance,
	 @c Frostbite, and
	 @c WardDuer.
	 */
	enum class BRDFType : U8 {
		Default      = 0,
		Lambertian   = 1,
		BlinnPhong   = 2,
		CookTorrance = 3,
		Frostbite    = 4,
		WardDuer     = 5
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// FalseColor
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of the different false colors.
	 
	 This contains:
	 
	 @c ConstantColor,
	 @c ConstantColorTexture,
	 @c BaseColor,
	 @c BaseColorCoefficient,
	 @c BaseColorTexture,
	 @c Material,
	 @c MaterialCoefficient,
	 @c MaterialTexture,
	 @c Roughness,
	 @c RoughnessCoefficient,
	 @c RoughnessTexture,
	 @c Metalness,
	 @c MetalnessCoefficient,
	 @c MetalnessTexture,
	 @c ShadingNormal,
	 @c TSNMShadingNormal,
	 @c Depth,
	 @c Distance, and
	 @c UV.
	 */
	enum class FalseColor : U8 {
		ConstantColor = 0,
		ConstantColorTexture,
		BaseColor,
		BaseColorCoefficient,
		BaseColorTexture,
		Material,
		MaterialCoefficient,
		MaterialTexture,
		Roughness,
		RoughnessCoefficient,
		RoughnessTexture,
		Metalness,
		MetalnessCoefficient,
		MetalnessTexture,
		ShadingNormal,
		TSNMShadingNormal,
		Depth,
		Distance,
		UV
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// FalseColor
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of the different Tone Mapping Functions.

	 This contains:
	 @c Default,
	 @c ACESFilmic,
	 @c Reinhard, and
	 @c Uncharted.
	 */
	enum class ToneMapping : U8 {
		Default    = 0,
		ACESFilmic = 1,
		Reinhard   = 2,
		Uncharted  = 3
	};

	#pragma endregion
}