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

	Timer::Timer() noexcept
		: m_clock(),
		m_last_timestamp(TimeStamp::min()),
		m_delta_time(TimeInterval::min()),
		m_total_delta_time(TimeInterval::min()),
		m_running(false) {}

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
		m_last_timestamp = m_clock.now();
	}

	F64 Timer::GetDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		using Seconds = std::chrono::duration< F64 >;
		return std::chrono::duration_cast< Seconds >(m_delta_time).count();
	}

	F64 Timer::GetTotalDeltaTime() const noexcept {
		if (m_running) {
			UpdateDeltaTime();
		}

		using Seconds = std::chrono::duration< F64 >;
		return std::chrono::duration_cast< Seconds >(m_total_delta_time).count();
	}

	void Timer::ResetDeltaTime() const noexcept {
		// Resets the delta time of this timer.
		m_delta_time       = TimeInterval::min();
		// Resets the total delta time of this timer.
		m_total_delta_time = TimeInterval::min();
		// Resets the last timestamp of this timer.
		m_last_timestamp   = m_clock.now();
	}

	void Timer::UpdateDeltaTime() const noexcept {
		// Get the current timestamp of this timer.
		const TimeStamp current_timestamp = m_clock.now();

		// Updates the delta time of this timer.
		m_delta_time        = current_timestamp - m_last_timestamp;
		// Updates the total delta time of this timer.
		m_total_delta_time += m_delta_time;
		// Updates the last timestamp of this timer.
		m_last_timestamp    = current_timestamp;
	}
}