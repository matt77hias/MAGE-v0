#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "logging\timer.hpp"
#include "logging\cpu_timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class CPUMonitor final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a CPU monitor.
		 */
		CPUMonitor()
			: m_timer(new Timer()),
			m_cpu_timer(new CPUTimer()) {}

		/**
		 Constructs a CPU monitor from the given CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor.
		 */
		CPUMonitor(const CPUMonitor &cpu_monitor)
			: m_timer(new Timer(*cpu_monitor.m_timer)), 
			m_cpu_timer(new CPUTimer(*cpu_monitor.m_cpu_timer)) {}

		/**
		 Constructs a CPU monitor from the given CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor.
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
						A reference to the CPU monitor to copy from.
		 @return		A reference to the copy of the given CPU monitor
						(i.e. this CPU monitor).
		 */
		CPUMonitor &operator=(const CPUMonitor &cpu_monitor) {
			m_timer.reset(new Timer(*cpu_monitor.m_timer));
			m_cpu_timer.reset(new CPUTimer(*cpu_monitor.m_cpu_timer));
			return (*this);
		}

		/**
		 Copies the given CPU monitor to this CPU monitor.

		 @param[in]		cpu_monitor
						A reference to the CPU monitor to copy from.
		 @return		A reference to the copy of the given CPU monitor
						(i.e. this CPU monitor).
		 */
		CPUMonitor &operator=(CPUMonitor &&cpu_monitor) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts this CPU monitor.
		 */
		void Start() {
			m_timer->Start();
			m_cpu_timer->Start();
		}

		/**
		 Stops this CPU monitor.
		 */
		void Stop() {
			m_timer->Stop();
			m_cpu_timer->Stop();
		}

		/**
		 Restarts this CPU monitor.
		 */
		void Restart() {
			m_timer->Restart();
			m_cpu_timer->Restart();
		}

		/**
		 Resumes this CPU monitor.
		 */
		void Resume() {
			m_timer->Resume();
			m_cpu_timer->Resume();
		}

		/**
		 Returns the CPU delta percentage of this timer's process.

		 @return		The CPU delta percentage of this timer's process.
		 */
		double GetCPUDeltaPercentage() const {
			const double time     = m_timer->GetDeltaTime();
			const double cpu_time = m_cpu_timer->GetCoreDeltaTimePerCore();
			return 100.0 * (cpu_time / time);
		}

		/**
		 Returns the total CPU delta percentage of this timer's process.

		 @return		The total CPU delta percentage of this timer's process.
		 */
		double GetTotalCPUDeltaPercentage() const {
			const double time = m_timer->GetTotalDeltaTime();
			const double cpu_time = m_cpu_timer->GetTotalCoreDeltaTimePerCore();
			return 100.0 * (cpu_time / time);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		UniquePtr< Timer > m_timer;
		UniquePtr< CPUTimer > m_cpu_timer;
	};
}