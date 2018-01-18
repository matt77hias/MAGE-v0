#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "material\spectrum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	/**
	 A class of ambient lights.
	 */
	class alignas(16) AmbientLight final : public Component {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an ambient light.
		 */
		AmbientLight() noexcept;

		/**
		 Constructs an ambient light from the given ambient light.

		 @param[in]		light
						A reference to the ambient light to copy.
		 */
		AmbientLight(const AmbientLight &light) noexcept;

		/**
		 Constructs an ambient light by moving the given ambient light.

		 @param[in]		light
						A reference to the ambient light to move.
		 */
		AmbientLight(AmbientLight &&light) noexcept;

		/**
		 Destructs this ambient light.
		 */
		virtual ~AmbientLight();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given ambient light to this ambient light.

		 @param[in]		light
						A reference to the ambient light to copy.
		 @return		A reference to the copy of the given ambient light 
						(i.e. this ambient light).
		 */
		AmbientLight &operator=(const AmbientLight &light) noexcept;

		/**
		 Moves the given ambient light to this ambient light.

		 @param[in]		light
						A reference to the ambient light to move.
		 @return		A reference to the moved ambient light (i.e. this 
						ambient light).
		 */
		AmbientLight &operator=(AmbientLight &&light) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB base color of this ambient light.

		 @return		A reference to the sRGB base color of this ambient 
						light.
		 */
		[[nodiscard]] SRGB &GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this ambient light.

		 @return		A reference to the sRGB base color of this ambient 
						light.
		 */
		[[nodiscard]] const SRGB &GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the radiance of this ambient light.

		 @return		The radiance in watts per square meter per steradians 
						of this ambient light.
		 */
		[[nodiscard]] F32 GetRadiance() const noexcept {
			return m_radiance;
		}

		/**
		 Sets the radiance of this ambient light to the given radiance.
		 
		 @pre			@a radiance must be non-negative.
		 @param[in]		radiance
						The radiance in watts per square meter per steradians.
		 */
		void SetRadiance(F32 radiance) noexcept {
			Assert(0.0f <= radiance);
			m_radiance = radiance;
		}

		/**
		 Returns the radiance spectrum of this ambient light.

		 @return		The radiance spectrum of this ambient light.
		 */
		[[nodiscard]] const RGB GetRadianceSpectrum() const noexcept {
			const XMVECTOR L_v = m_radiance 
				               * SRGBtoRGB(XMLoadFloat3(&m_base_color));
			RGB L;
			XMStoreFloat3(&L, L_v);
			return L;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables: Lighting
		//---------------------------------------------------------------------

		/**
		 The radiance in watts per square meter per steradians of this ambient 
		 light.
		 */
		F32 m_radiance;

		/**
		 The sRGB base color of this ambient light.
		 */
		SRGB m_base_color;
	};

	#pragma warning( pop )
}