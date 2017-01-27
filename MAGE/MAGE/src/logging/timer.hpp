#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "support.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of (high precision) timers.
	 */
	class Timer {

	public:

		/**
		 Constructs a timer.
		 */
		Timer();

		/**
		 Destructs this timer.
		 */
		virtual ~Timer() {}

		/**
		 Starts this timer.
		 */
		void Start();

		/**
		 Stops this timer.
		 */
		void Stop();

		/**
		 Resets this timer.
		 */
		void Reset();

		/**
		 Restarts this timer.
		 */
		void Restart() {
			Reset();
			Start();
		}

		/**
		 Returns the elapsed time of this timer.

		 @return		The elapsed time of this timer.
		 */
		double Time();

	protected:

		/**
		 Returns the time of this timer.

		 @return		The time of this timer.
		 @note			This member method encapsulates the performance
						of the underlying counter/frequency processing.
		*/
		double time();

		/**
		 The initial time stamp of this timer. 
		 */
		double m_time0;

		/**
		 The elapsed time of this timer.
		 */
		double m_elapsed;

		/**
		 Flag indicating whether this timer is running.
		 */
		bool m_running;

		/**
		 The counter of this timer.
		 */
		LARGE_INTEGER m_performance_counter;

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