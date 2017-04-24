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

		explicit DirectionalLight(const string name, const RGBSpectrum &intensity)
			: Light(name, intensity) {}
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

		virtual SharedPtr< WorldObject > CloneImplementation() const override {
			return SharedPtr< DirectionalLight >(new DirectionalLight(*this));
		}
	};
}