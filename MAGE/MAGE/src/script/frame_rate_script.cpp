#pragma once

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

	void FrameRateScript::Update(double delta_time) {
		// FPS
		m_seconds_per_frame = (m_nb_frames * m_seconds_per_frame + delta_time) / (m_nb_frames + 1);
		const uint32_t frames_per_second = static_cast< uint32_t >(1.0 / m_seconds_per_frame);
		++m_nb_frames;

		wchar_t buffer[16];
		_snwprintf_s(buffer, _countof(buffer), L"FPS: %u", frames_per_second);
		const wstring text = buffer;

		m_text->SetText(text);
	}
}