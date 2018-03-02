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
namespace mage {

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
}