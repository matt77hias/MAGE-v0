#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	enum LightInfoType {
		LightInfoType_NoLight          = 0,
		LightInfoType_SpotLight        = 1,
		LightInfoType_OmniLight	       = 2,
		LightInfoType_DirectionalLight = 3
	};

	__declspec(align(16)) struct LightInfo final {

	public:


		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		LightInfo()
			: m_intensity(), m_position(), m_direction(), m_type(LightInfoType_NoLight),
			m_distance_falloff_start(0.0f), m_distance_falloff_end(0.0f),
			m_cos_penumbra(0.0f), m_cos_umbra(0.0f) {}
		explicit LightInfo(const XMFLOAT4 &intensity,
			const XMFLOAT4 &position, const XMFLOAT3 &direction,
			float distance_falloff_start, float distance_falloff_end,
			float cos_penumbra, float cos_umbra)
			: m_intensity(intensity),
			m_position(position), m_direction(direction), m_type(LightInfoType_SpotLight),
			m_distance_falloff_start(distance_falloff_start), m_distance_falloff_end(distance_falloff_end),
			m_cos_penumbra(cos_penumbra), m_cos_umbra(cos_umbra) {}
		explicit LightInfo(const XMFLOAT4 &intensity, const XMFLOAT4 &position,
			float distance_falloff_start, float distance_falloff_end)
			: m_intensity(intensity),
			m_position(position), m_direction(), m_type(LightInfoType_OmniLight),
			m_distance_falloff_start(distance_falloff_start), m_distance_falloff_end(distance_falloff_end),
			m_cos_penumbra(0.0f), m_cos_umbra(0.0f) {}
		explicit LightInfo(const XMFLOAT4 &intensity, const XMFLOAT3 &direction)
			: m_intensity(intensity),
			m_position(), m_direction(direction), m_type(LightInfoType_DirectionalLight),
			m_distance_falloff_start(0.0f), m_distance_falloff_end(0.0f),
			m_cos_penumbra(0.0f), m_cos_umbra(0.0f) {}
		LightInfo(const LightInfo &light) = default;
		LightInfo(LightInfo &&light) = default;
		~LightInfo() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		LightInfo &operator=(const LightInfo &light) = default;
		LightInfo &operator=(LightInfo &&light) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const XMFLOAT4 GetIntensity() const {
			return m_intensity;
		}
		void SetIntensity(const XMFLOAT4 &intensity) {
			m_intensity = intensity;
		}
		const XMFLOAT4 GetPosition() const {
			return m_position;
		}
		void SetPosition(const XMFLOAT4 &position) {
			m_position = m_position;
		}
		const XMFLOAT3 GetDirection() const {
			return m_direction;
		}
		void SetDirection(const XMFLOAT3 &direction) {
			m_direction = m_direction;
		}
		const LightInfoType GetType() const {
			return m_type;
		}
		void SetType(LightInfoType type) {
			m_type = type;
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

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		XMFLOAT4 m_intensity;
		XMFLOAT4 m_position;
		XMFLOAT3 m_direction;
		LightInfoType m_type;
		float m_distance_falloff_start;
		float m_distance_falloff_end;
		float m_cos_penumbra;
		float m_cos_umbra;
	};

	static_assert(sizeof(LightInfo) == 64, "Light struct mismatch");

	LightInfo CreateOmniLightInfo(const XMFLOAT4 &intensity, const XMFLOAT4 &position,
		float distance_falloff_start, float distance_falloff_end) {
		return LightInfo(intensity, position, 
			distance_falloff_start, distance_falloff_end);
	}

	LightInfo CreateDirectionalLightInfo(const XMFLOAT4 &intensity, const XMFLOAT3 &direction) {
		return LightInfo(intensity, direction);
	}

	LightInfo CreateSpotLightInfo(const XMFLOAT4 &intensity,
		const XMFLOAT4 &position, const XMFLOAT3 &direction,
		float distance_falloff_start, float distance_falloff_end,
		float cos_penumbra, float cos_umbra) {
		return LightInfo(intensity, position, direction, 
			distance_falloff_start, distance_falloff_end,
			cos_penumbra, cos_umbra);
	}
}