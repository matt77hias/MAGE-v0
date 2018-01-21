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
	 A class of engine statistics.
	 */
	class EngineStatistics final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the engine statistics associated with the current engine.

		 @pre			The engine statistics associated with the current 
						engine must be loaded.
		 @return		A pointer to the engine statistics associated with the 
						current engine.
		 */
		[[nodiscard]] static EngineStatistics *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a engine statistics.
		 */
		constexpr EngineStatistics() noexcept
			: m_nb_draw_calls(0u) {}

		/**
		 Constructs a engine statistics from the given engine statistics.

		 @param[in]		statistics
						A reference to the engine statistics to copy.
		 */
		constexpr EngineStatistics(
			const EngineStatistics &statistics) noexcept = default;

		/**
		 Constructs a engine statistics by moving the given engine statistics.

		 @param[in]		statistics
						A reference to the engine statistics to move.
		 */
		constexpr EngineStatistics(
			EngineStatistics &&statistics) noexcept = default;

		/**
		 Destructs this engine statistics.
		 */
		~EngineStatistics() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given engine statistics to this engine statistics.

		 @param[in]		statistics
						A reference to the engine statistics to copy.
		 @return		A reference to the copy of the given engine statistics 
						(i.e. this engine statistics).
		 */
		constexpr EngineStatistics &operator=(
			const EngineStatistics &statistics) noexcept = default;

		/**
		 Moves the given engine statistics to this engine statistics.

		 @param[in]		statistics
						A reference to the engine statistics to move.
		 @return		A reference to the moved engine statistics (i.e. this 
						engine statistics).
		 */
		constexpr EngineStatistics &operator=(
			EngineStatistics &&statistics) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this engine statistics for rendering.
		 */
		constexpr void PrepareRendering() noexcept {
			m_nb_draw_calls = 0u;
		}

		/**
		 Returns the number of draw calls of this engine statistics.

		 @return		The number of draw calls of this engine statistics.
		 */
		[[nodiscard]] constexpr U32 GetNumberOfDrawCalls() noexcept {
			return m_nb_draw_calls;
		}

		/**
		 Increments the number of draw calls of this engine statistics.

		 @param[in]		units
						The number of units to add.
		 */
		constexpr void IncrementNumberOfDrawCalls(U32 units = 1u) noexcept {
			m_nb_draw_calls += units;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The number of draw calls of this engine statistics.
		 */
		U32 m_nb_draw_calls;
	};
}