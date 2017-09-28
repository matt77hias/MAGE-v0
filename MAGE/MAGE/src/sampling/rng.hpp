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

		explicit RNG(U32 seed = 606418532u)
			: m_generator(),
			m_distribution(std::uniform_real_distribution< F32 >(0.0f, 1.0f)) {

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

		void Seed(U32 seed) noexcept {
			m_generator.seed(seed);
		}

		F32 UniformF32() noexcept {
			return m_distribution(m_generator);
		}

		F32 UniformFloat(F32 start, F32 end) noexcept {
			return start + UniformF32() * (end - start);
		}

	private:

		//-------------------------------------------------------------------------
		// Member Variables
		//-------------------------------------------------------------------------

		std::default_random_engine m_generator;

		std::uniform_real_distribution< F32 > m_distribution;
	};
}