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
	 An enumeration of the different Bidirectional Reflection
	 Distribution Functions (BRDFs).

	 This contains:
	 @c Unknown,
	 @c Lambertian,
	 @c BlinnPhong,
	 @c CookTorrance,
	 @c Frostbite, and
	 @c WardDuer.
	 */
	enum class BRDFType : U8 {
		Unknown      = 0,
		Lambertian   = 1,
		BlinnPhong   = 2,
		CookTorrance = 3,
		Frostbite    = 4,
		WardDuer     = 5
	};
}