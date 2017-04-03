//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Timer::Timer() 
		: m_time0(0.0), m_elapsed(0.0), m_running(false) {
		// Retrieve the frequency of the performance counter. 
		// The frequency of the performance counter is fixed at system boot 
		// and is consistent across all processors.
		QueryPerformanceFrequency(&m_performance_frequency);
		// Calculate the period of the performance counter.
		m_performance_period = 1.0 / (static_cast< double >(m_performance_frequency.QuadPart));
	}

	double Timer::time() {
		// Retrieve the current value of the performance counter, 
		// which is a high resolution (< 1 µs) time stamp 
		// that can be used for time-interval measurements.
		QueryPerformanceCounter(&m_performance_counter);
		return static_cast< double >(m_performance_counter.QuadPart * m_performance_period);
	}

	void Timer::Start() {
		if (m_running) {
			return;
		}
		m_running = true;
		// Resets the initial time stamp.
		m_time0 = time();
	}

	void Timer::Stop() {
		if (!m_running) {
			return;
		}
		m_running = false;
		// Set the elapsed time.
		m_elapsed += time() - m_time0;
	}

	void Timer::Reset() {
		m_running = false;
		// Resets the elapsed time.
		m_elapsed = 0;
	}

	double Timer::Time() {
		if (m_running) {
			// Set the elapsed time.
			m_elapsed += time() - m_time0;
			// Resets the initial time stamp.
			m_time0 = time();
		}
		return m_elapsed;
	}
}