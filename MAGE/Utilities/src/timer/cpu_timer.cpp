//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "timer\cpu_timer.hpp"
#include "parallel\parallel.hpp"
#include "system\system_time.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const U16 CPUTimer::s_nb_processor_cores = NumberOfSystemCores();

	CPUTimer::CPUTimer() noexcept
		: CPUTimer(GetCurrentProcess()) {}

	CPUTimer::CPUTimer(HANDLE process) noexcept
		: m_process(process),
		m_last_timestamp{},
		m_delta_time{},
		m_total_delta_time{},
		m_running(false) {

		Assert(m_process);
	}

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

	F64 CPUTimer::GetCoreDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return s_time_period * static_cast< F64 >(
			m_delta_time[GetKernelModeIndex()] 
			+ m_delta_time[GetUserModeIndex()]);
	}

	F64 CPUTimer::GetKernelModeDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return s_time_period * static_cast< F64 >(
			m_delta_time[GetKernelModeIndex()]);
	}

	F64 CPUTimer::GetUserModeDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return s_time_period * static_cast< F64 >(
			m_delta_time[GetUserModeIndex()]);
	}

	F64 CPUTimer::GetTotalCoreDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return s_time_period * static_cast< F64 >(
			m_total_delta_time[GetKernelModeIndex()] 
			+ m_total_delta_time[GetUserModeIndex()]);
	}

	F64 CPUTimer::GetTotalKernelModeDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return s_time_period * static_cast< F64 >(
			m_total_delta_time[GetKernelModeIndex()]);
	}

	F64 CPUTimer::GetTotalUserModeDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return s_time_period * static_cast< F64 >(
			m_total_delta_time[GetUserModeIndex()]);
	}

	void CPUTimer::UpdateLastTimestamp() const noexcept {
		// Get the current timestamp of this timer's process.
		GetCurrentCoreTimestamp(m_process,
			                    m_last_timestamp[GetKernelModeIndex()],
			                    m_last_timestamp[GetUserModeIndex()]);
	}

	void CPUTimer::ResetDeltaTime() const noexcept {
		// Resets the modes' delta times of this timer's process.
		m_delta_time[GetKernelModeIndex()]       = 0ull;
		m_delta_time[GetUserModeIndex()]         = 0ull;
		// Resets the modes' total delta times of this timer's process.
		m_total_delta_time[GetKernelModeIndex()] = 0ull;
		m_total_delta_time[GetUserModeIndex()]   = 0ull;
		// Resets the modes' last timestamps of this timer's process.
		UpdateLastTimestamp();
	}
	
	void CPUTimer::UpdateDeltaTime() const noexcept {
		// Get the current timestamp of this timer's process.
		U64 current_timestamp[2];
		GetCurrentCoreTimestamp(m_process,
			                    current_timestamp[GetKernelModeIndex()],
			                    current_timestamp[GetUserModeIndex()]);
		
		// Update the modes' delta times of this timer's process.
		m_delta_time[GetKernelModeIndex()] 
			= current_timestamp[GetKernelModeIndex()]
			- m_last_timestamp[GetKernelModeIndex()];
		m_delta_time[GetUserModeIndex()] 
			= current_timestamp[GetUserModeIndex()]
			- m_last_timestamp[GetUserModeIndex()];
		// Update the modes' total delta times of this timer's process.
		m_total_delta_time[GetKernelModeIndex()] 
			+= m_delta_time[GetKernelModeIndex()];
		m_total_delta_time[GetUserModeIndex()] 
			+= m_delta_time[GetUserModeIndex()];
		// Update the modes' last timestamps of this timer's process.
		m_last_timestamp[GetKernelModeIndex()] 
			= current_timestamp[GetKernelModeIndex()];
		m_last_timestamp[GetUserModeIndex()]   
			= current_timestamp[GetUserModeIndex()];
	}
}