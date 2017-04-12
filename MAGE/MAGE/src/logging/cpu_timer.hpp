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
	 A class of cpu timers.
	 */
	class CPUTimer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a timer.
		 */
		CPUTimer();

		/**
		 Constructs a timer from the given timer.

		 @param[in]		timer
						A reference to the timer.
		 */
		CPUTimer(const CPUTimer &timer) = default;

		/**
		 Constructs a timer from the given timer.

		 @param[in]		timer
						A reference to the timer.
		 */
		CPUTimer(CPUTimer &&timer) = default;

		/**
		 Destructs this timer.
		 */
		~CPUTimer() = default;

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
		CPUTimer &operator=(const CPUTimer &timer) = default;

		/**
		 Copies the given timer to this timer.

		 @param[in]		timer
						A reference to the timer to copy from.
		 @return		A reference to the copy of the given timer
						(i.e. this timer).
		 */
		CPUTimer &operator=(CPUTimer &&timer) = default;

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
		 Returns the core delta time (in seconds) 
		 per processing core of this timer's process.

		 @return		The core delta time (in seconds) 
						per processing core of this timer's process.
		 */
		double GetCoreDeltaTimePerCore() const {
			return GetCoreDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the core delta time (in seconds) 
		 of this timer's process.

		 @return		The core delta time (in seconds) 
						of this timer's process.
		 */
		double GetCoreDeltaTime() const;

		/**
		 Returns the kernel mode delta time (in seconds) 
		 per processing core of this timer's process.

		 @return		The kernel mode delta time (in seconds) 
						per processing core of this timer's process.
		 */
		double GetKernelModeDeltaTimePerCore() const {
			return GetKernelModeDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the kernel mode delta time (in seconds) 
		 of this timer's process.

		 @return		The kernel mode delta time (in seconds) 
						of this timer's process.
		 */
		double GetKernelModeDeltaTime() const;

		/**
		 Returns the user mode delta time (in seconds) 
		 per processing core of this timer's process.

		 @return		The user mode delta time (in seconds) 
						per processing core of this timer's process.
		 */
		double GetUserModeDeltaTimePerCore() const {
			return GetUserModeDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the user mode delta time (in seconds) 
		 of this timer's process.

		 @return		The user mode delta time (in seconds) 
						of this timer's process.
		 */
		double GetUserModeDeltaTime() const;

		//---------------------------------------------------------------------
		// Member Methods: Total Delta Time
		//---------------------------------------------------------------------

		/**
		 Returns the total core delta time (in seconds)
		 per processing core of this timer's process.

		 @return		The total core delta time (in seconds)
						per processing core of this timer's process.
		 */
		double GetTotalCoreDeltaTimePerCore() const {
			return GetTotalCoreDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the total core delta time (in seconds)
		 of this timer's process.

		 @return		The total core delta time (in seconds)
						of this timer's process.
		 */
		double GetTotalCoreDeltaTime() const;

		/**
		 Returns the total kernel mode delta time (in seconds)
		 per processing core of this timer's process.

		 @return		The total kernel mode delta time (in seconds)
						per processing core of this timer's process.
		 */
		double GetTotalKernelModeDeltaTimePerCore() const {
			return GetTotalKernelModeDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the total kernel mode delta time (in seconds)
		 of this timer's process.

		 @return		The total kernel mode delta time (in seconds)
						of this timer's process.
		 */
		double GetTotalKernelModeDeltaTime() const;

		/**
		 Returns the total user mode delta time (in seconds)
		 per processing core of this timer's process.

		 @return		The total user mode delta time (in seconds)
						per processing core of this timer's process.
		 */
		double GetTotalUserModeDeltaTimePerCore() const {
			return GetTotalUserModeDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the total user mode delta time (in seconds)
		 of this timer's process.

		 @return		The total user mode delta time (in seconds)
						of this timer's process.
		 */
		double GetTotalUserModeDeltaTime() const;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the modes' last timestamps 
		 of this timer's process.
		 */
		void UpdateLastTimestamp() const;

		/**
		 Resets the modes' delta times, total delta times and last timestamps 
		 of this timer's process.
		 */
		void ResetDeltaTime() const;

		/**
		 Updates the modes' delta times, total delta times and last timestamps 
		 of this timer's process.
		 */
		void UpdateDeltaTime() const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The process handle.
		 */
		HANDLE m_handle;

		/**
		 The number of processor cores.
		 */
		size_t m_nb_processor_cores;
		
		/**
		 The modes of this timer.
		 */
		enum { 
			KERNEL_MODE = 0,
			USER_MODE   = 1,
			NB_MODES    = 2
		};

		/**
		 The modes' last timestamps of this timer's process.
		 */
		mutable uint64_t m_last_timestamp[NB_MODES];
		
		/**
		 The modes' delta times (in seconds) of this timer's process.
		 */
		mutable uint64_t m_delta_time[NB_MODES];

		/**
		 The modes' total delta times (in seconds) of this timer's process.
		 */
		mutable uint64_t m_total_delta_time[NB_MODES];

		/**
		 Flag indicating whether this timer is running.
		 */
		bool m_running;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The time period.
		 */
		static const double time_period;
	};
}