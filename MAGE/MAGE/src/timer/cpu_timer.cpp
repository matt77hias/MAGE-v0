//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "timer\cpu_timer.hpp"
#include "parallel\parallel.hpp"
#include "system\system_time.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const double CPUTimer::time_period = 0.0000001;

	CPUTimer::CPUTimer() 
		: m_handle(GetCurrentProcess()), m_nb_processor_cores(NumberOfSystemCores()),
		m_last_timestamp{}, m_delta_time{}, m_total_delta_time{}, m_running(false) {}

	void CPUTimer::Start() {
		if (m_running) {
			return;
		}

		m_running = true;
		ResetDeltaTime();
	}

	void CPUTimer::Stop() {
		if (!m_running) {
			return;
		}

		m_running = false;
		UpdateDeltaTime();
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
		UpdateLastTimestamp();
	}

	double CPUTimer::GetCoreDeltaTime() const {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_delta_time[KERNEL_MODE] + m_delta_time[USER_MODE]);
	}

	double CPUTimer::GetKernelModeDeltaTime() const {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_delta_time[KERNEL_MODE]);
	}

	double CPUTimer::GetUserModeDeltaTime() const {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_delta_time[USER_MODE]);
	}

	double CPUTimer::GetTotalCoreDeltaTime() const {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_total_delta_time[KERNEL_MODE] + m_total_delta_time[USER_MODE]);
	}

	double CPUTimer::GetTotalKernelModeDeltaTime() const {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_total_delta_time[KERNEL_MODE]);
	}

	double CPUTimer::GetTotalUserModeDeltaTime() const {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_total_delta_time[USER_MODE]);
	}

	void CPUTimer::UpdateLastTimestamp() const {
		// Get the current timestamp of this timer's process.
		GetCurrentCoreTimestamp(m_handle,
			&m_last_timestamp[KERNEL_MODE],
			&m_last_timestamp[USER_MODE]);
	}

	void CPUTimer::ResetDeltaTime() const {
		// Resets the modes' delta times of this timer's process.
		m_delta_time[KERNEL_MODE]       = 0;
		m_delta_time[USER_MODE]         = 0;
		// Resets the modes' total delta times of this timer's process.
		m_total_delta_time[KERNEL_MODE] = 0;
		m_total_delta_time[USER_MODE]   = 0;
		// Resets the modes' last timestamps of this timer's process.
		UpdateLastTimestamp();
	}

	void CPUTimer::UpdateDeltaTime() const {
		// Get the current timestamp of this timer's process.
		uint64_t current_timestamp[NB_MODES];
		GetCurrentCoreTimestamp(m_handle,
			&current_timestamp[KERNEL_MODE],
			&current_timestamp[USER_MODE]);
		
		// Update the modes' delta times of this timer's process.
		m_delta_time[KERNEL_MODE]        = (current_timestamp[KERNEL_MODE] - m_last_timestamp[KERNEL_MODE]);
		m_delta_time[USER_MODE]          = (current_timestamp[USER_MODE]   - m_last_timestamp[USER_MODE]);
		// Update the modes' total delta times of this timer's process.
		m_total_delta_time[KERNEL_MODE] += m_delta_time[KERNEL_MODE];
		m_total_delta_time[USER_MODE]   += m_delta_time[USER_MODE];
		// Update the modes' last timestamps of this timer's process.
		m_last_timestamp[KERNEL_MODE]    = current_timestamp[KERNEL_MODE];
		m_last_timestamp[USER_MODE]      = current_timestamp[USER_MODE];
	}
}