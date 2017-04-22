#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.hpp"
#include "material\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Light : public WorldObject {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~Light() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		Light &operator=(const Light &light) = default;
		Light &operator=(Light &&light) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual Light *Clone() const = 0;

		const RGBSpectrum GetIntensity() const {
			return m_intensity;
		}
		void SetIntensity(const RGBSpectrum &intensity) {
			m_intensity = intensity;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit Light(const string name, const RGBSpectrum &intensity)
			: WorldObject(name), m_intensity(intensity) {}
		Light(const Light &light) = default;
		Light(Light &&light) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const XMVECTOR GetWorldLightPosition() const {
			return GetTransform()->GetWorldEye();
		}
		const XMVECTOR GetWorldLightDirection() const {
			return GetTransform()->GetWorldForward();
		}
		const XMVECTOR GetViewLightPosition(const XMMATRIX &world_to_view) const {
			return XMVector4Transform(GetWorldLightPosition(), world_to_view);
		}
		const XMVECTOR GetViewLightDirection(const XMMATRIX &world_to_view) const {
			return XMVector4Transform(GetWorldLightDirection(), world_to_view);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The intensity of this light.
		 */
		RGBSpectrum m_intensity;
	};
}