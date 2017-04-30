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

	class DirectionalLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit DirectionalLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));
		DirectionalLight(const DirectionalLight &light) = default;
		DirectionalLight(DirectionalLight &&light) = default;
		virtual ~DirectionalLight() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		DirectionalLight &operator=(const DirectionalLight &light) = delete;
		DirectionalLight &operator=(DirectionalLight &&light) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< DirectionalLight > Clone() const {
			return std::static_pointer_cast< DirectionalLight >(CloneImplementation());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< Light > CloneImplementation() const override;
	};
}