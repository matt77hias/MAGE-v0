#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	inline XMFLOAT2 UniformSampleOnUnitCircle(float u) noexcept {
		const float phi = XM_2PI * u;
		return XMFLOAT2(cos(phi), sin(phi));
	}

	inline XMFLOAT2 UniformSampleOnUnitHalfcircle(float u) noexcept {
		const float phi = XM_PI * u;
		return XMFLOAT2(cos(phi), sin(phi));
	}

	inline XMFLOAT2 UniformSampleInUnitCircle(float u1, float u2) noexcept {
		const float phi = XM_2PI * u1;
		const float r = sqrt(u2);
		return XMFLOAT2(r * cos(phi), r * sin(phi));
	}

	inline XMFLOAT2 UniformSampleInUnitHalfcircle(float u1, float u2) noexcept {
		const float phi = XM_PI * u1;
		const float r = sqrt(u2);
		return XMFLOAT2(r * cos(phi), r * sin(phi));
	}

	inline XMFLOAT3 UniformSampleOnUnitSphere(float u1, float u2) noexcept {
		const float cos_theta = 1.0f - 2.0f * u1;
		const float sin_theta = sqrtf(std::max(0.0f, 1.0f - cos_theta * cos_theta));
		const float phi = XM_2PI * u2;
		return XMFLOAT3(cos(phi) * sin_theta, cos_theta, sin(phi) * sin_theta);
	}

	inline XMFLOAT3 UniformSampleOnUnitHemisphere(float u1, float u2) noexcept {
		// u1 := cos_theta
		const float sin_theta = sqrt(std::max(0.0f, 1.0f - u1 * u1));
		const float phi = XM_2PI * u2;
		return XMFLOAT3(cos(phi) * sin_theta, u1, sin(phi) * sin_theta);
	}

	inline XMFLOAT3 UniformSampleInUnitSphere(float u1, float u2, float u3) noexcept {
		const float cos_theta = 1.0f - 2.0f * u1;
		const float sin_theta = sqrtf(std::max(0.0f, 1.0f - cos_theta * cos_theta));
		const float phi = XM_2PI * u2;
		const float r = pow(u3, 1.0f / 3.0f);
		return XMFLOAT3(r * cos(phi) * sin_theta, r * cos_theta, r * sin(phi) * sin_theta);
	}

	inline XMFLOAT3 UniformSampleInUnitHemisphere(float u1, float u2, float u3) noexcept {
		// u1 := cos_theta
		const float sin_theta = sqrt(std::max(0.0f, 1.0f - u1 * u1));
		const float phi = XM_2PI * u2;
		const float r = pow(u3, 1.0f / 3.0f);
		return XMFLOAT3(r * cos(phi) * sin_theta, r * u1, r * sin(phi) * sin_theta);
	}

	inline XMFLOAT3 CosineWeightedSampleOnUnitHemisphere(float u1, float u2) noexcept {
		const float cos_theta = sqrt(1.0f - u1);
		const float sin_theta = sqrt(u1);
		const float phi = XM_2PI * u2;
		return XMFLOAT3(cos(phi) * sin_theta, cos_theta, sin(phi) * sin_theta);
	}
}