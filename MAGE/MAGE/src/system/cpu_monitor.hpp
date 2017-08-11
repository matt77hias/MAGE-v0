#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "timer\timer.hpp"
#include "timer\cpu_timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of CPU monitors for monitoring CPU usage.
	 */
	class CPUMonitor final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a CPU monitor.
		 */
		CPUMonitor()
			: m_timer(MakeUnique< Timer >()),
			m_cpu_timer(MakeUnique< CPUTimer >()) {}

		/**
		 Constructs a CPU monitor from the given CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor to copy.
		 */
		CPUMonitor(const CPUMonitor &cpu_monitor)
			: m_timer(MakeUnique< Timer >(*cpu_monitor.m_timer)), 
			m_cpu_timer(MakeUnique< CPUTimer >(*cpu_monitor.m_cpu_timer)) {}

		/**
		 Constructs a CPU monitor by moving the given CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor to move.
		 */
		CPUMonitor(CPUMonitor &&cpu_monitor) = default;

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
		 @return		A reference to the copy of the given CPU monitor
						(i.e. this CPU monitor).
		 */
		CPUMonitor &operator=(const CPUMonitor &cpu_monitor) {
			m_timer     = MakeUnique< Timer >(*cpu_monitor.m_timer);
			m_cpu_timer = MakeUnique< CPUTimer >(*cpu_monitor.m_cpu_timer);
			return (*this);
		}

		/**
		 Moves the given CPU monitor to this CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor to move.
		 @return		A reference to the moved CPU monitor
						(i.e. this CPU monitor).
		 */
		CPUMonitor &operator=(CPUMonitor &&cpu_monitor) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts this CPU monitor.
		 */
		void Start() noexcept {
			m_timer->Start();
			m_cpu_timer->Start();
		}

		/**
		 Stops this CPU monitor.
		 */
		void Stop() noexcept {
			m_timer->Stop();
			m_cpu_timer->Stop();
		}

		/**
		 Restarts this CPU monitor.
		 */
		void Restart() noexcept {
			m_timer->Restart();
			m_cpu_timer->Restart();
		}

		/**
		 Resumes this CPU monitor.
		 */
		void Resume() noexcept {
			m_timer->Resume();
			m_cpu_timer->Resume();
		}

		/**
		 Returns the CPU delta percentage of this CPU monitor's process.

		 @return		The CPU delta percentage of this CPU monitor's process.
		 */
		double GetCPUDeltaPercentage() const noexcept {
			const double time     = m_timer->GetDeltaTime();
			const double cpu_time = m_cpu_timer->GetCoreDeltaTimePerCore();
			return 100.0 * (cpu_time / time);
		}

		/**
		 Returns the total CPU delta percentage of this CPU monitor's process.

		 @return		The total CPU delta percentage of this CPU monitor's process.
		 */
		double GetTotalCPUDeltaPercentage() const noexcept {
			const double time     = m_timer->GetTotalDeltaTime();
			const double cpu_time = m_cpu_timer->GetTotalCoreDeltaTimePerCore();
			return 100.0 * (cpu_time / time);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the wallclock timer of this CPU monitor.
		 */
		UniquePtr< Timer > m_timer;

		/**
		 A pointer to the CPU core timer of this CPU monitor.
		 */
		UniquePtr< CPUTimer > m_cpu_timer;
	};
}