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
	class DirectionalLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a directional light.

		 @param[in]		intensity
						The RGB intensity.
		 */
		explicit DirectionalLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));
		
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
		 @return		A reference to the moved directional light
						(i.e. this directional light).
		 */
		DirectionalLight &operator=(DirectionalLight &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this directional light.

		 @return		A pointer to the clone of this directional light.
		 */
		SharedPtr< DirectionalLight > Clone() const {
			return std::static_pointer_cast< DirectionalLight >(CloneImplementation());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this directional light.

		 @return		A pointer to the clone of this directional light.
		 */
		virtual SharedPtr< Light > CloneImplementation() const override;
	};
}