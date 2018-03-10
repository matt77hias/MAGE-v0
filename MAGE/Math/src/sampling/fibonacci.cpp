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

		auto sample    = samples.data();
		const size_t n = samples.size();

		// Boundary points
		// alpha == 0.0f -> jagged boundary.
		// alpha == 2.0f -> smooth boundary.
		const auto n_boundary = static_cast< U32 >(
			                    alpha * sqrt(static_cast< F32 >(n))) + 1;
		
		size_t j = 0;
		for (size_t i = j; i <= n - n_boundary; ++i, ++j, ++sample) {
			const auto r   = sqrt((i + 0.5f) / (n - 0.5f * n_boundary));
			const auto phi = XM_GA * (i + shift);
			
			*sample = F32x2(r * cos(phi), r * sin(phi));
		}
		for (size_t i = j + 1; i < n; ++i, ++sample) {
			const auto r   = 1.0f;
			const auto phi = XM_GA * (i + shift);
			
			*sample = F32x2(r * cos(phi), r * sin(phi));
		}
	}

	void FibonacciSpiralSamplesOnUnitSphere(gsl::span< F32x3 > samples, 
											F32 shift) noexcept {

		const auto offset = 2.0f / samples.size();
		const size_t n    = samples.size();
		
		size_t i = 0;
		for (auto& sample : samples) {
			const auto phi       = XM_GA * fmodf((i + shift),
				                                static_cast< F32 >(n));
			const auto cos_theta = ((i + 0.5f) * offset) - 1.0f;
			const auto sin_theta = sqrt(1.0f - cos_theta * cos_theta);
			
			sample = F32x3(cos(phi) * sin_theta, 
						   cos_theta, 
						   sin(phi) * sin_theta);
		}
	}

	void FibonacciSpiralSamplesOnUnitHemisphere(gsl::span< F32x3 > samples, 
												F32 shift, 
												bool positive) noexcept {

		const auto offset = 1.0f / samples.size();
		const size_t n    = 2 * samples.size();
		
		size_t i = (positive) ? samples.size() : 0;
		for (auto& sample : samples) {
			const auto phi       = XM_GA * fmodf((i + shift), 
												 static_cast< F32 >(n));
			const auto cos_theta = ((i + 0.5f) * offset) - 1.0f;
			const auto sin_theta = sqrt(1.0f - cos_theta * cos_theta);
			
			sample = F32x3(cos(phi) * sin_theta, 
						   cos_theta,
						   sin(phi) * sin_theta);
		}
	}

	void FibonacciSpiralCosineWeightedSamplesOnUnitHemisphere(
		gsl::span< F32x3 > samples, F32 shift) noexcept {

		size_t i = 0;
		for (auto& sample : samples) {
			const auto phi       = XM_GA * (i + shift);
			const auto sin_theta = sqrt((i + 0.5f) / (samples.size() - 0.5f));
			const auto cos_theta = sqrt(1.0f - sin_theta * sin_theta);
			
			sample = F32x3(cos(phi) * sin_theta, 
						   cos_theta, 
						   sin(phi) * sin_theta);
		}
	}
}