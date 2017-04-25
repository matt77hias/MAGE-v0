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

	class AmbientLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit AmbientLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f))
			: Light(intensity) {}
		AmbientLight(const AmbientLight &light) = default;
		AmbientLight(AmbientLight &&light) = default;
		virtual ~AmbientLight() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		AmbientLight &operator=(const AmbientLight &light) = delete;
		AmbientLight &operator=(AmbientLight &&light) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< AmbientLight > Clone() const {
			return std::static_pointer_cast< AmbientLight >(CloneImplementation());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< Light > CloneImplementation() const override {
			return SharedPtr< AmbientLight >(new AmbientLight(*this));
		}
	};
}