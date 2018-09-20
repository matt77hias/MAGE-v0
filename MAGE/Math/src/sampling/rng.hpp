#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

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

	#ifdef RNG
		#error Illegal symbol definition.
	#endif

	/**
	 A class of (uniform) random number generators (RNGs).
	 */
	class RNG final {

	public:

		//-------------------------------------------------------------------------
		// Constructors and Destructors
		//-------------------------------------------------------------------------

		/**
		 Constructs a RNG with the given seed.

		 @param[in]		seed
						The seed.
		 */
		explicit RNG(U32 seed = 606418532u) noexcept
			: m_generator(),
			m_distribution() {

			Seed(seed);
		}

		/**
		 Constructs a RNG from the given RNG.

		 @param[in]		rng
						A reference to the RNG to copy.
		 */
		RNG(const RNG& rng) noexcept = default;

		/**
		 Constructs a RNG by moving the given RNG.

		 @param[in]		rng
						A reference to the RNG to move.
		 */
		RNG(RNG&& rng) noexcept = default;

		/**
		 Destructs this RNG.
		 */
		~RNG() = default;

		//-------------------------------------------------------------------------
		// Assignment Operators
		//-------------------------------------------------------------------------

		/**
		 Copies the given RNG to this RNG.

		 @param[in]		rng
						A reference to the RNG to copy.
		 @return		A reference to the copy of the given RNG (i.e. this RNG).
		 */
		RNG& operator=(const RNG& rng) = delete;

		/**
		 Moves the given RNG to this RNG.

		 @param[in]		rng
						A reference to the RNG to move.
		 @return		A reference to the moved RNG (i.e. this RNG).
		 */
		RNG& operator=(RNG&& rng) = delete;

		//-------------------------------------------------------------------------
		// Member Methods
		//-------------------------------------------------------------------------

		/**
		 Seeds this RNG.

		 @param[in]		seed
						The seed.
		 */
		void Seed(U32 seed) noexcept {
			m_generator.seed(seed);
		}

		/**
		 Generates a uniform random number in [0,1).

		 @return		A uniform random number in [0,1).
		 */
		F32 Uniform() noexcept {
			return m_distribution(m_generator);
		}

		/**
		 Generates a uniform random number in [@a start,@a end).

		 @param[in]		low
						The lower (inclusive) bound of the interval.
		 @param[in]		high
						The upper (exclusive) bound of the interval.
		 @return		A uniform random number in [@a start,@a end).
		 */
		F32 Uniform(F32 low, F32 high) noexcept {
			return low + Uniform() * (high - low);
		}

	private:

		//-------------------------------------------------------------------------
		// Member Variables
		//-------------------------------------------------------------------------

		/**
		 The random number generator, Newer "Minimum standard", of this RNG. This
		 LCG has a much smaller footprint compared to the default Mersenne Twister
		 used in the std.
		 */
		std::minstd_rand m_generator;

		/**
		 The uniform real number distribution of this RNG.
		 */
		std::uniform_real_distribution< F32 > m_distribution;
	};
}
