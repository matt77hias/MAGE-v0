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

	void CPUTimer::Start() noexcept {
		if (m_running) {
			return;
		}

		m_running = true;
		ResetDeltaTime();
	}

	void CPUTimer::Stop() noexcept {
		if (!m_running) {
			return;
		}

		m_running = false;
		UpdateDeltaTime();
	}

	void CPUTimer::Restart() noexcept {
		m_running = false;
		Start();
	}

	void CPUTimer::Resume() noexcept {
		if (m_running) {
			return;
		}

		m_running = true;
		UpdateLastTimestamp();
	}

	double CPUTimer::GetCoreDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_delta_time[KERNEL] + m_delta_time[USER]);
	}

	double CPUTimer::GetKernelModeDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_delta_time[KERNEL]);
	}

	double CPUTimer::GetUserModeDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_delta_time[USER]);
	}

	double CPUTimer::GetTotalCoreDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_total_delta_time[KERNEL] + m_total_delta_time[USER]);
	}

	double CPUTimer::GetTotalKernelModeDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_total_delta_time[KERNEL]);
	}

	double CPUTimer::GetTotalUserModeDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return time_period * static_cast< double >(m_total_delta_time[USER]);
	}

	void CPUTimer::UpdateLastTimestamp() const noexcept {
		// Get the current timestamp of this timer's process.
		GetCurrentCoreTimestamp(m_handle,
			&m_last_timestamp[KERNEL],
			&m_last_timestamp[USER]);
	}

	void CPUTimer::ResetDeltaTime() const noexcept {
		// Resets the modes' delta times of this timer's process.
		m_delta_time[KERNEL]       = 0;
		m_delta_time[USER]         = 0;
		// Resets the modes' total delta times of this timer's process.
		m_total_delta_time[KERNEL] = 0;
		m_total_delta_time[USER]   = 0;
		// Resets the modes' last timestamps of this timer's process.
		UpdateLastTimestamp();
	}

	void CPUTimer::UpdateDeltaTime() const noexcept {
		// Get the current timestamp of this timer's process.
		uint64_t current_timestamp[COUNT];
		GetCurrentCoreTimestamp(m_handle,
			&current_timestamp[KERNEL],
			&current_timestamp[USER]);
		
		// Update the modes' delta times of this timer's process.
		m_delta_time[KERNEL]        = (current_timestamp[KERNEL] - m_last_timestamp[KERNEL]);
		m_delta_time[USER]          = (current_timestamp[USER]   - m_last_timestamp[USER]);
		// Update the modes' total delta times of this timer's process.
		m_total_delta_time[KERNEL] += m_delta_time[KERNEL];
		m_total_delta_time[USER]   += m_delta_time[USER];
		// Update the modes' last timestamps of this timer's process.
		m_last_timestamp[KERNEL]    = current_timestamp[KERNEL];
		m_last_timestamp[USER]      = current_timestamp[USER];
	}
}