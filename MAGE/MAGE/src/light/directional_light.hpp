#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "spectrum\spectrum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	/**
	 A class of directional lights.
	 */
	class alignas(16) DirectionalLight final : public Component {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a directional light.
		 */
		DirectionalLight() noexcept;
		
		/**
		 Constructs a directional light from the given directional light.

		 @param[in]		light
						A reference to the directional light to copy.
		 */
		DirectionalLight(const DirectionalLight &light) noexcept;

		/**
		 Constructs a directional light by moving the given directional light.

		 @param[in]		light
						A reference to the directional light to move.
		 */
		DirectionalLight(DirectionalLight &&light) noexcept;

		/**
		 Destructs this directional light.
		 */
		virtual ~DirectionalLight();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given directional light to this directional light.

		 @param[in]		light
						A reference to the directional light to copy.
		 @return		A reference to the copy of the given directional light
						(i.e. this directional light).
		 */
		DirectionalLight &operator=(const DirectionalLight &light) noexcept;

		/**
		 Moves the given directional light to this directional light.

		 @param[in]		light
						A reference to the directional light to move.
		 @return		A reference to the moved directional light (i.e. this 
						directional light).
		 */
		DirectionalLight &operator=(DirectionalLight &&light) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB base color of this directional light.

		 @return		A reference to the sRGB base color of this directional 
						light.
		 */
		[[nodiscard]] SRGB &GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this directional light.

		 @return		A reference to the sRGB base color of this directional 
						light.
		 */
		[[nodiscard]] const SRGB &GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the radiance of this directional light.

		 @return		The radiance in watts per square meter per steradians 
						of this directional light.
		 */
		[[nodiscard]] F32 GetRadiance() const noexcept {
			return m_radiance;
		}

		/**
		 Sets the radiance of this directional light to the given radiance.
		 
		 @pre			@a radiance must be non-negative.
		 @param[in]		radiance
						The radiance in watts per square meter per steradians.
		 */
		void SetRadiance(F32 radiance) noexcept {
			Assert(0.0f <= radiance);
			m_radiance = radiance;
		}

		/**
		 Returns the radiance spectrum of this directional light.

		 @return		The radiance spectrum of this directional light.
		 */
		[[nodiscard]] const RGB GetRadianceSpectrum() const noexcept {
			const auto L = m_radiance * SRGBtoRGB(XMLoad(m_base_color));
			return RGB(XMStore< F32x3 >(L));
		}

		//---------------------------------------------------------------------
		// Member Methods: Shadowing
		//---------------------------------------------------------------------

		/**
		 Checks whether shadows should be used for this directional light.

		 @return		@c true if shadows should be used for this
						directional light. @c false otherwise.
		 */
		[[nodiscard]] bool UseShadows() const noexcept {
			return m_shadows;
		}

		/**
		 Enables shadows for this directional light.
		 */
		void EnableShadows() noexcept {
			SetShadows(true);
		}

		/**
		 Dissables shadows for this directional light.
		 */
		void DissableShadows() noexcept {
			SetShadows(false);
		}

		/**
		 Toggles shadows for this directional light.
		 */
		void ToggleShadows() noexcept {
			SetShadows(!m_shadows);
		}

		/**
		 Sets shadows for this directional light to the given value.

		 @param[in]		shadows
						@c true if shadows should be used for this directional 
						light. @c false otherwise.
		 */
		void SetShadows(bool shadows) noexcept {
			m_shadows = shadows;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether shadows should be calculated or not not for 
		 this directional light.
		 */
		bool m_shadows;

		/**
		 The radiance in watts per square meter per steradians of this 
		 directional light.
		 */
		F32 m_radiance;

		/**
		 The sRGB base color of this directional light.
		 */
		SRGB m_base_color;
	};

	#pragma warning( pop )
}