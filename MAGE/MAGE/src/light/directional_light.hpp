#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of directional lights.
	 */
	class DirectionalLight final : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a directional light.

		 @param[in]		color
						The color.
		 */
		DirectionalLight();
		
		/**
		 Constructs a directional light from the given directional light.

		 @param[in]		light
						A reference to the directional light to copy.
		 */
		DirectionalLight(const DirectionalLight &light);

		/**
		 Constructs a directional light by moving the given directional light.

		 @param[in]		light
						A reference to the directional light to move.
		 */
		DirectionalLight(DirectionalLight &&light);

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
		DirectionalLight &operator=(const DirectionalLight &light);

		/**
		 Moves the given directional light to this directional light.

		 @param[in]		light
						A reference to the directional light to move.
		 @return		A reference to the moved directional light (i.e. this 
						directional light).
		 */
		DirectionalLight &operator=(DirectionalLight &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this directional light.

		 @return		A pointer to the clone of this directional light.
		 */
		UniquePtr< DirectionalLight > Clone() const {
			return static_pointer_cast< DirectionalLight >(CloneImplementation());
		}

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the radiance of this directional light.

		 @return		The radiance of this directional light.
		 */
		F32 GetRadiance() const noexcept {
			return m_radiance;
		}

		/**
		 Sets the radiance of this directional light to the given radiance.
		 
		 @param[in]		radiance
						The radiance.
		 */
		void SetRadiance(F32 radiance) noexcept {
			m_radiance = radiance;
		}

		/**
		 Returns the radiance spectrum of this directional light.

		 @return		The radiance spectrum of this directional light.
		 */
		const RGBSpectrum GetRadianceSpectrum() const noexcept {
			const RGBSpectrum color = GetColor();
			return RGBSpectrum(m_radiance * color.x, 
				               m_radiance * color.y, 
				               m_radiance * color.z);
		}

		//---------------------------------------------------------------------
		// Member Methods: Shadowing
		//---------------------------------------------------------------------

		/**
		 Checks whether shadows should be used for this directional light.

		 @return		@c true if shadows should be used for this
						directional light. @c false otherwise.
		 */
		bool UseShadows() const noexcept {
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
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this directional light.

		 @return		A pointer to the clone of this directional light.
		 */
		virtual UniquePtr< Light > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The radiance of this directional light.
		 */
		F32 m_radiance;

		/**
		 A flag indicating whether shadows should be calculated or not not for 
		 this directional light.
		 */
		bool m_shadows;
	};
}