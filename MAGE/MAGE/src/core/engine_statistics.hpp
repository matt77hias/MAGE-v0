#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of engine statistics.
	 */
	struct EngineStatistics final {

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
		static EngineStatistics *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a engine statistics.
		 */
		EngineStatistics()
			: m_nb_draw_calls(0) {}

		/**
		 Constructs a engine statistics from the given engine statistics.

		 @param[in]		engine_statistics
						A reference to the engine statistics to copy.
		 */
		EngineStatistics(const EngineStatistics &engine_statistics) = default;

		/**
		 Constructs a engine statistics by moving the given engine statistics.

		 @param[in]		engine_statistics
						A reference to the engine statistics to move.
		 */
		EngineStatistics(EngineStatistics &&engine_statistics) = default;

		/**
		 Destructs this engine statistics.
		 */
		~EngineStatistics() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given engine statistics to this engine statistics.

		 @param[in]		engine_statistics
						A reference to the engine statistics to copy.
		 @return		A reference to the copy of the given engine statistics 
						(i.e. this engine statistics).
		 */
		EngineStatistics &operator=(
			const EngineStatistics &engine_statistics) = default;

		/**
		 Moves the given engine statistics to this engine statistics.

		 @param[in]		engine_statistics
						A reference to the engine statistics to move.
		 @return		A reference to the moved engine statistics (i.e. this 
						engine statistics).
		 */
		EngineStatistics &operator=(
			EngineStatistics &&engine_statistics) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this engine statistics for rendering.
		 */
		void PrepareRendering() noexcept {
			m_nb_draw_calls = 0;
		}

		/**
		 Returns the number of draw calls of this engine statistics.

		 @return		The number of draw calls of this engine statistics.
		 */
		u32 GetNumberOfDrawCalls() noexcept {
			return m_nb_draw_calls;
		}

		/**
		 Increments the number of draw calls of this engine statistics.

		 @param[in]		units
						The number of units to add.
		 */
		void IncrementNumberOfDrawCalls(u32 units = 1) noexcept {
			m_nb_draw_calls += units;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The number of draw calls of this engine statistics.
		 */
		u32 m_nb_draw_calls;
	};
}