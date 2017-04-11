//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\cpu_timer.hpp"
#include "logging\error.hpp"
#include "parallel\parallel.hpp"
#include "system\system_time.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	CPUTimer::CPUTimer() 
		: m_handle(GetCurrentProcess()), m_nb_processor_cores(NumberOfSystemCores()),
		m_initial_kernel_mode_time(0), m_initial_user_mode_time(0),
		m_last_kernel_mode_time(0), m_last_user_mode_time(0),
		m_elapsed_kernel_mode_time(0.0), m_elapsed_user_mode_time(0.0),
		m_running(false) {}

	void CPUTimer::Start() {
		if (m_running) {
			return;
		}

		m_running = true;

		UpdateInitialTimeStamp();
		// Reset the elapsed time.
		m_elapsed_kernel_mode_time = 0.0;
		m_elapsed_user_mode_time   = 0.0;
		UpdateLastTimeStamp();
	}

	void CPUTimer::Stop() {
		if (!m_running) {
			return;
		}

		m_running = false;

		UpdateElapsedTime();
	}

	void CPUTimer::Restart() {
		m_running = false;
		Start();
	}

	void CPUTimer::Resume() {
		if (m_running) {
			return;
		}

		m_running = true;

		UpdateLastTimeStamp();
	}

	double CPUTimer::GetElapsedCoreTime() const {
		if (m_running) {
			UpdateElapsedTime();
		}

		return m_elapsed_kernel_mode_time + m_elapsed_user_mode_time;
	}

	double CPUTimer::GetElapsedKernelModeTime() const {
		if (m_running) {
			UpdateElapsedTime();
		}

		return m_elapsed_kernel_mode_time;
	}

	double CPUTimer::GetElapsedUserModeTime() const {
		if (m_running) {
			UpdateElapsedTime();
		}

		return m_elapsed_user_mode_time;
	}

	void CPUTimer::UpdateInitialTimeStamp() {
		// Set the initial time stamp.
		GetCoreTime(m_handle, &m_initial_kernel_mode_time, &m_initial_user_mode_time);
	}

	void CPUTimer::UpdateLastTimeStamp() const {
		// Set the last time stamp.
		GetCoreTime(m_handle, &m_last_kernel_mode_time, &m_last_user_mode_time);
	}

	void CPUTimer::UpdateElapsedTime() const {
		uint64_t kernel_mode_time;
		uint64_t user_mode_time;
		GetCoreTime(m_handle, &kernel_mode_time, &user_mode_time);
		
		m_elapsed_kernel_mode_time = 0.0000001 * (kernel_mode_time - m_last_kernel_mode_time);
		m_elapsed_user_mode_time   = 0.0000001 * (user_mode_time   - m_last_user_mode_time);
		
		m_last_kernel_mode_time    = kernel_mode_time;
		m_last_user_mode_time      = user_mode_time;
	}
}