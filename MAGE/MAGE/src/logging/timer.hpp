#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

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

		/**
		 Returns the elapsed time of this timer.

		 @return		The elapsed time of this timer.
		 */
		double GetElapsedTime() const;

		/**
		 Returns the time of this timer.

		 @return		The time of this timer.
		 */
		double GetTime() const;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the initial time of this timer.
		 */
		void UpdateInitialTime() {
			// Set the initial time stamp.
			m_initial_time = GetTime();
		}

		/**
		 Updates the last time of this timer.
		 */
		void UpdateLastTime() const {
			// Set the last time stamp.
			m_last_time = GetTime();
		}

		/**
		 Updates the elapsed time (and last time) of this timer.
		 */
		void UpdateElapsedTime() const {
			// Set the elapsed time.
			m_elapsed_time = GetTime() - m_last_time;
			// Set the last time stamp.
			m_last_time = GetTime();
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The initial time stamp of this timer. 
		 */
		double m_initial_time;

		/**
		 The last time stamp of this timer.
		 */
		mutable double m_last_time;

		/**
		 The elapsed time of this timer.
		 */
		mutable double m_elapsed_time;

		/**
		 Flag indicating whether this timer is running.
		 */
		bool m_running;

		/**
		 The counter of this timer.
		 */
		mutable LARGE_INTEGER m_performance_counter;

		/**
		 The frequency of this timer.
		 */
		LARGE_INTEGER m_performance_frequency;

		/**
		 The period of this timer.
		*/
		double m_performance_period;
	};
}