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
	 A class of (high precision) timers.
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
						A reference to the timer.
		 */
		Timer(const Timer &timer) = default;

		/**
		 Constructs a timer from the given timer.

		 @param[in]		timer
						A reference to the timer.
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
						A reference to the timer to copy from.
		 @return		A reference to the copy of the given timer
						(i.e. this timer).
		 */
		Timer &operator=(const Timer &timer) = default;

		/**
		 Copies the given timer to this timer.

		 @param[in]		timer
						A reference to the timer to copy from.
		 @return		A reference to the copy of the given timer
						(i.e. this timer).
		 */
		Timer &operator=(Timer &&timer) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts this timer.
		 */
		void Start();

		/**
		 Stops this timer.
		 */
		void Stop();

		/**
		 Restarts this timer.
		 */
		void Restart();

		/**
		 Resumes this timer.
		 */
		void Resume();

		//---------------------------------------------------------------------
		// Member Methods: Delta Time
		//---------------------------------------------------------------------

		/**
		 Returns the system delta time (in seconds) 
		 of this timer.

		 @return		The system delta time (in seconds) 
						of this timer.
		 */
		double GetSystemDeltaTime() const;

		//---------------------------------------------------------------------
		// Member Methods: Total Delta Time
		//---------------------------------------------------------------------

		/**
		 Returns the total system delta time (in seconds)
		 of this timer.

		 @return		The total system delta time (in seconds)
						of this timer.
		 */
		double GetTotalSystemDeltaTime() const;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the current system time stamp of this timer.

		 @return		The current system time stamp of this timer.
		 */
		uint64_t GetCurrentSystemTimestamp() const;

		/**
		 Updates the last timestamp of this timer.
		 */
		void UpdateLastTimestamp() const;

		/**
		 Resets the delta time, total delta time and last timestamp of this timer.
		 */
		void ResetDeltaTime() const;

		/**
		 Updates the delta time, total delta time and last timestamp of this timer.
		 */
		void UpdateDeltaTime() const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The last timestamp of this timer.
		 */
		mutable uint64_t m_last_timestamp;

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
		 The time counter of this timer.
		 */
		mutable LARGE_INTEGER m_time_counter;

		/**
		 The time frequency of this timer.
		 */
		LARGE_INTEGER m_time_frequency;

		/**
		 The time period of this timer.
		 */
		double m_time_period;
	};
}