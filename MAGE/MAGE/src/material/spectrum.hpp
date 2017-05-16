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

	//-------------------------------------------------------------------------
	// RGBSpectrum
	//-------------------------------------------------------------------------

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
		RGBSpectrum() noexcept
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
		explicit RGBSpectrum(float r, float g, float b) noexcept
			: XMFLOAT3(r, g, b) {}

		/**
		 Constructs a RGB spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to copy.
		 */
		RGBSpectrum(const RGBSpectrum &rgb) noexcept = default;
		
		/**
		 Constructs a RGB spectrum by moving the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 */
		RGBSpectrum(RGBSpectrum &&rgb) noexcept = default;
		
		/**
		 Constructs a RGB spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to copy.
		 */
		explicit RGBSpectrum(const XYZSpectrum &xyz) noexcept;

		/**
		 Constructs a RGB spectrum by moving the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 */
		explicit RGBSpectrum(XYZSpectrum &&xyz) noexcept;

		/**
		 Constructs a RGB spectrum from the given components.

		 @param[in]		v
						A reference to the components to copy.
		 */
		explicit RGBSpectrum(const XMFLOAT3 &v) noexcept
			: XMFLOAT3(v) {}

		/**
		 Constructs a RGB spectrum by moving the given components.

		 @param[in]		v
						A reference to the components to move.
		 */
		explicit RGBSpectrum(XMFLOAT3 &&v) noexcept
			: XMFLOAT3(std::move(v)) {}

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
		RGBSpectrum &operator=(const RGBSpectrum &rgb) noexcept = default;

		/**
		 Moves the given RGB spectrum to this RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 @return		A reference to the moved RGB spectrum
						(i.e. this RGB spectrum).
		 */
		RGBSpectrum &operator=(RGBSpectrum &&rgb) noexcept = default;
	};

	static_assert(sizeof(RGBSpectrum) == sizeof(XMFLOAT3), "RGBSpectrum/XMFLOAT3 mismatch");

	//-------------------------------------------------------------------------
	// XYZSpectrum
	//-------------------------------------------------------------------------

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
		XYZSpectrum() noexcept
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
		explicit XYZSpectrum(float x, float y, float z) noexcept
			: XMFLOAT3(x, y, z) {}

		/**
		 Constructs a XYZ spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to copy.
		 */
		XYZSpectrum(const XYZSpectrum &xyz) noexcept = default;
		
		/**
		 Constructs a XYZ spectrum by moving the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 */
		XYZSpectrum(XYZSpectrum &&xyz) noexcept = default;
		
		/**
		 Constructs a XYZ spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to copy.
		 */
		explicit XYZSpectrum(const RGBSpectrum &rgb) noexcept;
		
		/**
		 Constructs a XYZ spectrum by moving the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 */
		explicit XYZSpectrum(RGBSpectrum &&rgb) noexcept;
		
		/**
		 Constructs a XYZ spectrum from the given components.

		 @param[in]		v
						A reference to the components to copy.
		 */
		explicit XYZSpectrum(const XMFLOAT3 &v) noexcept
			: XMFLOAT3(v) {}

		/**
		 Constructs a XYZ spectrum by moving the given components.

		 @param[in]		v
						A reference to the components to move.
		 */
		explicit XYZSpectrum(XMFLOAT3 &&v) noexcept
			: XMFLOAT3(std::move(v)) {}

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
		XYZSpectrum &operator=(const XYZSpectrum &xyz) noexcept = default;

		/**
		 Moves the given XYZ spectrum to this XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 @return		A reference to the moved XYZ spectrum
						(i.e. this XYZ spectrum).
		 */
		XYZSpectrum &operator=(XYZSpectrum &&xyz) noexcept = default;
	};

	static_assert(sizeof(XYZSpectrum) == sizeof(XMFLOAT3), "XYZSpectrum/XMFLOAT3 mismatch");
}