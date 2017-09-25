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

	inline XMFLOAT2 UniformSampleOnUnitCircle(f32 u) noexcept {
		const f32 phi = XM_2PI * u;
		
		return XMFLOAT2(
				cos(phi), 
				sin(phi));
	}

	inline XMFLOAT2 UniformSampleOnUnitHalfcircle(f32 u) noexcept {
		const f32 phi = XM_PI * u;
		
		return XMFLOAT2(
				cos(phi), 
				sin(phi));
	}

	inline XMFLOAT2 UniformSampleInUnitCircle(f32 u1, f32 u2) noexcept {
		const f32 phi = XM_2PI * u1;
		const f32 r   = sqrt(u2);
		
		return XMFLOAT2(
				r * cos(phi), 
				r * sin(phi));
	}

	inline XMFLOAT2 UniformSampleInUnitHalfcircle(f32 u1, f32 u2) noexcept {
		const f32 phi = XM_PI * u1;
		const f32 r   = sqrt(u2);
		
		return XMFLOAT2(
				r * cos(phi), 
				r * sin(phi));
	}

	inline XMFLOAT3 UniformSampleOnUnitSphere(f32 u1, f32 u2) noexcept {
		const f32 cos_theta = 1.0f - 2.0f * u1;
		const f32 sin_theta = sqrtf(std::max(0.0f, 1.0f - cos_theta * cos_theta));
		const f32 phi       = XM_2PI * u2;
		
		return XMFLOAT3(
				cos(phi) * sin_theta, 
				cos_theta, 
				sin(phi) * sin_theta);
	}

	inline XMFLOAT3 UniformSampleOnUnitHemisphere(f32 u1, f32 u2) noexcept {
		// u1 := cos_theta
		const f32 sin_theta = sqrt(std::max(0.0f, 1.0f - u1 * u1));
		const f32 phi = XM_2PI * u2;
		
		return XMFLOAT3(
				cos(phi) * sin_theta, 
				u1, 
				sin(phi) * sin_theta);
	}

	inline XMFLOAT3 UniformSampleInUnitSphere(f32 u1, f32 u2, f32 u3) noexcept {
		const f32 cos_theta = 1.0f - 2.0f * u1;
		const f32 sin_theta = sqrtf(std::max(0.0f, 1.0f - cos_theta * cos_theta));
		const f32 phi = XM_2PI * u2;
		const f32 r = pow(u3, 1.0f / 3.0f);
		
		return XMFLOAT3(
				r * cos(phi) * sin_theta, 
				r * cos_theta, 
				r * sin(phi) * sin_theta);
	}

	inline XMFLOAT3 UniformSampleInUnitHemisphere(f32 u1, f32 u2, f32 u3) noexcept {
		// u1 := cos_theta
		const f32 sin_theta = sqrt(std::max(0.0f, 1.0f - u1 * u1));
		const f32 phi = XM_2PI * u2;
		const f32 r = pow(u3, 1.0f / 3.0f);
		
		return XMFLOAT3(
				r * cos(phi) * sin_theta, 
				r * u1, 
				r * sin(phi) * sin_theta);
	}

	inline XMFLOAT3 CosineWeightedSampleOnUnitHemisphere(f32 u1, f32 u2) noexcept {
		
		const f32 cos_theta = sqrt(1.0f - u1);
		const f32 sin_theta = sqrt(u1);
		const f32 phi       = XM_2PI * u2;
		
		return XMFLOAT3(
				cos(phi) * sin_theta, 
				cos_theta, 
				sin(phi) * sin_theta);
	}
}