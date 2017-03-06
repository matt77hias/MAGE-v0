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
		PointLight(const PointLight &light)
			: WorldObject(light), m_radius(light.m_radius), m_intensity(light.m_intensity) {}
		virtual ~PointLight() = default;

		PointLight &operator=(const PointLight &light) {
			WorldObject::operator=(static_cast< const WorldObject & >(light));
			m_radius = light.m_radius;
			m_intensity = light.m_intensity;
			return (*this);
		}

		virtual PointLight *Clone() const {
			return new PointLight(*this);
		}

		float GetRadius() const {
			return m_radius;
		}
		void SetRadius(float radius) {
			m_radius = radius;
		}
		RGBSpectrum GetIntensity() const {
			return m_intensity;
		}
		void SetIntensity(const RGBSpectrum &intensity) {
			m_intensity = intensity;
		}

		//TODO
		//Point3 result;
		//XMStoreFloat3(&result, XMVector4Transform(m_transform->GetWorldOrigin(), transform));
	
	private:

		/**
		 The name of this point light.
		 */
		string m_name;

		/**
		 The transform of this point light.
		 */
		SharedPtr< Transform > m_transform;

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