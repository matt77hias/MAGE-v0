#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]]
	inline const F32x2 UniformSampleOnUnitCircle(F32 u) noexcept {
		const auto phi = XM_2PI * u;

		return { std::cos(phi), std::sin(phi) };
	}

	[[nodiscard]]
	inline const F32x2 UniformSampleOnUnitHalfcircle(F32 u) noexcept {
		const auto phi = XM_PI * u;

		return { std::cos(phi), std::sin(phi) };
	}

	[[nodiscard]]
	inline const F32x2 UniformSampleInUnitCircle(F32 u1, F32 u2) noexcept {
		const auto phi = XM_2PI * u1;
		const auto r   = std::sqrt(u2);

		return { r * std::cos(phi), r * std::sin(phi) };
	}

	[[nodiscard]]
	inline const F32x2 UniformSampleInUnitHalfcircle(F32 u1, F32 u2) noexcept {
		const auto phi = XM_PI * u1;
		const auto r   = std::sqrt(u2);

		return { r * std::cos(phi), r * std::sin(phi) };
	}

	[[nodiscard]]
	inline const F32x3 UniformSampleOnUnitSphere(F32 u1, F32 u2) noexcept {
		const auto cos_theta = 1.0f - 2.0f * u1;
		const auto sin_theta = std::sqrt(std::max(0.0f, 1.0f - cos_theta * cos_theta));
		const auto phi       = XM_2PI * u2;

		return { std::cos(phi) * sin_theta,
			     cos_theta,
			     std::sin(phi) * sin_theta };
	}

	[[nodiscard]]
	inline const F32x3 UniformSampleOnUnitHemisphere(F32 u1, F32 u2) noexcept {
		// u1 := cos_theta
		const auto sin_theta = std::sqrt(std::max(0.0f, 1.0f - u1 * u1));
		const auto phi       = XM_2PI * u2;

		return { std::cos(phi) * sin_theta,
				 u1,
				 std::sin(phi) * sin_theta };
	}

	[[nodiscard]]
	inline const F32x3 UniformSampleInUnitSphere(F32 u1, F32 u2, F32 u3) noexcept {
		const auto cos_theta = 1.0f - 2.0f * u1;
		const auto sin_theta = std::sqrt(std::max(0.0f, 1.0f - cos_theta * cos_theta));
		const auto phi       = XM_2PI * u2;
		const auto r         = std::pow(u3, 1.0f / 3.0f);

		return { r * std::cos(phi) * sin_theta,
				 r * cos_theta,
				 r * std::sin(phi) * sin_theta };
	}

	[[nodiscard]]
	inline const F32x3 UniformSampleInUnitHemisphere(F32 u1, F32 u2, F32 u3) noexcept {
		// u1 := cos_theta
		const auto sin_theta = std::sqrt(std::max(0.0f, 1.0f - u1 * u1));
		const auto phi       = XM_2PI * u2;
		const auto r         = std::pow(u3, 1.0f / 3.0f);

		return { r * std::cos(phi) * sin_theta,
				 r * u1,
				 r * std::sin(phi) * sin_theta };
	}

	[[nodiscard]]
	inline const F32x3 CosineWeightedSampleOnUnitHemisphere(F32 u1, F32 u2) noexcept {
		const auto cos_theta = std::sqrt(1.0f - u1);
		const auto sin_theta = std::sqrt(u1);
		const auto phi       = XM_2PI * u2;

		return { std::cos(phi) * sin_theta,
				 cos_theta,
				 std::sin(phi) * sin_theta };
	}
}