#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "system\timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of CPU monitors for monitoring CPU usage.
	 */
	class CPUMonitor {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a CPU monitor.
		 */
		CPUMonitor() noexcept = default;

		/**
		 Constructs a CPU monitor from the given CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor to copy.
		 */
		CPUMonitor(const CPUMonitor& cpu_monitor) noexcept = default;

		/**
		 Constructs a CPU monitor by moving the given CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor to move.
		 */
		CPUMonitor(CPUMonitor&& cpu_monitor) noexcept = default;

		/**
		 Destructs this CPU monitor.
		 */
		~CPUMonitor() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given CPU monitor to this CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor to copy.
		 @return		A reference to the copy of the given CPU monitor (i.e.
						this CPU monitor).
		 */
		CPUMonitor& operator=(const CPUMonitor& cpu_monitor) noexcept = default;

		/**
		 Moves the given CPU monitor to this CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor to move.
		 @return		A reference to the moved CPU monitor (i.e. this CPU
						monitor).
		 */
		CPUMonitor& operator=(CPUMonitor&& cpu_monitor) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts this CPU monitor.
		 */
		void Start() noexcept {
			m_wall_clock_timer.Start();
			m_core_clock_timer.Start();
		}

		/**
		 Stops this CPU monitor.
		 */
		void Stop() noexcept {
			m_wall_clock_timer.Stop();
			m_core_clock_timer.Stop();
		}

		/**
		 Restarts this CPU monitor.
		 */
		void Restart() noexcept {
			m_wall_clock_timer.Restart();
			m_core_clock_timer.Restart();
		}

		/**
		 Resumes this CPU monitor.
		 */
		void Resume() noexcept {
			m_wall_clock_timer.Resume();
			m_core_clock_timer.Resume();
		}

		/**
		 Returns the CPU delta percentage of this CPU monitor's process.

		 @return		The CPU delta percentage of this CPU monitor's process.
		 */
		F64 GetCPUDeltaPercentage() noexcept {
			const auto wall_time = m_wall_clock_timer.GetDeltaTime();
			const auto core_time = m_core_clock_timer.GetDeltaTime();
			return 100.0 * (core_time / wall_time);
		}

		/**
		 Returns the total CPU delta percentage of this CPU monitor's process.

		 @return		The total CPU delta percentage of this CPU monitor's
						process.
		 */
		F64 GetTotalCPUDeltaPercentage() noexcept {
			const auto wall_time = m_wall_clock_timer.GetTotalDeltaTime();
			const auto core_time = m_core_clock_timer.GetTotalDeltaTime();
			return 100.0 * (core_time / wall_time);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The wall clock timer of this CPU monitor.
		 */
		WallClockTimer m_wall_clock_timer;

		/**
		 The core clock per core timer of this CPU monitor.
		 */
		CPUTimer m_core_clock_timer;
	};
}