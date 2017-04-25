//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\frame_rate_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const double FrameRateScript::resource_fetch_period = 1.00;

	void FrameRateScript::Update(double delta_time) {
		m_accumulated_time += delta_time;
		++m_accumulated_nb_frames;
		
		if (m_accumulated_time > FrameRateScript::resource_fetch_period) {
			// FPS
			m_last_frames_per_second = static_cast< uint32_t >(m_accumulated_nb_frames / m_accumulated_time);
			m_accumulated_time = 0.0;
			m_accumulated_nb_frames = 0;
		}

		wchar_t buffer[16];
		_snwprintf_s(buffer, _countof(buffer), L"FPS: %u", m_last_frames_per_second);
		const wstring text = buffer;

		m_text->SetText(text);
	}
}