#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "math\sampling\primes.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	inline F32 RadicalInverse(size_t index, F32 base) noexcept {
		F32 result = 0.0f;
		F32 denom  = 1.0f;

		while (index) {
			denom  *= base;
			result += fmod(index, base) / denom;
			index  /= base;
		}

		return result;
	}

	inline F32 VanderCorput(size_t index) noexcept {
		return RadicalInverse(index, 2.0f);
	}

	inline void Halton(size_t index, F32 *sample, size_t nb_dims) noexcept {
		Assert(nb_dims < _countof(g_primes));

		for (size_t i = 0; i < nb_dims; ++i, ++sample) {
			*sample = RadicalInverse(index, 
									 static_cast< F32 >(g_primes[i]));
		}
	}

	inline const F32x2 Halton2D(size_t index) noexcept {
		const F32 x = RadicalInverse(index, 2.0f);
		const F32 y = RadicalInverse(index, 3.0f);
		
		return F32x2(x, y);
	}

	inline const F32x3 Halton3D(size_t index) noexcept {
		const F32 x = RadicalInverse(index, 2.0f);
		const F32 y = RadicalInverse(index, 3.0f);
		const F32 z = RadicalInverse(index, 5.0f);
		
		return F32x3(x, y, z);
	}

	inline const F32x4 Halton4D(size_t index) noexcept {
		const F32 x = RadicalInverse(index, 2.0f);
		const F32 y = RadicalInverse(index, 3.0f);
		const F32 z = RadicalInverse(index, 5.0f);
		const F32 w = RadicalInverse(index, 7.0f);
		
		return F32x4(x, y, z, w);
	}

	inline void Hammersley(size_t index, F32 *sample, size_t nb_dims, 
		size_t nb_samples) noexcept {
		
		Assert(index < nb_samples);
		Assert(nb_dims <= _countof(g_primes));
		
		*sample = index / F32(nb_samples);
		++sample;

		for (size_t i = 0; i < nb_dims - 1; ++i, ++sample) {
			*sample = RadicalInverse(index, 
									 static_cast< F32 >(g_primes[i]));
		}
	}

	inline const F32x2 Hammersley2D(size_t index, size_t nb_samples) noexcept {
		Assert(index < nb_samples);

		const F32 x = index / F32(nb_samples);
		const F32 y = RadicalInverse(index, 2.0f);
		
		return F32x2(x, y);
	}

	inline const F32x3 Hammersley3D(size_t index, size_t nb_samples) noexcept {
		Assert(index < nb_samples);

		const F32 x = index / F32(nb_samples);
		const F32 y = RadicalInverse(index, 2.0f);
		const F32 z = RadicalInverse(index, 3.0f);
		
		return F32x3(x, y, z);
	}

	inline const F32x4 Hammersley4D(size_t index, size_t nb_samples) noexcept {
		Assert(index < nb_samples);

		const F32 x = index / F32(nb_samples);
		const F32 y = RadicalInverse(index, 2.0f);
		const F32 z = RadicalInverse(index, 3.0f);
		const F32 w = RadicalInverse(index, 5.0f);
		
		return F32x4(x, y, z, w);
	}

	inline const F32x2 Roth(size_t index, size_t nb_samples) noexcept {
		return Hammersley2D(index, nb_samples);
	}
}