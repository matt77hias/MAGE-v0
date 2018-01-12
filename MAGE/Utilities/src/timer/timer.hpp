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

#include <chrono>

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
		Timer() noexcept;

		/**
		 Constructs a timer from the given timer.
		
		 @param[in]		timer
						A reference to the timer to copy.
		 */
		Timer(const Timer &timer) noexcept = default;

		/**
		 Constructs a timer by moving the given timer.

		 @param[in]		timer
						A reference to the timer to move.
		 */
		Timer(Timer &&timer) noexcept = default;

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
		 @return		A reference to the copy of the given timer (i.e. this 
						timer).
		 */
		Timer &operator=(const Timer &timer) noexcept = default;

		/**
		 Moves the given timer to this timer.

		 @param[in]		timer
						A reference to the timer to move.
		 @return		A reference to the moved timer (i.e. this timer).
		 */
		Timer &operator=(Timer &&timer) noexcept = default;

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
		F64 GetDeltaTime() const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Total Delta Time
		//---------------------------------------------------------------------

		/**
		 Returns the total wall clock delta time (in seconds) of this timer.

		 @return		The total wall clock delta time (in seconds) of this 
						timer.
		 */
		F64 GetTotalDeltaTime() const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Resets the delta time, total delta time and last timestamp of this 
		 timer.
		 */
		void ResetDeltaTime() const noexcept;

		/**
		 Updates the delta time, total delta time and last timestamp of this 
		 timer.
		 */
		void UpdateDeltaTime() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The clock type of timers.
		 */
		using Clock = std::chrono::high_resolution_clock;
		
		/**
		 The time stamp type representing the time points of timers.
		 */
		using TimeStamp = Clock::time_point;

		/**
		 The time interval type representing the interval between time points 
		 of timers.
		 */
		using TimeInterval = Clock::duration;

		/**
		 The clock of this timer.
		 */
		Clock m_clock;

		/**
		 The last timestamp of this timer.
		 */
		mutable TimeStamp m_last_timestamp;

		/**
		 The delta time of this timer.
		 */
		mutable TimeInterval m_delta_time;

		/**
		 The total delta time of this timer.
		 */
		mutable TimeInterval m_total_delta_time;

		/**
		 Flag indicating whether this timer is running.
		 */
		bool m_running;
	};
}