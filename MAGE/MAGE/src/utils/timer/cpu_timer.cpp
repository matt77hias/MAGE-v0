//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\timer\cpu_timer.hpp"
#include "utils\parallel\parallel.hpp"
#include "utils\system\system_time.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const F64 CPUTimer::s_time_period = 0.0000001;

	CPUTimer::CPUTimer() 
		: m_handle(GetCurrentProcess()), 
		m_nb_processor_cores(NumberOfSystemCores()),
		m_last_timestamp{}, 
		m_delta_time{}, 
		m_total_delta_time{}, 
		m_running(false) {}

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
		GetCurrentCoreTimestamp(m_handle,
			&m_last_timestamp[GetKernelModeIndex()],
			&m_last_timestamp[GetUserModeIndex()]);
	}

	void CPUTimer::ResetDeltaTime() const noexcept {
		
		const size_t kernel_mode_index = GetKernelModeIndex();
		const size_t user_mode_index   = GetUserModeIndex();
		
		// Resets the modes' delta times of this timer's process.
		m_delta_time[kernel_mode_index]       = 0;
		m_delta_time[user_mode_index]         = 0;
		// Resets the modes' total delta times of this timer's process.
		m_total_delta_time[kernel_mode_index] = 0;
		m_total_delta_time[user_mode_index]   = 0;
		// Resets the modes' last timestamps of this timer's process.
		UpdateLastTimestamp();
	}
	
	void CPUTimer::UpdateDeltaTime() const noexcept {

		const size_t kernel_mode_index = GetKernelModeIndex();
		const size_t user_mode_index   = GetUserModeIndex();

		// Get the current timestamp of this timer's process.
		U64 current_timestamp[2];
		GetCurrentCoreTimestamp(m_handle,
			&current_timestamp[kernel_mode_index],
			&current_timestamp[user_mode_index]);
		
		// Update the modes' delta times of this timer's process.
		m_delta_time[kernel_mode_index] = current_timestamp[kernel_mode_index] 
										 - m_last_timestamp[kernel_mode_index];
		m_delta_time[user_mode_index]   = current_timestamp[user_mode_index] 
										 - m_last_timestamp[user_mode_index];
		// Update the modes' total delta times of this timer's process.
		m_total_delta_time[kernel_mode_index] += m_delta_time[kernel_mode_index];
		m_total_delta_time[user_mode_index]   += m_delta_time[user_mode_index];
		// Update the modes' last timestamps of this timer's process.
		m_last_timestamp[kernel_mode_index] = current_timestamp[kernel_mode_index];
		m_last_timestamp[user_mode_index]   = current_timestamp[user_mode_index];
	}
}