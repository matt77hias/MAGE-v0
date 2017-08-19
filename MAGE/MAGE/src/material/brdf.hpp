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
	 @c Phong,
	 @c ModifiedPhong,
	 @c BlinnPhong, and
	 @c ModifiedBlinnPhong.

	 Emperical BRDFs:
	 @c Ward and
	 @c WardDuer.

	 Physically-based BRDFs:
	 @c CookTorrance.
	 */
	enum struct BRDFType {
		Unknown = 0,
		Lambertian,				// Diffuse component
		Phong,					// Diffuse + Specular component
		ModifiedPhong,			// Diffuse + Specular component
		BlinnPhong,				// Diffuse + Specular component
		ModifiedBlinnPhong,		// Diffuse + Specular component
		Ward,					// Diffuse + Specular component
		WardDuer,				// Diffuse + Specular component
		CookTorrance			// Diffuse + Specular component
	};
}