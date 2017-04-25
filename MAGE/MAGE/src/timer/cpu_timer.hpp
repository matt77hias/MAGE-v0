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
	 A class of CPU timers.
	 */
	class CPUTimer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a CPU timer.
		 */
		CPUTimer();

		/**
		 Constructs a CPU timer from the given CPU timer.

		 @param[in]		timer
						A reference to the CPU timer.
		 */
		CPUTimer(const CPUTimer &timer) = default;

		/**
		 Constructs a CPU timer by moving the given CPU timer.

		 @param[in]		timer
						A reference to the CPU timer to move.
		 */
		CPUTimer(CPUTimer &&timer) = default;

		/**
		 Destructs this CPU timer.
		 */
		~CPUTimer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given CPU timer to this CPU timer.

		 @param[in]		timer
						A reference to the CPU timer to copy from.
		 @return		A reference to the copy of the given CPU timer
						(i.e. this CPU timer).
		 */
		CPUTimer &operator=(const CPUTimer &timer) = default;

		/**
		 Moves the given CPU timer to this CPU timer.

		 @param[in]		timer
						A reference to the CPU timer to move.
		 @return		A reference to the moved CPU timer
						(i.e. this CPU timer).
		 */
		CPUTimer &operator=(CPUTimer &&timer) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts this CPU timer.
		 */
		void Start();

		/**
		 Stops this CPU timer.
		 */
		void Stop();

		/**
		 Restarts this CPU timer.
		 */
		void Restart();

		/**
		 Resumes this CPU timer.
		 */
		void Resume();

		//---------------------------------------------------------------------
		// Member Methods: Delta Time
		//---------------------------------------------------------------------

		/**
		 Returns the core delta time (in seconds) 
		 per processing core of this CPU timer's process.

		 @return		The core delta time (in seconds) 
						per processing core of this CPU timer's process.
		 */
		double GetCoreDeltaTimePerCore() const {
			return GetCoreDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the core delta time (in seconds) 
		 of this CPU timer's process.

		 @return		The core delta time (in seconds) 
						of this CPU timer's process.
		 */
		double GetCoreDeltaTime() const;

		/**
		 Returns the kernel mode delta time (in seconds) 
		 per processing core of this CPU timer's process.

		 @return		The kernel mode delta time (in seconds) 
						per processing core of this CPU timer's process.
		 */
		double GetKernelModeDeltaTimePerCore() const {
			return GetKernelModeDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the kernel mode delta time (in seconds) 
		 of this CPU timer's process.

		 @return		The kernel mode delta time (in seconds) 
						of this CPU timer's process.
		 */
		double GetKernelModeDeltaTime() const;

		/**
		 Returns the user mode delta time (in seconds) 
		 per processing core of this CPU timer's process.

		 @return		The user mode delta time (in seconds) 
						per processing core of this CPU timer's process.
		 */
		double GetUserModeDeltaTimePerCore() const {
			return GetUserModeDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the user mode delta time (in seconds) 
		 of this CPU timer's process.

		 @return		The user mode delta time (in seconds) 
						of this CPU timer's process.
		 */
		double GetUserModeDeltaTime() const;

		//---------------------------------------------------------------------
		// Member Methods: Total Delta Time
		//---------------------------------------------------------------------

		/**
		 Returns the total core delta time (in seconds)
		 per processing core of this CPU timer's process.

		 @return		The total core delta time (in seconds)
						per processing core of this CPU timer's process.
		 */
		double GetTotalCoreDeltaTimePerCore() const {
			return GetTotalCoreDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the total core delta time (in seconds)
		 of this CPU timer's process.

		 @return		The total core delta time (in seconds)
						of this CPU timer's process.
		 */
		double GetTotalCoreDeltaTime() const;

		/**
		 Returns the total kernel mode delta time (in seconds)
		 per processing core of this CPU timer's process.

		 @return		The total kernel mode delta time (in seconds)
						per processing core of this CPU timer's process.
		 */
		double GetTotalKernelModeDeltaTimePerCore() const {
			return GetTotalKernelModeDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the total kernel mode delta time (in seconds)
		 of this CPU timer's process.

		 @return		The total kernel mode delta time (in seconds)
						of this CPU timer's process.
		 */
		double GetTotalKernelModeDeltaTime() const;

		/**
		 Returns the total user mode delta time (in seconds)
		 per processing core of this CPU timer's process.

		 @return		The total user mode delta time (in seconds)
						per processing core of this CPU timer's process.
		 */
		double GetTotalUserModeDeltaTimePerCore() const {
			return GetTotalUserModeDeltaTime() / m_nb_processor_cores;
		}

		/**
		 Returns the total user mode delta time (in seconds)
		 of this CPU timer's process.

		 @return		The total user mode delta time (in seconds)
						of this CPU timer's process.
		 */
		double GetTotalUserModeDeltaTime() const;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the modes' last timestamps 
		 of this CPU timer's process.
		 */
		void UpdateLastTimestamp() const;

		/**
		 Resets the modes' delta times, total delta times and last timestamps 
		 of this CPU timer's process.
		 */
		void ResetDeltaTime() const;

		/**
		 Updates the modes' delta times, total delta times and last timestamps 
		 of this CPU timer's process.
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
		 The modes of this CPU timer.
		 */
		enum { 
			KERNEL_MODE = 0,
			USER_MODE   = 1,
			NB_MODES    = 2
		};

		/**
		 The modes' last timestamps of this CPU timer's process.
		 */
		mutable uint64_t m_last_timestamp[NB_MODES];
		
		/**
		 The modes' delta times (in seconds) of this CPU timer's process.
		 */
		mutable uint64_t m_delta_time[NB_MODES];

		/**
		 The modes' total delta times (in seconds) of this CPU timer's process.
		 */
		mutable uint64_t m_total_delta_time[NB_MODES];

		/**
		 Flag indicating whether this CPU timer is running.
		 */
		bool m_running;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The time period of CPU timers.
		 */
		static const double time_period;
	};
}