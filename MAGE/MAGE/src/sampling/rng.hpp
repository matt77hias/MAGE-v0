#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <random>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class RNG final {

	public:

		//-------------------------------------------------------------------------
		// Constructors and Destructors
		//-------------------------------------------------------------------------

		explicit RNG(u32 seed = 606418532u)
			: m_generator(),
			m_distribution(std::uniform_real_distribution< float >(0.0f, 1.0f)) {

			Seed(seed);
		}
		
		RNG(const RNG &rng) = default;
		
		RNG(RNG &&rng) = default;
		
		~RNG() = default;

		//-------------------------------------------------------------------------
		// Assignment Operators
		//-------------------------------------------------------------------------

		RNG &operator=(const RNG &rng) = delete;
		
		RNG &operator=(RNG &&rng) = delete;

		//-------------------------------------------------------------------------
		// Member Methods
		//-------------------------------------------------------------------------

		void Seed(u32 seed) noexcept {
			m_generator.seed(seed);
		}

		f32 UniformF32() noexcept {
			return m_distribution(m_generator);
		}

		f32 UniformFloat(f32 start, f32 end) noexcept {
			return start + UniformF32() * (end - start);
		}

	private:

		//-------------------------------------------------------------------------
		// Member Variables
		//-------------------------------------------------------------------------

		std::default_random_engine m_generator;

		std::uniform_real_distribution< f32 > m_distribution;
	};
}