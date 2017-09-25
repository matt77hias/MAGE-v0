#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "sampling\rng.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 The Golden Angle.
	 */
	const float XM_GA = 2.399963230f;

	inline void FibonacciSpiralSamplesInUnitCircle(XMFLOAT2 *samples, 
		size_t nb_samples, float shift = 1.0f, float alpha = 2.0f) noexcept {

		// Boundary points
		// alpha == 0.0f -> jagged boundary.
		// alpha == 2.0f -> smooth boundary.
		const u32 np_boundary = static_cast< u32 >(
			alpha * sqrt(static_cast< float >(nb_samples))) + 1;
		
		size_t j = 0;
		for (size_t i = j; i <= nb_samples - np_boundary; ++i, ++j, ++samples) {
			
			const float r   = sqrt((i + 0.5f) / (nb_samples - 0.5f * np_boundary));
			const float phi = XM_GA * (i + shift);
			
			*samples = XMFLOAT2(
						r * cos(phi), 
						r * sin(phi));
		}
		for (size_t i = j + 1; i < nb_samples; ++i, ++samples) {
			
			const float r   = 1.0f;
			const float phi = XM_GA * (i + shift);
			
			*samples = XMFLOAT2(
						r * cos(phi), 
						r * sin(phi));
		}
	}

	inline void FibonacciSpiralSamplesOnUnitSphere(XMFLOAT3 *samples, 
		size_t nb_samples, float shift = 1.0f) noexcept {

		const float offset = 2.0f / nb_samples;
		
		for (size_t i = 0; i < nb_samples; ++i, ++samples) {
			
			const float phi       = XM_GA * fmod((i + shift), nb_samples);
			const float cos_theta = ((i + 0.5f) * offset) - 1.0f;
			const float sin_theta = sqrt(1.0f - cos_theta * cos_theta);
			
			*samples = XMFLOAT3(
						cos(phi) * sin_theta, 
						cos_theta, 
						sin(phi) * sin_theta);
		}
	}

	inline void FibonacciSpiralSamplesOnUnitHemisphere(XMFLOAT3 *samples, 
		size_t nb_samples, float shift = 1.0f, bool positive = true) noexcept {

		const float offset = 1.0f / nb_samples;
		
		const size_t n     = 2 * nb_samples;
		const size_t start = (positive) ? nb_samples : 0;
		const size_t end   = (positive) ? n : nb_samples;
		for (size_t i = start; i < end; ++i, ++samples) {
			
			const float phi       = XM_GA * fmod((i + shift), n);
			const float cos_theta = ((i + 0.5f) * offset) - 1.0f;
			const float sin_theta = sqrt(1.0f - cos_theta * cos_theta);
			
			*samples = XMFLOAT3(
						cos(phi) * sin_theta, 
						cos_theta, 
						sin(phi) * sin_theta);
		}
	}

	inline void FibonacciSpiralCosineWeightedSamplesOnUnitHemisphere(
		XMFLOAT3 *samples, size_t nb_samples, float shift = 1.0f) noexcept {

		for (size_t i = 0; i < nb_samples; ++i, ++samples) {
			
			const float phi       = XM_GA * (i + shift);
			const float sin_theta = sqrt((i + 0.5f) / (nb_samples - 0.5f));
			const float cos_theta = sqrt(1.0f - sin_theta * sin_theta);
			
			*samples = XMFLOAT3(
						cos(phi) * sin_theta, 
						cos_theta, 
						sin(phi) * sin_theta);
		}
	}
}