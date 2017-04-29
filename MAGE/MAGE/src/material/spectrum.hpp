#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declaration
	struct XYZSpectrum;

	/**
	 A struct of RGB color spectra.
	 */
	struct RGBSpectrum final : public XMFLOAT3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a RGB spectrum.
		 */
		RGBSpectrum()
			: RGBSpectrum(0.0f, 0.0f, 0.0f) {}
		
		/**
		 Constructs a RGB spectrum from the given spectrum components.

		 @param[in]		r
						The red component.
		 @param[in]		g
						The green component.
		 @param[in]		b
						The blue component.
		 */
		explicit RGBSpectrum(float r, float g, float b)
			: XMFLOAT3(r, g, b) {}

		/**
		 Constructs a RGB spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to copy.
		 */
		RGBSpectrum(const RGBSpectrum &rgb)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(rgb)) {}
		
		/**
		 Constructs a RGB spectrum by moving the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 */
		RGBSpectrum(RGBSpectrum &&rgb)
			: XMFLOAT3(static_cast< XMFLOAT3 && >(rgb)) {}
		
		/**
		 Constructs a RGB spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to copy.
		 */
		explicit RGBSpectrum(const XYZSpectrum &xyz);

		/**
		 Constructs a RGB spectrum by moving the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 */
		explicit RGBSpectrum(XYZSpectrum &&xyz);

		/**
		 Constructs a RGB spectrum from the given components.

		 @param[in]		vector
						A reference to the components to copy.
		 */
		explicit RGBSpectrum(const XMFLOAT3 &vector)
			: XMFLOAT3(vector) {}

		/**
		 Constructs a RGB spectrum by moving the given components.

		 @param[in]		vector
						A reference to the components to move.
		 */
		explicit RGBSpectrum(XMFLOAT3 &&vector)
			: XMFLOAT3(vector) {}

		/**
		 Destructs this RGB spectrum.
		 */
		~RGBSpectrum() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given RGB spectrum to this RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to copy.
		 @return		A reference to the copy of the given RGB spectrum
						(i.e. this RGB spectrum).
		 */
		RGBSpectrum &operator=(const RGBSpectrum &rgb) = default;

		/**
		 Moves the given RGB spectrum to this RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 @return		A reference to the moved RGB spectrum
						(i.e. this RGB spectrum).
		 */
		RGBSpectrum &operator=(RGBSpectrum &&rgb) = default;
	};

	static_assert(sizeof(RGBSpectrum) == sizeof(XMFLOAT3), "RGBSpectrum/XMFLOAT3 mismatch");

	/**
	 A struct of XYZ color spectra.
	 */
	struct XYZSpectrum final : public XMFLOAT3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a XYZ spectrum.
		 */
		XYZSpectrum()
			: XYZSpectrum(0.0f, 0.0f, 0.0f) {}
		
		/**
		 Constructs a XYZ spectrum from the given spectrum components.

		 @param[in]		x
						The x component.
		 @param[in]		y
						The y component.
		 @param[in]		z
						The z component.
		 */
		explicit XYZSpectrum(float x, float y, float z)
			: XMFLOAT3(x, y, z) {}

		/**
		 Constructs a XYZ spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to copy.
		 */
		XYZSpectrum(const XYZSpectrum &xyz)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(xyz)) {}
		
		/**
		 Constructs a XYZ spectrum by moving the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 */
		XYZSpectrum(XYZSpectrum &&xyz)
			: XMFLOAT3(static_cast< XMFLOAT3 && >(xyz)) {}
		
		/**
		 Constructs a XYZ spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to copy.
		 */
		explicit XYZSpectrum(const RGBSpectrum &rgb);
		
		/**
		 Constructs a XYZ spectrum by moving the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 */
		explicit XYZSpectrum(RGBSpectrum &&rgb);
		
		/**
		 Constructs a XYZ spectrum from the given components.

		 @param[in]		vector
						A reference to the components to copy.
		 */
		explicit XYZSpectrum(const XMFLOAT3 &vector)
			: XMFLOAT3(vector) {}

		/**
		 Constructs a XYZ spectrum by moving the given components.

		 @param[in]		vector
						A reference to the components to move.
		 */
		explicit XYZSpectrum(XMFLOAT3 &&vector)
			: XMFLOAT3(vector) {}

		/**
		 Destructs this XYZ spectrum.
		 */
		~XYZSpectrum() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given XYZ spectrum to this XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to copy.
		 @return		A reference to the copy of the given XYZ spectrum
						(i.e. this XYZ spectrum).
		 */
		XYZSpectrum &operator=(const XYZSpectrum &xyz) = default;

		/**
		 Moves the given XYZ spectrum to this XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 @return		A reference to the moved XYZ spectrum
						(i.e. this XYZ spectrum).
		 */
		XYZSpectrum &operator=(XYZSpectrum &&xyz) = default;
	};

	static_assert(sizeof(XYZSpectrum) == sizeof(XMFLOAT3), "XYZSpectrum/XMFLOAT3 mismatch");
}