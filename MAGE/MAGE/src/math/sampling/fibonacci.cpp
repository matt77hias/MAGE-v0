#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\sampling\fibonacci.hpp"
#include "math\sampling\rng.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void FibonacciSpiralSamplesInUnitCircle(F32x2 *samples, 
		size_t nb_samples, F32 shift, F32 alpha) noexcept {

		// Boundary points
		// alpha == 0.0f -> jagged boundary.
		// alpha == 2.0f -> smooth boundary.
		const U32 np_boundary = static_cast< U32 >(
			alpha * sqrt(static_cast< F32 >(nb_samples))) + 1;
		
		size_t j = 0;
		for (size_t i = j; i <= nb_samples - np_boundary; ++i, ++j, ++samples) {
			
			const F32 r   = sqrt((i + 0.5f) / (nb_samples - 0.5f * np_boundary));
			const F32 phi = XM_GA * (i + shift);
			
			*samples = F32x2(r * cos(phi), r * sin(phi));
		}
		for (size_t i = j + 1; i < nb_samples; ++i, ++samples) {
			
			const F32 r   = 1.0f;
			const F32 phi = XM_GA * (i + shift);
			
			*samples = F32x2(r * cos(phi), r * sin(phi));
		}
	}

	void FibonacciSpiralSamplesOnUnitSphere(F32x3 *samples, 
		size_t nb_samples, F32 shift) noexcept {

		const F32 offset = 2.0f / nb_samples;
		
		for (size_t i = 0; i < nb_samples; ++i, ++samples) {
			
			const F32 phi       = XM_GA * fmodf((i + shift), 
				                                static_cast< F32 >(nb_samples));
			const F32 cos_theta = ((i + 0.5f) * offset) - 1.0f;
			const F32 sin_theta = sqrt(1.0f - cos_theta * cos_theta);
			
			*samples = F32x3(cos(phi) * sin_theta, 
						     cos_theta, 
						     sin(phi) * sin_theta);
		}
	}

	void FibonacciSpiralSamplesOnUnitHemisphere(F32x3 *samples, 
		size_t nb_samples, F32 shift, bool positive) noexcept {

		const F32 offset = 1.0f / nb_samples;
		
		const size_t n     = 2 * nb_samples;
		const size_t start = (positive) ? nb_samples : 0;
		const size_t end   = (positive) ? n : nb_samples;
		for (size_t i = start; i < end; ++i, ++samples) {
			
			const F32 phi       = XM_GA * fmodf((i + shift), 
				                                static_cast< F32 >(n));
			const F32 cos_theta = ((i + 0.5f) * offset) - 1.0f;
			const F32 sin_theta = sqrt(1.0f - cos_theta * cos_theta);
			
			*samples = F32x3(cos(phi) * sin_theta, 
						     cos_theta, 
						     sin(phi) * sin_theta);
		}
	}

	void FibonacciSpiralCosineWeightedSamplesOnUnitHemisphere(
		F32x3 *samples, size_t nb_samples, F32 shift) noexcept {

		for (size_t i = 0; i < nb_samples; ++i, ++samples) {
			
			const F32 phi       = XM_GA * (i + shift);
			const F32 sin_theta = sqrt((i + 0.5f) / (nb_samples - 0.5f));
			const F32 cos_theta = sqrt(1.0f - sin_theta * sin_theta);
			
			*samples = F32x3(cos(phi) * sin_theta, 
						     cos_theta, 
						     sin(phi) * sin_theta);
		}
	}
}