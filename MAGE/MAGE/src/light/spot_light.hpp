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

	class SpotLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpotLight(const string name, const RGBSpectrum &intensity,
			float distance_falloff_start = 0.0f, 
			float distance_falloff_end = 10.0f,
			float cos_penumbra = 0.96592583f,
			float cos_umbra = 0.86602540f)
			: Light(name, intensity),
			m_distance_falloff_start(distance_falloff_start), 
			m_distance_falloff_end(distance_falloff_end),
			m_cos_penumbra(cos_penumbra),
			m_cos_umbra(cos_umbra) {}
		SpotLight(const SpotLight &light) = default;
		SpotLight(SpotLight &&light) = default;
		virtual ~SpotLight() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		SpotLight &operator=(const SpotLight &light) = default;
		SpotLight &operator=(SpotLight &&light) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SpotLight *Clone() const {
			return new SpotLight(*this);
		}

		const XMVECTOR GetWorldLightPosition() const {
			return GetTransform()->GetWorldEye();
		}
		const XMVECTOR GetWorldLightDirection() const {
			return GetTransform()->GetWorldForward();
		}
		
		float GetStartDistanceFalloff() const {
			return m_distance_falloff_start;
		}
		void SetStartDistanceFalloff(float distance_falloff_start) {
			m_distance_falloff_start = distance_falloff_start;
		}
		float GetEndDistanceFalloff() const {
			return m_distance_falloff_end;
		}
		void SetEndDistanceFalloff(float distance_falloff_end) {
			m_distance_falloff_end = distance_falloff_end;
		}
		void SetDistanceFalloff(float distance_falloff_start, float distance_falloff_end) {
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
		}

		float GetStartAngualCutoff() const {
			return m_cos_penumbra;
		}
		void SetStartAngualCutoff(float cos_penumbra) {
			m_cos_penumbra = cos_penumbra;
		}
		float GetEndAngualCutoff() const {
			return m_cos_umbra;
		}
		void SetEndAngualCutoff(float cos_umbra) {
			m_cos_umbra = cos_umbra;
		}
		void SetAngualCutoff(float cos_penumbra, float cos_umbra) {
			SetStartAngualCutoff(cos_penumbra);
			SetEndAngualCutoff(cos_umbra);
		}

	private:

		float m_distance_falloff_start;
		float m_distance_falloff_end;
		float m_cos_penumbra;
		float m_cos_umbra;
	};
}