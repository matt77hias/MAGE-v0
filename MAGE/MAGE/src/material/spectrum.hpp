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

	//-------------------------------------------------------------------------
	// sRGB <-> Linear
	//-------------------------------------------------------------------------

	/**
	 Converts the given spectrum from linear to sRGB space.

	 @param[in]		linear
					The spectrum in linear space.
	 @return		The spectrum in sRGB space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	inline const XMVECTOR XM_CALLCONV LinearToSRGB(FXMVECTOR linear) noexcept {
		// Frostbite's conversion
		static const float exp = 1.0f / 2.4f;
		
		const XMVECTOR low  = linear * 12.92f;
		const XMVECTOR high = 1.055f * XMVectorPow(linear, XMVectorReplicate(exp))
			                - XMVectorReplicate(0.055f);
		const XMVECTOR comp = XMVectorLessOrEqual(linear, XMVectorReplicate(0.0031308f));

		return XMVectorSet(
			XMVectorGetX(comp) ? XMVectorGetX(low) : XMVectorGetX(high),
			XMVectorGetY(comp) ? XMVectorGetY(low) : XMVectorGetY(high),
			XMVectorGetZ(comp) ? XMVectorGetZ(low) : XMVectorGetZ(high),
			XMVectorGetW(linear)
		);
	}

	/**
	 Converts the given spectrum from sRGB to linear space.

	 @param[in]		srgb
					The spectrum in sRGB space.
	 @return		The spectrum in linear space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	inline const XMVECTOR XM_CALLCONV SRGBToLinear(FXMVECTOR srgb) noexcept {
		// Frostbite's conversion
		static const float mlow  = 1.0f / 12.92f;
		static const float mhigh = 1.0f / 1.055f;

		const XMVECTOR low  = srgb * mlow;
		const XMVECTOR high = XMVectorPow(
			                      mhigh * (srgb + XMVectorReplicate(0.055f)),
			                      XMVectorReplicate(2.4f)
		                      );
		const XMVECTOR comp = XMVectorLessOrEqual(srgb, XMVectorReplicate(0.04045f));

		return XMVectorSet(
			XMVectorGetX(comp) ? XMVectorGetX(low) : XMVectorGetX(high),
			XMVectorGetY(comp) ? XMVectorGetY(low) : XMVectorGetY(high),
			XMVectorGetZ(comp) ? XMVectorGetZ(low) : XMVectorGetZ(high),
			XMVectorGetW(srgb)
		);
	}

	//-------------------------------------------------------------------------
	// RGBSpectrum
	//-------------------------------------------------------------------------

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
		 Constructs a RGB spectrum from the given spectrum components.

		 @param[in]		rgb
						The red, green and blue component.
		 */
		explicit RGBSpectrum(F32 rgb = 0.0f) noexcept
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
		explicit RGBSpectrum(F32 r, F32 g, F32 b) noexcept
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
		 @return		A reference to the copy of the given RGB spectrum (i.e. 
						this RGB spectrum).
		 */
		RGBSpectrum &operator=(const RGBSpectrum &rgb) = default;

		/**
		 Moves the given RGB spectrum to this RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 @return		A reference to the moved RGB spectrum (i.e. this RGB 
						spectrum).
		 */
		RGBSpectrum &operator=(RGBSpectrum &&rgb) = default;
	};

	static_assert(sizeof(RGBSpectrum) == sizeof(XMFLOAT3), 
		"RGBSpectrum/XMFLOAT3 mismatch");

	/**
	 Converts the given spectrum from linear to sRGB space.

	 @param[in]		linear
					The spectrum in linear space.
	 @return		The spectrum in sRGB space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	inline const RGBSpectrum LinearToSRGB(const RGBSpectrum &linear) noexcept {
		RGBSpectrum result;
		XMStoreFloat3(&result, LinearToSRGB(XMLoadFloat3(&linear)));
		return result;
	}

	/**
	 Converts the given spectrum from sRGB to linear space.

	 @param[in]		srgb
					The spectrum in sRGB space.
	 @return		The spectrum in linear space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	inline const RGBSpectrum SRGBToLinear(const RGBSpectrum &srgb) noexcept {
		RGBSpectrum result;
		XMStoreFloat3(&result, SRGBToLinear(XMLoadFloat3(&srgb)));
		return result;
	}

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
		explicit XYZSpectrum(F32 xyz = 0.0f) noexcept
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
		explicit XYZSpectrum(F32 x, F32 y, F32 z) noexcept
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
		 @return		A reference to the copy of the given XYZ spectrum (i.e. 
						this XYZ spectrum).
		 */
		XYZSpectrum &operator=(const XYZSpectrum &xyz) = default;

		/**
		 Moves the given XYZ spectrum to this XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 @return		A reference to the moved XYZ spectrum (i.e. this XYZ 
						spectrum).
		 */
		XYZSpectrum &operator=(XYZSpectrum &&xyz) = default;
	};

	static_assert(sizeof(XYZSpectrum) == sizeof(XMFLOAT3),
		"XYZSpectrum/XMFLOAT3 mismatch");

	//-------------------------------------------------------------------------
	// RGBASpectrum
	//-------------------------------------------------------------------------

	// Forward declaration
	struct XYZASpectrum;

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
		explicit RGBASpectrum(F32 rgba = 0.0f) noexcept
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
		explicit RGBASpectrum(F32 r, F32 g, F32 b, F32 a = 1.0f) noexcept
			: XMFLOAT4(r, g, b, a) {}

		/**
		 Constructs a RGBA spectrum from the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to copy.
		 */
		RGBASpectrum(const RGBASpectrum &rgba) noexcept = default;
		
		/**
		 Constructs a RGBA spectrum by moving the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to move.
		 */
		RGBASpectrum(RGBASpectrum &&rgba) noexcept = default;
		
		/**
		 Constructs a RGBA spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum.
		 @param[in]		a
						The alpha component.
		 */
		explicit RGBASpectrum(const RGBSpectrum &rgb, F32 a = 1.0f) noexcept
			: RGBASpectrum(rgb.x, rgb.y, rgb.z, a) {}

		/**
		 Constructs a RGBA spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum.
		 @param[in]		a
						The alpha component.
		 */
		explicit RGBASpectrum(const XYZSpectrum &xyz, F32 a = 1.0f) noexcept 
			: RGBASpectrum(RGBSpectrum(xyz), a) {}

		/**
		 Constructs a RGBA spectrum from the given XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum.
		 */
		explicit RGBASpectrum(const XYZASpectrum &xyza) noexcept;

		/**
		 Constructs a RGBA spectrum from the given components.

		 @param[in]		v
						A reference to the components to copy.
		 @param[in]		a
						The alpha component.
		 */
		explicit RGBASpectrum(const XMFLOAT3 &v, F32 a = 1.0f) noexcept
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
		 @return		A reference to the moved RGBA spectrum (i.e. this RGBA 
						spectrum).
		 */
		RGBASpectrum &operator=(RGBASpectrum &&rgba) = default;
	};

	static_assert(sizeof(RGBASpectrum) == sizeof(XMFLOAT4), 
		"RGBASpectrum/XMFLOAT4 mismatch");
	
	/**
	 Converts the given spectrum from linear to sRGB space.

	 @param[in]		linear
					The spectrum in linear space.
	 @return		The spectrum in sRGB space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	inline const RGBASpectrum LinearToSRGB(const RGBASpectrum &linear) noexcept {
		RGBASpectrum result;
		XMStoreFloat4(&result, LinearToSRGB(XMLoadFloat4(&linear)));
		return result;
	}

	/**
	 Converts the given spectrum from sRGB to linear space.

	 @param[in]		srgb
					The spectrum in sRGB space.
	 @return		The spectrum in linear space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	inline const RGBASpectrum SRGBToLinear(const RGBASpectrum &srgb) noexcept {
		RGBASpectrum result;
		XMStoreFloat4(&result, SRGBToLinear(XMLoadFloat4(&srgb)));
		return result;
	}

	//-------------------------------------------------------------------------
	// XYZASpectrum
	//-------------------------------------------------------------------------

	/**
	 A struct of XYZA color spectra.
	 */
	struct XYZASpectrum final : public XMFLOAT4 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a XYZA spectrum from the given spectrum components.

		 @param[in]		xyza
						The x, y and z and alpha component.
		 */
		explicit XYZASpectrum(F32 xyza = 0.0f) noexcept
			: XYZASpectrum(xyza, xyza, xyza, xyza) {}
		
		/**
		 Constructs a XYZA spectrum from the given spectrum components.

		 @param[in]		x
						The x component.
		 @param[in]		y
						The y component.
		 @param[in]		z
						The z component.
		 @param[in]		a
						The alpha component.
		 */
		explicit XYZASpectrum(F32 x, F32 y, F32 z, F32 a = 1.0f) noexcept
			: XMFLOAT4(x, y, z, a) {}

		/**
		 Constructs a XYZA spectrum from the given XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum to copy.
		 */
		XYZASpectrum(const XYZASpectrum &xyza) noexcept = default;
		
		/**
		 Constructs a XYZA spectrum by moving the given XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum to move.
		 */
		XYZASpectrum(XYZASpectrum &&xyza) noexcept = default;
		
		/**
		 Constructs a XYZA spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum.
		 @param[in]		a
						The alpha component.
		 */
		explicit XYZASpectrum(const XYZSpectrum &xyz, F32 a = 1.0f) noexcept
			: XYZASpectrum(xyz.x, xyz.y, xyz.z, a) {}

		/**
		 Constructs a XYZA spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum.
		 @param[in]		a
						The alpha component.
		 */
		explicit XYZASpectrum(const RGBSpectrum &rgb, F32 a = 1.0f) noexcept 
			: XYZASpectrum(XYZSpectrum(rgb), a) {}

		/**
		 Constructs a XYZA spectrum from the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum.
		 */
		explicit XYZASpectrum(const RGBASpectrum &rgba) noexcept;

		/**
		 Constructs a XYZA spectrum from the given components.

		 @param[in]		v
						A reference to the components to copy.
		 @param[in]		a
						The alpha component.
		 */
		explicit XYZASpectrum(const XMFLOAT3 &v, F32 a = 1.0f) noexcept
			: XYZASpectrum(v.x, v.y, v.z, a) {}

		/**
		 Constructs a XYZA spectrum from the given components.

		 @param[in]		v
						A reference to the components to copy.
		 */
		explicit XYZASpectrum(const XMFLOAT4 &v) noexcept
			: XMFLOAT4(v) {}

		/**
		 Constructs a XYZA spectrum by moving the given components.

		 @param[in]		v
						A reference to the components to move.
		 */
		explicit XYZASpectrum(XMFLOAT4 &&v) noexcept
			: XMFLOAT4(std::move(v)) {}

		/**
		 Destructs this XYZA spectrum.
		 */
		~XYZASpectrum() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given XYZA spectrum to this XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum to copy.
		 @return		A reference to the copy of the given XYZA spectrum 
						(i.e. this XYZA spectrum).
		 */
		XYZASpectrum &operator=(const XYZASpectrum &xyza) = default;

		/**
		 Moves the given XYZA spectrum to this XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum to move.
		 @return		A reference to the moved XYZA spectrum (i.e. this 
						XYZA spectrum).
		 */
		XYZASpectrum &operator=(XYZASpectrum &&xyza) = default;
	};

	static_assert(sizeof(XYZASpectrum) == sizeof(XMFLOAT4), 
		"XYZASpectrum/XMFLOAT4 mismatch");
}