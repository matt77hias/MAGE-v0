#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 The Golden Angle.
	 */
	constexpr F32 XM_GA = 2.399963230f;

	void FibonacciSpiralSamplesInUnitCircle(F32x2 *samples,
		size_t nb_samples, F32 shift = 1.0f, F32 alpha = 2.0f) noexcept;

	void FibonacciSpiralSamplesOnUnitSphere(F32x3 *samples,
		size_t nb_samples, F32 shift = 1.0f) noexcept;

	void FibonacciSpiralSamplesOnUnitHemisphere(F32x3 *samples,
		size_t nb_samples, F32 shift = 1.0f, bool positive = true) noexcept;

	void FibonacciSpiralCosineWeightedSamplesOnUnitHemisphere(
		F32x3 *samples, size_t nb_samples, F32 shift = 1.0f) noexcept;
}