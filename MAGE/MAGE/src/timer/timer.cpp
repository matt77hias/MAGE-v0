//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "timer\timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Timer::Timer()
		: m_last_timestamp{}, m_delta_time(0), m_total_delta_time(0), m_running(false) {
		
		// Retrieve the frequency of the performance counter. 
		// The frequency of the performance counter is fixed at system boot 
		// and is consistent across all processors.
		QueryPerformanceFrequency(&m_time_frequency);
		// Calculate the period of the performance counter.
		m_time_period = 1.0 / (static_cast< double >(m_time_frequency.QuadPart));
	}

	void Timer::Start() noexcept {
		if (m_running) {
			return;
		}

		m_running = true;
		ResetDeltaTime();
	}

	void Timer::Stop() noexcept {
		if (!m_running) {
			return;
		}

		m_running = false;
		UpdateDeltaTime();
	}

	void Timer::Restart() noexcept {
		m_running = false;
		Start();
	}

	void Timer::Resume() noexcept {
		if (m_running) {
			return;
		}

		m_running = true;
		UpdateLastTimestamp();
	}

	double Timer::GetDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return m_time_period * static_cast< double >(m_delta_time);
	}

	double Timer::GetTotalDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		return m_time_period * static_cast< double >(m_total_delta_time);
	}

	void Timer::UpdateLastTimestamp() const noexcept {
		// Get the current timestamp of this timer.
		QueryPerformanceCounter(&m_last_timestamp);
	}

	void Timer::ResetDeltaTime() const noexcept {
		// Resets the delta time of this timer.
		m_delta_time       = 0;
		// Resets the total delta time of this timer.
		m_total_delta_time = 0;
		// Resets the last timestamp of this timer.
		UpdateLastTimestamp();
	}

	void Timer::UpdateDeltaTime() const noexcept {
		// Get the current timestamp of this timer.
		LARGE_INTEGER current_timestamp;
		QueryPerformanceCounter(&current_timestamp);

		// Updates the delta time of this timer.
		m_delta_time        = current_timestamp.QuadPart - m_last_timestamp.QuadPart;
		// Updates the total delta time of this timer.
		m_total_delta_time += m_delta_time;
		// Updates the last timestamp of this timer.
		m_last_timestamp    = current_timestamp;
	}
}