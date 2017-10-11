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
	 @c Lambertian, and
	 @c CookTorrance.
	 */
	enum struct BRDFType {
		Unknown = 0,
		Lambertian,
		CookTorrance
	};
}