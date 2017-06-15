#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of (high precision) wall clock timers.
	 */
	class Timer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a timer.
		 */
		Timer();

		/**
		 Constructs a timer from the given timer.
		
		 @param[in]		timer
						A reference to the timer to copy.
		 */
		Timer(const Timer &timer) = default;

		/**
		 Constructs a timer by moving the given timer.

		 @param[in]		timer
						A reference to the timer to move.
		 */
		Timer(Timer &&timer) = default;

		/**
		 Destructs this timer.
		 */
		~Timer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given timer to this timer.
		
		 @param[in]		timer
						A reference to the timer to copy.
		 @return		A reference to the copy of the given timer
						(i.e. this timer).
		 */
		Timer &operator=(const Timer &timer) = default;

		/**
		 Moves the given timer to this timer.

		 @param[in]		timer
						A reference to the timer to move.
		 @return		A reference to the moved timer
						(i.e. this timer).
		 */
		Timer &operator=(Timer &&timer) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts this timer.
		 */
		void Start() noexcept;

		/**
		 Stops this timer.
		 */
		void Stop() noexcept;

		/**
		 Restarts this timer.
		 */
		void Restart() noexcept;

		/**
		 Resumes this timer.
		 */
		void Resume() noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Delta Time
		//---------------------------------------------------------------------

		/**
		 Returns the wall clock delta time (in seconds) of this timer.

		 @return		The wall clock delta time (in seconds) of this timer.
		 */
		double GetDeltaTime() const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Total Delta Time
		//---------------------------------------------------------------------

		/**
		 Returns the total wall clock delta time (in seconds) of this timer.

		 @return		The total wall clock delta time (in seconds) of this timer.
		 */
		double GetTotalDeltaTime() const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the last timestamp of this timer.
		 */
		void UpdateLastTimestamp() const noexcept;

		/**
		 Resets the delta time, total delta time and last timestamp of this timer.
		 */
		void ResetDeltaTime() const noexcept;

		/**
		 Updates the delta time, total delta time and last timestamp of this timer.
		 */
		void UpdateDeltaTime() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The last timestamp of this timer.
		 */
		mutable LARGE_INTEGER m_last_timestamp;

		/**
		 The delta time of this timer.
		 */
		mutable uint64_t m_delta_time;

		/**
		 The total delta time of this timer.
		 */
		mutable uint64_t m_total_delta_time;

		/**
		 Flag indicating whether this timer is running.
		 */
		bool m_running;

		/**
		 The time frequency of this timer.
		 */
		LARGE_INTEGER m_time_frequency;

		/**
		 The time period of this timer.
		 */
		double m_s_time_period;
	};
}