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

		/**
		 Returns the elapsed core time per processing core of this timer's process.

		 @return		The elapsed core time per processing core of this timer's process.
		 */
		double GetElapsedCoreTimePerCore() const {
			return GetElapsedCoreTime() / m_nb_processor_cores;
		}

		/**
		 Returns the elapsed core time of this timer's process.

		 @return		The elapsed core time of this timer's process.
		 */
		double GetElapsedCoreTime() const;

		/**
		 Returns the elapsed kernel mode time per processing core of this timer's process.

		 @return		The elapsed kernel mode time per processing core of this timer's process.
		 */
		double GetElapsedKernelModeTimePerCore() const {
			return GetElapsedKernelModeTime() / m_nb_processor_cores;
		}

		/**
		 Returns the elapsed kernel mode time of this timer's process.

		 @return		The elapsed kernel mode of this timer's process.
		 */
		double GetElapsedKernelModeTime() const;

		/**
		 Returns the elapsed user mode time per processing core of this timer's process.

		 @return		The elapsed user mode time per processing core of this timer's process.
		 */
		double GetElapsedUserModeTimePerCore() const {
			return GetElapsedUserModeTime() / m_nb_processor_cores;
		}

		/**
		 Returns the elapsed user mode time of this timer's process.

		 @return		The elapsed user mode time of this timer's process.
		 */
		double GetElapsedUserModeTime() const;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the initial time of this timer.
		 */
		void UpdateInitialTime();

		/**
		 Updates the last time of this timer.
		 */
		void UpdateLastTime() const;

		/**
		 Updates the elapsed time (and last time) of this timer.
		 */
		void UpdateElapsedTime() const;

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
		 The initial kernel mode time of this timer.
		 */
		uint64_t m_initial_kernel_mode_time;
		
		/**
		 The initial user mode time of this timer.
		 */
		uint64_t m_initial_user_mode_time;

		/**
		 The last kernel mode time of this timer.
		 */
		mutable uint64_t m_last_kernel_mode_time;
		
		/**
		 The last user mode time of this timer.
		 */
		mutable uint64_t m_last_user_mode_time;

		/**
		 The elapsed kernel mode time of this timer.
		 */
		mutable double m_elapsed_kernel_mode_time;

		/**
		 The elapsed user mode time of this timer.
		 */
		mutable double m_elapsed_user_mode_time;

		/**
		 Flag indicating whether this timer is running.
		 */
		bool m_running;
	};
}