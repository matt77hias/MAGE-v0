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
		 Constructs a RGB spectrum from the given spectrum components.

		 @param[in]		rgb
						The red, green and blue component.
		 */
		explicit RGBSpectrum(float rgb = 0.0f) noexcept
			: RGBSpectrum(rgb, rgb, rgb) {}
		
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
		RGBSpectrum(const RGBSpectrum &rgb) = default;
		
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
		 Constructs a XYZ spectrum from the given spectrum components.

		 @param[in]		xyz
						The x, y and z component.
		 */
		explicit XYZSpectrum(float xyz = 0.0f) noexcept
			: XYZSpectrum(xyz, xyz, xyz) {}
		
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
		XYZSpectrum(const XYZSpectrum &xyz) = default;
		
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

	//-------------------------------------------------------------------------
	// RGBASpectrum
	//-------------------------------------------------------------------------

	/**
	 A struct of RGBA color spectra.
	 */
	struct RGBASpectrum final : public XMFLOAT4 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a RGBA spectrum from the given spectrum components.

		 @param[in]		rgba
						The red, green and blue and alpha component.
		 */
		explicit RGBASpectrum(float rgba = 0.0f) noexcept
			: RGBASpectrum(rgba, rgba, rgba, rgba) {}
		
		/**
		 Constructs a RGBA spectrum from the given spectrum components.

		 @param[in]		r
						The red component.
		 @param[in]		g
						The green component.
		 @param[in]		b
						The blue component.
		 @param[in]		a
						The alpha component.
		 */
		explicit RGBASpectrum(float r, float g, float b, float a = 1.0f) noexcept
			: XMFLOAT4(r, g, b, a) {}

		/**
		 Constructs a RGBA spectrum from the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to copy.
		 */
		RGBASpectrum(const RGBASpectrum &rgba) = default;
		
		/**
		 Constructs a RGBA spectrum by moving the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to move.
		 */
		RGBASpectrum(RGBASpectrum &&rgba) noexcept = default;
		
		/**
		 Constructs a RGBA spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the rgb spectrum.
		 @param[in]		a
						The alpha component.
		 */
		explicit RGBASpectrum(const RGBSpectrum &rgb, float a = 1.0f) noexcept
			: RGBASpectrum(rgb.x, rgb.y, rgb.z, a) {}

		/**
		 Constructs a RGBA spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the xyz spectrum.
		 @param[in]		a
						The alpha component.
		 */
		explicit RGBASpectrum(const XYZSpectrum &xyz, float a = 1.0f) noexcept 
			: RGBASpectrum(RGBSpectrum(xyz), a) {}

		/**
		 Constructs a RGBA spectrum from the given components.

		 @param[in]		v
						A reference to the components to copy.
		 */
		explicit RGBASpectrum(const XMFLOAT3 &v, float a = 1.0f) noexcept
			: RGBASpectrum(v.x, v.y, v.z, a) {}

		/**
		 Constructs a RGBA spectrum from the given components.

		 @param[in]		v
						A reference to the components to copy.
		 */
		explicit RGBASpectrum(const XMFLOAT4 &v) noexcept
			: XMFLOAT4(v) {}

		/**
		 Constructs a RGBA spectrum by moving the given components.

		 @param[in]		v
						A reference to the components to move.
		 */
		explicit RGBASpectrum(XMFLOAT4 &&v) noexcept
			: XMFLOAT4(std::move(v)) {}

		/**
		 Destructs this RGBA spectrum.
		 */
		~RGBASpectrum() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given RGBA spectrum to this RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to copy.
		 @return		A reference to the copy of the given RGBA spectrum
						(i.e. this RGBA spectrum).
		 */
		RGBASpectrum &operator=(const RGBASpectrum &rgba) = default;

		/**
		 Moves the given RGBA spectrum to this RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to move.
		 @return		A reference to the moved RGBA spectrum
						(i.e. this RGBA spectrum).
		 */
		RGBASpectrum &operator=(RGBASpectrum &&rgba) = default;
	};

	static_assert(sizeof(RGBASpectrum) == sizeof(XMFLOAT4), "RGBASpectrum/XMFLOAT4 mismatch");
}