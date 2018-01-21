#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\sampling\primes.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]] inline F32 RadicalInverse(size_t index, F32 base) noexcept {
		auto result = 0.0f;
		auto denom  = 1.0f;

		while (index) {
			denom  *= base;
			result += fmod(index, base) / denom;
			index  /= base;
		}

		return result;
	}

	[[nodiscard]] inline F32 VanderCorput(size_t index) noexcept {
		return RadicalInverse(index, 2.0f);
	}

	inline void Halton(size_t index,  F32 *sample, size_t nb_dims) noexcept {
		Assert(nb_dims < std::size(g_primes));

		for (size_t i = 0; i < nb_dims; ++i, ++sample) {
			*sample = RadicalInverse(index, 
									 static_cast< F32 >(g_primes[i]));
		}
	}

	[[nodiscard]] inline const F32x2 Halton2D(size_t index) noexcept {
		const auto x = RadicalInverse(index, 2.0f);
		const auto y = RadicalInverse(index, 3.0f);
		
		return F32x2(x, y);
	}

	[[nodiscard]] inline const F32x3 Halton3D(size_t index) noexcept {
		const auto x = RadicalInverse(index, 2.0f);
		const auto y = RadicalInverse(index, 3.0f);
		const auto z = RadicalInverse(index, 5.0f);
		
		return F32x3(x, y, z);
	}

	[[nodiscard]] inline const F32x4 Halton4D(size_t index) noexcept {
		const auto x = RadicalInverse(index, 2.0f);
		const auto y = RadicalInverse(index, 3.0f);
		const auto z = RadicalInverse(index, 5.0f);
		const auto w = RadicalInverse(index, 7.0f);
		
		return F32x4(x, y, z, w);
	}

	inline void Hammersley(size_t index, F32 *sample, size_t nb_dims, size_t nb_samples) noexcept {
		
		Assert(index < nb_samples);
		Assert(nb_dims <= std::size(g_primes));
		
		*sample = index / F32(nb_samples);
		++sample;

		for (size_t i = 0; i < nb_dims - 1; ++i, ++sample) {
			*sample = RadicalInverse(index, 
									 static_cast< F32 >(g_primes[i]));
		}
	}

	[[nodiscard]] inline const F32x2 
		Hammersley2D(size_t index, size_t nb_samples) noexcept {
		
		Assert(index < nb_samples);

		const auto x = index / F32(nb_samples);
		const auto y = RadicalInverse(index, 2.0f);
		
		return F32x2(x, y);
	}

	[[nodiscard]] inline const F32x3 
		Hammersley3D(size_t index, size_t nb_samples) noexcept {
		
		Assert(index < nb_samples);

		const auto x = index / F32(nb_samples);
		const auto y = RadicalInverse(index, 2.0f);
		const auto z = RadicalInverse(index, 3.0f);
		
		return F32x3(x, y, z);
	}

	[[nodiscard]] inline const F32x4 
		Hammersley4D(size_t index, size_t nb_samples) noexcept {
		
		Assert(index < nb_samples);

		const auto x = index / F32(nb_samples);
		const auto y = RadicalInverse(index, 2.0f);
		const auto z = RadicalInverse(index, 3.0f);
		const auto w = RadicalInverse(index, 5.0f);
		
		return F32x4(x, y, z, w);
	}

	[[nodiscard]] inline const F32x2 
		Roth(size_t index, size_t nb_samples) noexcept {

		return Hammersley2D(index, nb_samples);
	}
}