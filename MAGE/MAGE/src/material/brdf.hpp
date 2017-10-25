#pragma once

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
	enum struct BRDFType {
		Unknown = 0,
		Lambertian,
		BlinnPhong,
		CookTorrance,
		Frostbite,
		WardDuer
	};
}