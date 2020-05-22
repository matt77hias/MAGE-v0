#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sampling\fibonacci.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void FibonacciSpiralSamplesInUnitCircle(gsl::span< F32x2 > samples,
											F32 shift,
											F32 alpha) noexcept {

		using std::size;
		auto sample    = samples.data();
		const auto n   = static_cast< std::size_t >(size(samples));

		// Boundary points
		// alpha == 0.0f -> jagged boundary.
		// alpha == 2.0f -> smooth boundary.
		const auto n_boundary = static_cast< std::size_t >(
			                    alpha * std::sqrt(static_cast< F32 >(n))) + 1;

		std::size_t j = 0u;
		for (std::size_t i = j; i <= n - n_boundary; ++i, ++j, ++sample) {
			const auto r   = std::sqrt((i + 0.5f) / (n - 0.5f * n_boundary));
			const auto phi = XM_GA * (i + shift);

			*sample = F32x2(r * std::cos(phi), r * std::sin(phi));
		}
		for (std::size_t i = j + 1u; i < n; ++i, ++sample) {
			const auto r   = 1.0f;
			const auto phi = XM_GA * (i + shift);

			*sample = F32x2(r * std::cos(phi), r * std::sin(phi));
		}
	}

	void FibonacciSpiralSamplesOnUnitSphere(gsl::span< F32x3 > samples,
											F32 shift) noexcept {


		using std::size;
		const auto offset = 2.0f / size(samples);
		const auto n      = static_cast< std::size_t >(size(samples));

		std::size_t i = 0u;
		for (auto& sample : samples) {
			const auto phi       = XM_GA * fmodf((i + shift),
				                                static_cast< F32 >(n));
			const auto cos_theta = ((i + 0.5f) * offset) - 1.0f;
			const auto sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);

			sample = F32x3(std::cos(phi) * sin_theta,
						   cos_theta,
						   std::sin(phi) * sin_theta);
		}
	}

	void FibonacciSpiralSamplesOnUnitHemisphere(gsl::span< F32x3 > samples,
												F32 shift,
												bool positive) noexcept {

		using std::size;
		const auto offset = 1.0f / size(samples);
		const auto n      = 2 * static_cast< std::size_t >(size(samples));

		std::size_t i = positive ? size(samples) : 0u;
		for (auto& sample : samples) {
			const auto phi       = XM_GA * fmodf((i + shift),
												 static_cast< F32 >(n));
			const auto cos_theta = ((i + 0.5f) * offset) - 1.0f;
			const auto sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);

			sample = F32x3(cos(phi) * sin_theta,
						   cos_theta,
						   sin(phi) * sin_theta);
		}
	}

	void FibonacciSpiralCosineWeightedSamplesOnUnitHemisphere(
		gsl::span< F32x3 > samples, F32 shift) noexcept {

		using std::size;

		std::size_t i = 0u;
		for (auto& sample : samples) {
			const auto phi       = XM_GA * (i + shift);
			const auto sin_theta = std::sqrt((i + 0.5f) / (size(samples) - 0.5f));
			const auto cos_theta = std::sqrt(1.0f - sin_theta * sin_theta);

			sample = F32x3(std::cos(phi) * sin_theta,
						   cos_theta,
						   std::sin(phi) * sin_theta);
		}
	}
}