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

		 @param[in]		intensity
						The RGB intensity.
		 */
		explicit DirectionalLight(
			const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));
		
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

		 @param[in]		@c true if shadows should be used for this directional 
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
		 A flag indicating whether shadows should be calculated or not not for 
		 this directional light.
		 */
		bool m_shadows;
	};
}