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
	 A class of ambient lights.
	 */
	class AmbientLight final : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an ambient light.

		 @param[in]		intensity
						The RGB intensity.
		 */
		explicit AmbientLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));

		/**
		 Constructs an ambient light from the given ambient light.

		 @param[in]		light
						A reference to the ambient light to copy.
		 */
		AmbientLight(const AmbientLight &light);

		/**
		 Constructs an ambient light by moving the given ambient light.

		 @param[in]		light
						A reference to the ambient light to move.
		 */
		AmbientLight(AmbientLight &&light);

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
		AmbientLight &operator=(const AmbientLight &light);

		/**
		 Moves the given ambient light to this ambient light.

		 @param[in]		light
						A reference to the ambient light to move.
		 @return		A reference to the moved ambient light
						(i.e. this ambient light).
		 */
		AmbientLight &operator=(AmbientLight &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this ambient light.

		 @return		A pointer to the clone of this ambient light.
		 */
		UniquePtr< AmbientLight > Clone() const {
			return static_pointer_cast< AmbientLight >(CloneImplementation());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this ambient light.

		 @return		A pointer to the clone of this ambient light.
		 */
		virtual UniquePtr< Light > CloneImplementation() const override;
	};
}