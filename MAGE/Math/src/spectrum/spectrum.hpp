#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// (linear) RGB
	//-------------------------------------------------------------------------
	#pragma region

	#ifdef RGB
		#error Illegal symbol definition.
	#endif

	// Forward declaration
	struct SRGB;
	struct XYZ;

	/**
	 A struct of RGB color spectra.
	 */
	struct RGB final : public F32x3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a RGB spectrum from the given spectrum components.

		 @param[in]		rgb
						The red, green and blue component.
		 */
		constexpr explicit RGB(F32 rgb = 0.0f) noexcept
			: RGB(rgb, rgb, rgb) {}
		
		/**
		 Constructs a RGB spectrum from the given spectrum components.

		 @param[in]		r
						The red component.
		 @param[in]		g
						The green component.
		 @param[in]		b
						The blue component.
		 */
		constexpr RGB(F32 r, F32 g, F32 b) noexcept
			: F32x3(r, g, b) {}

		/**
		 Constructs a RGB spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to copy.
		 */
		constexpr RGB(const RGB& rgb) noexcept = default;
		
		/**
		 Constructs a RGB spectrum by moving the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 */
		constexpr RGB(RGB&& rgb) noexcept = default;

		/**
		 Constructs a RGB spectrum from the given sRGB spectrum.

		 @param[in]		srgb
						A reference to the sRGB spectrum to copy.
		 */
		explicit RGB(const SRGB& srgb) noexcept;
		
		/**
		 Constructs a RGB spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to copy.
		 */
		explicit RGB(const XYZ& xyz) noexcept;

		/**
		 Constructs a RGB spectrum from the given components.

		 @param[in]		v
						The components.
		 */
		constexpr explicit RGB(F32x3 v) noexcept
			: F32x3(std::move(v)) {}

		/**
		 Destructs this RGB spectrum.
		 */
		~RGB() = default;

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
		constexpr RGB& operator=(const RGB& rgb) noexcept = default;

		/**
		 Moves the given RGB spectrum to this RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to move.
		 @return		A reference to the moved RGB spectrum (i.e. this RGB 
						spectrum).
		 */
		constexpr RGB& operator=(RGB&& rgb) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the red component of this RGB spectrum.

		 @return		A reference to the red component of this RGB spectrum.
		 */
		constexpr F32& GetR() noexcept {
			return operator[](0);
		}

		/**
		 Returns the red component of this RGB spectrum.

		 @return		The red component of this RGB spectrum.
		 */
		constexpr F32 GetR() const noexcept {
			return operator[](0);
		}

		/**
		 Returns the green component of this RGB spectrum.

		 @return		A reference to the green component of this RGB spectrum.
		 */
		constexpr F32& GetG() noexcept {
			return operator[](1);
		}

		/**
		 Returns the green component of this RGB spectrum.

		 @return		The green component of this RGB spectrum.
		 */
		constexpr F32 GetG() const noexcept {
			return operator[](1);
		}

		/**
		 Returns the blue component of this RGB spectrum.

		 @return		A reference to the blue component of this RGB spectrum.
		 */
		constexpr F32& GetB() noexcept {
			return operator[](2);
		}

		/**
		 Returns the blue component of this RGB spectrum.

		 @return		The blue component of this RGB spectrum.
		 */
		constexpr F32 GetB() const noexcept {
			return operator[](2);
		}
	};

	static_assert(sizeof(RGB) == sizeof(F32x3), "RGB/F32x3 mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// SRGB
	//-------------------------------------------------------------------------
	#pragma region

	#ifdef SRGB
		#error Illegal symbol definition.
	#endif

	/**
	 A struct of sRGB color spectra.
	 */
	struct SRGB final : public F32x3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sRGB spectrum from the given spectrum components.

		 @param[in]		srgb
						The red, green and blue component.
		 */
		constexpr explicit SRGB(F32 srgb = 0.0f) noexcept
			: SRGB(srgb, srgb, srgb) {}
		
		/**
		 Constructs a sRGB spectrum from the given spectrum components.

		 @param[in]		r
						The red component.
		 @param[in]		g
						The green component.
		 @param[in]		b
						The blue component.
		 */
		constexpr SRGB(F32 r, F32 g, F32 b) noexcept
			: F32x3(r, g, b) {}

		/**
		 Constructs a sRGB spectrum from the given sRGB spectrum.

		 @param[in]		srgb
						A reference to the sRGB spectrum to copy.
		 */
		constexpr SRGB(const SRGB& srgb) noexcept = default;
		
		/**
		 Constructs a sRGB spectrum by moving the given sRGB spectrum.

		 @param[in]		srgb
						A reference to the sRGB spectrum to move.
		 */
		constexpr SRGB(SRGB&& srgb) noexcept = default;
		
		/**
		 Constructs a sRGB spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to copy.
		 */
		explicit SRGB(const RGB& rgb) noexcept;

		/**
		 Constructs a sRGB spectrum from the given components.

		 @param[in]		v
						The components.
		 */
		constexpr explicit SRGB(F32x3 v) noexcept
			: F32x3(std::move(v)) {}

		/**
		 Destructs this sRGB spectrum.
		 */
		~SRGB() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given sRGB spectrum to this sRGB spectrum.

		 @param[in]		srgb
						A reference to the sRGB spectrum to copy.
		 @return		A reference to the copy of the given sRGB spectrum (i.e. 
						this sRGB spectrum).
		 */
		constexpr SRGB& operator=(const SRGB& srgb) noexcept = default;

		/**
		 Moves the given sRGB spectrum to this sRGB spectrum.

		 @param[in]		srgb
						A reference to the sRGB spectrum to move.
		 @return		A reference to the moved sRGB spectrum (i.e. this sRGB 
						spectrum).
		 */
		constexpr SRGB& operator=(SRGB&& srgb) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the red component of this sRGB spectrum.

		 @return		A reference to the red component of this sRGB spectrum.
		 */
		constexpr F32& GetR() noexcept {
			return operator[](0);
		}

		/**
		 Returns the red component of this sRGB spectrum.

		 @return		The red component of this sRGB spectrum.
		 */
		constexpr F32 GetR() const noexcept {
			return operator[](0);
		}

		/**
		 Returns the green component of this sRGB spectrum.

		 @return		A reference to the green component of this sRGB spectrum.
		 */
		constexpr F32& GetG() noexcept {
			return operator[](1);
		}

		/**
		 Returns the green component of this sRGB spectrum.

		 @return		The green component of this sRGB spectrum.
		 */
		constexpr F32 GetG() const noexcept {
			return operator[](1);
		}

		/**
		 Returns the blue component of this sRGB spectrum.

		 @return		A reference to the blue component of this sRGB spectrum.
		 */
		constexpr F32& GetB() noexcept {
			return operator[](2);
		}

		/**
		 Returns the blue component of this sRGB spectrum.

		 @return		The blue component of this sRGB spectrum.
		 */
		constexpr F32 GetB() const noexcept {
			return operator[](2);
		}
	};

	static_assert(sizeof(SRGB) == sizeof(F32x3), "SRGB/F32x3 mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// XYZ
	//-------------------------------------------------------------------------
	#pragma region

	#ifdef XYZ
		#error Illegal symbol definition.
	#endif

	/**
	 A struct of XYZ color spectra.
	 */
	struct XYZ final : public F32x3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a XYZ spectrum from the given spectrum components.

		 @param[in]		xyz
						The x, y and z component.
		 */
		constexpr explicit XYZ(F32 xyz = 0.0f) noexcept
			: XYZ(xyz, xyz, xyz) {}
		
		/**
		 Constructs a XYZ spectrum from the given spectrum components.

		 @param[in]		x
						The x component.
		 @param[in]		y
						The y component.
		 @param[in]		z
						The z component.
		 */
		constexpr XYZ(F32 x, F32 y, F32 z) noexcept
			: F32x3(x, y, z) {}

		/**
		 Constructs a XYZ spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to copy.
		 */
		constexpr XYZ(const XYZ& xyz) noexcept = default;
		
		/**
		 Constructs a XYZ spectrum by moving the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 */
		constexpr XYZ(XYZ&& xyz) noexcept = default;
		
		/**
		 Constructs a XYZ spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum to copy.
		 */
		explicit XYZ(const RGB& rgb) noexcept;
		
		/**
		 Constructs a XYZ spectrum from the given components.

		 @param[in]		v
						The components.
		 */
		constexpr explicit XYZ(F32x3 v) noexcept
			: F32x3(std::move(v)) {}

		/**
		 Destructs this XYZ spectrum.
		 */
		~XYZ() = default;

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
		constexpr XYZ& operator=(const XYZ& xyz) noexcept = default;

		/**
		 Moves the given XYZ spectrum to this XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum to move.
		 @return		A reference to the moved XYZ spectrum (i.e. this XYZ 
						spectrum).
		 */
		constexpr XYZ& operator=(XYZ&& xyz) noexcept = default;
	};

	static_assert(sizeof(XYZ) == sizeof(F32x3), "XYZ/F32x3 mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// (linear) RGBA
	//-------------------------------------------------------------------------
	#pragma region

	#ifdef RGBA
		#error Illegal symbol definition.
	#endif

	// Forward declaration
	struct SRGBA;
	struct XYZA;

	/**
	 A struct of RGBA color spectra.
	 */
	struct RGBA final : public F32x4 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a RGBA spectrum from the given spectrum components.

		 @param[in]		rgba
						The red, green and blue and alpha component.
		 */
		constexpr explicit RGBA(F32 rgba = 0.0f) noexcept
			: RGBA(rgba, rgba, rgba, rgba) {}
		
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
		constexpr RGBA(F32 r, F32 g, F32 b, F32 a = 1.0f) noexcept
			: F32x4(r, g, b, a) {}

		/**
		 Constructs a RGBA spectrum from the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to copy.
		 */
		constexpr RGBA(const RGBA& rgba) noexcept = default;
		
		/**
		 Constructs a RGBA spectrum by moving the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to move.
		 */
		constexpr RGBA(RGBA&& rgba) noexcept = default;
		
		/**
		 Constructs a RGBA spectrum from the given RGB spectrum.

		 @param[in]		rgb
						A reference to the RGB spectrum.
		 @param[in]		a
						The alpha component.
		 */
		constexpr RGBA(const RGB& rgb, F32 a = 1.0f) noexcept
			: F32x4(rgb, a) {}

		/**
		 Constructs a RGBA spectrum from the given SRGBA spectrum.

		 @param[in]		srgba
						A reference to the SRGBA spectrum.
		 */
		explicit RGBA(const SRGBA& srgba) noexcept;

		/**
		 Constructs a RGBA spectrum from the given XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum.
		 */
		explicit RGBA(const XYZA& xyza) noexcept;

		/**
		 Constructs a RGBA spectrum from the given components.

		 @param[in]		v
						The components.
		 */
		constexpr explicit RGBA(F32x4 v) noexcept
			: F32x4(std::move(v)) {}

		/**
		 Destructs this RGBA spectrum.
		 */
		~RGBA() = default;

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
		constexpr RGBA& operator=(const RGBA& rgba) noexcept = default;

		/**
		 Moves the given RGBA spectrum to this RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum to move.
		 @return		A reference to the moved RGBA spectrum (i.e. this RGBA 
						spectrum).
		 */
		constexpr RGBA& operator=(RGBA&& rgba) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the red component of this RGB spectrum.

		 @return		A reference to the red component of this RGB spectrum.
		 */
		constexpr F32& GetR() noexcept {
			return operator[](0);
		}

		/**
		 Returns the red component of this RGB spectrum.

		 @return		The red component of this RGB spectrum.
		 */
		constexpr F32 GetR() const noexcept {
			return operator[](0);
		}

		/**
		 Returns the green component of this RGB spectrum.

		 @return		A reference to the green component of this RGB spectrum.
		 */
		constexpr F32& GetG() noexcept {
			return operator[](1);
		}

		/**
		 Returns the green component of this RGB spectrum.

		 @return		The green component of this RGB spectrum.
		 */
		constexpr F32 GetG() const noexcept {
			return operator[](1);
		}

		/**
		 Returns the blue component of this RGB spectrum.

		 @return		A reference to the blue component of this RGB spectrum.
		 */
		constexpr F32& GetB() noexcept {
			return operator[](2);
		}

		/**
		 Returns the blue component of this RGB spectrum.

		 @return		The blue component of this RGB spectrum.
		 */
		constexpr F32 GetB() const noexcept {
			return operator[](2);
		}
	
		/**
		 Returns the alpha component of this RGB spectrum.

		 @return		A reference to the alpha component of this RGB spectrum.
		 */
		constexpr F32& GetA() noexcept {
			return operator[](3);
		}

		/**
		 Returns the alpha component of this RGB spectrum.

		 @return		The alpha component of this RGB spectrum.
		 */
		constexpr F32 GetA() const noexcept {
			return operator[](3);
		}
	};

	static_assert(sizeof(RGBA) == sizeof(F32x4), "RGBA/F32x4 mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// SRGBA
	//-------------------------------------------------------------------------
	#pragma region

	#ifdef SRGBA
		#error Illegal symbol definition.
	#endif

	/**
	 A struct of sRGBA color spectra.
	 */
	struct SRGBA final : public F32x4 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sRGBA spectrum from the given spectrum components.

		 @param[in]		rgba
						The red, green and blue and alpha component.
		 */
		constexpr explicit SRGBA(F32 rgba = 0.0f) noexcept
			: SRGBA(rgba, rgba, rgba, rgba) {}
		
		/**
		 Constructs a sRGBA spectrum from the given spectrum components.

		 @param[in]		r
						The red component.
		 @param[in]		g
						The green component.
		 @param[in]		b
						The blue component.
		 @param[in]		a
						The alpha component.
		 */
		constexpr SRGBA(F32 r, F32 g, F32 b, F32 a = 1.0f) noexcept
			: F32x4(r, g, b, a) {}

		/**
		 Constructs a sRGBA spectrum from the given sRGBA spectrum.

		 @param[in]		rgba
						A reference to the sRGBA spectrum to copy.
		 */
		constexpr SRGBA(const SRGBA& rgba) noexcept = default;
		
		/**
		 Constructs a sRGBA spectrum by moving the given sRGBA spectrum.

		 @param[in]		rgba
						A reference to the sRGBA spectrum to move.
		 */
		constexpr SRGBA(SRGBA&& rgba) noexcept = default;
		
		/**
		 Constructs a sRGBA spectrum from the given sRGB spectrum.

		 @param[in]		srgb
						A reference to the sRGB spectrum.
		 @param[in]		a
						The alpha component.
		 */
		constexpr SRGBA(const SRGB& srgb, F32 a = 1.0f) noexcept
			: F32x4(srgb, a) {}

		/**
		 Constructs a sRGBA spectrum from the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum.
		 */
		explicit SRGBA(const RGBA& rgba) noexcept;

		/**
		 Constructs a sRGBA spectrum from the given components.

		 @param[in]		v
						The components.
		 */
		constexpr explicit SRGBA(F32x4 v) noexcept
			: F32x4(std::move(v)) {}

		/**
		 Destructs this sRGBA spectrum.
		 */
		~SRGBA() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given sRGBA spectrum to this sRGBA spectrum.

		 @param[in]		rgba
						A reference to the sRGBA spectrum to copy.
		 @return		A reference to the copy of the given sRGBA spectrum 
						(i.e. this sRGBA spectrum).
		 */
		constexpr SRGBA& operator=(const SRGBA& rgba) noexcept = default;

		/**
		 Moves the given sRGBA spectrum to this sRGBA spectrum.

		 @param[in]		rgba
						A reference to the sRGBA spectrum to move.
		 @return		A reference to the moved sRGBA spectrum (i.e. this sRGBA 
						spectrum).
		 */
		constexpr SRGBA& operator=(SRGBA&& rgba) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the red component of this sRGB spectrum.

		 @return		A reference to the red component of this sRGB spectrum.
		 */
		constexpr F32& GetR() noexcept {
			return operator[](0);
		}

		/**
		 Returns the red component of this sRGB spectrum.

		 @return		The red component of this sRGB spectrum.
		 */
		constexpr F32 GetR() const noexcept {
			return operator[](0);
		}

		/**
		 Returns the green component of this sRGB spectrum.

		 @return		A reference to the green component of this sRGB spectrum.
		 */
		constexpr F32& GetG() noexcept {
			return operator[](1);
		}

		/**
		 Returns the green component of this sRGB spectrum.

		 @return		The green component of this sRGB spectrum.
		 */
		constexpr F32 GetG() const noexcept {
			return operator[](1);
		}

		/**
		 Returns the blue component of this sRGB spectrum.

		 @return		A reference to the blue component of this sRGB spectrum.
		 */
		constexpr F32& GetB() noexcept {
			return operator[](2);
		}

		/**
		 Returns the blue component of this sRGB spectrum.

		 @return		The blue component of this sRGB spectrum.
		 */
		constexpr F32 GetB() const noexcept {
			return operator[](2);
		}
	
		/**
		 Returns the alpha component of this sRGB spectrum.

		 @return		A reference to the alpha component of this sRGB spectrum.
		 */
		constexpr F32& GetA() noexcept {
			return operator[](3);
		}

		/**
		 Returns the alpha component of this sRGB spectrum.

		 @return		The alpha component of this sRGB spectrum.
		 */
		constexpr F32 GetA() const noexcept {
			return operator[](3);
		}
	};

	static_assert(sizeof(SRGBA) == sizeof(F32x4), "SRGBA/F32x4 mismatch");
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// XYZA
	//-------------------------------------------------------------------------
	#pragma region

	#ifdef XYZA
		#error Illegal symbol definition.
	#endif

	/**
	 A struct of XYZA color spectra.
	 */
	struct XYZA final : public F32x4 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a XYZA spectrum from the given spectrum components.

		 @param[in]		xyza
						The x, y and z and alpha component.
		 */
		constexpr explicit XYZA(F32 xyza = 0.0f) noexcept
			: XYZA(xyza, xyza, xyza, xyza) {}
		
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
		constexpr XYZA(F32 x, F32 y, F32 z, F32 a = 1.0f) noexcept
			: F32x4(x, y, z, a) {}

		/**
		 Constructs a XYZA spectrum from the given XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum to copy.
		 */
		constexpr XYZA(const XYZA& xyza) noexcept = default;
		
		/**
		 Constructs a XYZA spectrum by moving the given XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum to move.
		 */
		constexpr XYZA(XYZA&& xyza) noexcept = default;
		
		/**
		 Constructs a XYZA spectrum from the given XYZ spectrum.

		 @param[in]		xyz
						A reference to the XYZ spectrum.
		 @param[in]		a
						The alpha component.
		 */
		constexpr explicit XYZA(const XYZ& xyz, F32 a = 1.0f) noexcept
			: F32x4(xyz, a) {}

		/**
		 Constructs a XYZA spectrum from the given RGBA spectrum.

		 @param[in]		rgba
						A reference to the RGBA spectrum.
		 */
		explicit XYZA(const RGBA& rgba) noexcept;

		/**
		 Constructs a XYZA spectrum from the given components.

		 @param[in]		v
						The components.
		 */
		constexpr explicit XYZA(F32x4 v) noexcept
			: F32x4(std::move(v)) {}

		/**
		 Destructs this XYZA spectrum.
		 */
		~XYZA() = default;

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
		constexpr XYZA& operator=(const XYZA& xyza) noexcept = default;

		/**
		 Moves the given XYZA spectrum to this XYZA spectrum.

		 @param[in]		xyza
						A reference to the XYZA spectrum to move.
		 @return		A reference to the moved XYZA spectrum (i.e. this 
						XYZA spectrum).
		 */
		constexpr XYZA& operator=(XYZA&& xyza) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the alpha component of this XYZA spectrum.

		 @return		A reference to the alpha component of this XYZA spectrum.
		 */
		constexpr F32& GetA() noexcept {
			return operator[](3);
		}

		/**
		 Returns the alpha component of this XYZA spectrum.

		 @return		The alpha component of this XYZA spectrum.
		 */
		constexpr F32 GetA() const noexcept {
			return operator[](3);
		}
	};

	static_assert(sizeof(XYZA) == sizeof(F32x4), "XYZA/F32x4 mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// Conversions: (linear) RGB <-> sRGB
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Converts the given spectrum from (linear) RGB to sRGB space.

	 @param[in]		rgb
					The spectrum in (linear) RGB space.
	 @return		The spectrum in sRGB space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV RGBtoSRGB(FXMVECTOR rgb) noexcept {
		// Frostbite's conversion
		static constexpr auto exp = 1.0f / 2.4f;
		
		const auto low  = rgb * 12.92f;
		const auto high = 1.055f * XMVectorPow(rgb, XMVectorReplicate(exp))
			            - XMVectorReplicate(0.055f);
		const auto comp = XMVectorLessOrEqual(rgb, XMVectorReplicate(0.0031308f));
		
		return XMVectorSetW(XMVectorSelect(high, low, comp), XMVectorGetW(rgb));
	}

	/**
	 Converts the given spectrum from sRGB to (linear) RGB space.

	 @param[in]		srgb
					The spectrum in sRGB space.
	 @return		The spectrum in (linear) RGB space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV SRGBtoRGB(FXMVECTOR srgb) noexcept {
		// Frostbite's conversion
		static constexpr auto mlow  = 1.0f / 12.92f;
		static constexpr auto mhigh = 1.0f / 1.055f;

		const auto low  = srgb * mlow;
		const auto high = XMVectorPow(mhigh * (srgb + XMVectorReplicate(0.055f)),
			                          XMVectorReplicate(2.4f));
		const auto comp = XMVectorLessOrEqual(srgb, XMVectorReplicate(0.04045f));

		return XMVectorSetW(XMVectorSelect(high, low, comp), XMVectorGetW(srgb));
	}

	inline RGB::RGB(const SRGB& srgb) noexcept
		: RGB(XMStore< F32x3 >(SRGBtoRGB(XMLoad(srgb)))) {}

	inline SRGB::SRGB(const RGB& rgb) noexcept
		: SRGB(XMStore< F32x3 >(RGBtoSRGB(XMLoad(rgb)))) {}

	inline RGBA::RGBA(const SRGBA& srgba) noexcept
		: RGBA(XMStore< F32x4 >(SRGBtoRGB(XMLoad(srgba)))) {}

	inline SRGBA::SRGBA(const RGBA& rgba) noexcept
		: SRGBA(XMStore< F32x4 >(RGBtoSRGB(XMLoad(rgba)))) {}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Conversions: (linear) RGB <-> XYZ
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Converts the given spectrum from (linear) RGB to XYZ space.

	 @param[in]		rgb
					The spectrum in (linear) RGB space.
	 @return		The spectrum in XYZ space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV RGBtoXYZ(FXMVECTOR rgb) noexcept {
		// Convert ITU-R Recommendation BT.709 linear RGB to XYZ.
		static const XMMATRIX transform = {
			0.412453f, 0.212671f, 0.019334f, 0.0f,
			0.357580f, 0.715160f, 0.119193f, 0.0f,
			0.180423f, 0.072169f, 0.950227f, 0.0f,
			0.0f,      0.0f,      0.0f,      1.0f
		};

		return XMVector4Transform(rgb, transform);
	}

	/**
	 Converts the given spectrum from XYZ to (linear) RGB space.

	 @param[in]		xyz
					The spectrum in XYZ space.
	 @return		The spectrum in (linear) RGB space.
	 @note			The alpha channel of the given spectrum is preserved.
	 */
	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XYZtoRGB(FXMVECTOR xyz) noexcept {
		// Convert XYZ to ITU-R Recommendation BT.709 linear RGB.
		static const XMMATRIX transform = {
			 3.240479f, -0.969256f,  0.055648f, 0.0f,
			-1.537150f,  1.875992f, -0.204043f, 0.0f, 
			-0.498535f,  0.041556f,  1.057311f, 0.0f,
			 0.0f,       0.0f,       0.0f,      1.0f
		};

		return XMVector4Transform(xyz, transform);
	}

	inline RGB::RGB(const XYZ& xyz) noexcept
		: RGB(XMStore< F32x3 >(XYZtoRGB(XMLoad(xyz)))) {}

	inline XYZ::XYZ(const RGB& rgb) noexcept
		: XYZ(XMStore< F32x3 >(RGBtoXYZ(XMLoad(rgb)))) {}

	inline RGBA::RGBA(const XYZA& xyza) noexcept
		: RGBA(XMStore< F32x4 >(XYZtoRGB(XMLoad(xyza)))) {}

	inline XYZA::XYZA(const RGBA& rgba) noexcept
		: XYZA(XMStore< F32x4 >(RGBtoXYZ(XMLoad(rgba)))) {}

	#pragma endregion
}
