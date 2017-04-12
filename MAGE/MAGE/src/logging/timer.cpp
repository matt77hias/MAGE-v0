//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\timer.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Timer::Timer() 
		: m_last_timestamp(0), m_delta_time(0), m_total_delta_time(0), m_running(false) {
		
		// Retrieve the frequency of the performance counter. 
		// The frequency of the performance counter is fixed at system boot 
		// and is consistent across all processors.
		QueryPerformanceFrequency(&m_time_frequency);
		// Calculate the period of the performance counter.
		m_time_period = 1.0 / (static_cast< double >(m_time_frequency.QuadPart));
	}

	void Timer::Start() {
		if (m_running) {
			return;
		}

		m_running = true;
		ResetDeltaTime();
	}

	void Timer::Stop() {
		if (!m_running) {
			return;
		}

		m_running = false;
		UpdateDeltaTime();
	}

	void Timer::Restart() {
		m_running = false;
		Start();
	}

	void Timer::Resume() {
		if (m_running) {
			return;
		}

		m_running = true;
		UpdateLastTimestamp();
	}

	double Timer::GetSystemDeltaTime() const {
		if (m_running) {
			UpdateDeltaTime();
		}

		return m_time_period * static_cast< double >(m_delta_time);
	}

	double Timer::GetTotalSystemDeltaTime() const {
		if (m_running) {
			UpdateDeltaTime();
		}

		return m_time_period * static_cast< double >(m_total_delta_time);
	}

	uint64_t Timer::GetCurrentSystemTimestamp() const {
		// Retrieve the current value of the performance counter, 
		// which is a high resolution (< 1 µs) time stamp 
		// that can be used for time-interval measurements.
		QueryPerformanceCounter(&m_time_counter);
		
		Assert(m_time_counter.HighPart >= 0);
		return static_cast< uint64_t >(m_time_counter.LowPart) | static_cast< uint64_t >(m_time_counter.HighPart << 32);
	}

	void Timer::UpdateLastTimestamp() const {
		// Get the current timestamp of this timer.
		m_last_timestamp = GetCurrentSystemTimestamp();
	}

	void Timer::ResetDeltaTime() const {
		// Resets the delta time of this timer.
		m_delta_time       = 0;
		// Resets the total delta time of this timer.
		m_total_delta_time = 0;
		// Resets the last timestamp of this timer.
		UpdateLastTimestamp();
	}

	void Timer::UpdateDeltaTime() const {
		// Get the current timestamp of this timer.
		const uint64_t current_timestamp = GetCurrentSystemTimestamp();

		// Updates the delta time of this timer.
		m_delta_time        = current_timestamp - m_last_timestamp;
		// Updates the total delta time of this timer.
		m_total_delta_time += m_delta_time;
		// Updates the last timestamp of this timer.
		m_last_timestamp    = current_timestamp;
	}
}