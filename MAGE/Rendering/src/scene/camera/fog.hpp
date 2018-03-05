#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math_utils.hpp"
#include "spectrum\color.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of fog with respect to the camera position (eye) to avoid popping 
	 artifacts while moving.
	 */
	class Fog final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a fog.
		 */
		constexpr Fog() noexcept
			: m_base_color(color::Silver), 
			m_density(0.0) {}

		/**
		 Constructs a fog from the given fog.

		 @param[in]		fog
						A reference to the fog to copy.
		 */
		constexpr Fog(const Fog& fog) noexcept = default;

		/**
		 Constructs a fog by moving the given fog.

		 @param[in]		fog
						A reference to the fog to move.
		 */
		constexpr Fog(Fog&& fog) noexcept = default;

		/**
		 Destructs this fog.
		 */
		~Fog() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given fog to this fog.

		 @param[in]		fog
						A reference to the fog to copy.
		 @return		A reference to the copy of the given fog (i.e. this fog).
		 */
		constexpr Fog& operator=(const Fog& fog) noexcept = default;

		/**
		 Moves the given fog to this fog.

		 @param[in]		fog
						A reference to the fog to move.
		 @return		A reference to the moved fog (i.e. this fog).
		 */
		constexpr Fog& operator=(Fog&& fog) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB base color of this fog.

		 @return		A reference to the sRGB base color of this fog.
		 */
		[[nodiscard]]
		constexpr SRGB& GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this fog.

		 @return		A reference to the sRGB base color of this fog.
		 */
		[[nodiscard]]
		constexpr const SRGB& GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the density of this fog.
		
		 @return		The density of this fog.
		 */
		[[nodiscard]]
		constexpr F32 GetDensity() const noexcept {
			return m_density;
		}

		/**
		 Sets the density of this fog to the given value.

		 @param[in]		density
						The density.
		 */
		constexpr void SetDensity(F32 density) noexcept {
			m_density = Saturate(density);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The sRGB base color of this fog.
		 */
		SRGB m_base_color;

		/**
		 The density of this fog.
		 */
		F32 m_density;
	};
}