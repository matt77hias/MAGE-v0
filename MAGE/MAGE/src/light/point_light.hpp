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

	class PointLight : public WorldObject {

	public:

		PointLight(const string name, float radius, const RGBSpectrum &intensity)
			: WorldObject(name), m_radius(radius), m_intensity(intensity) {}
		PointLight(const PointLight &light) = default;
		PointLight(PointLight &&light) = default;
		virtual ~PointLight() = default;

		PointLight &operator=(const PointLight &light) = default;
		PointLight &operator=(PointLight &&light) = default;

		virtual PointLight *Clone() const {
			return new PointLight(*this);
		}

		float GetRadius() const {
			return m_radius;
		}
		void SetRadius(float radius) {
			m_radius = radius;
		}
		const RGBSpectrum GetIntensity() const {
			return m_intensity;
		}
		void SetIntensity(const RGBSpectrum &intensity) {
			m_intensity = intensity;
		}

	private:

		/**
		 The radius of this point light.
		 */
		float m_radius;

		/**
		 The intensity of this point light.
		 */
		RGBSpectrum m_intensity;
	};
}