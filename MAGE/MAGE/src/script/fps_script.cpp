#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\fps_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	void FPSScript::Update(double elapsed_time, const Scene &scene) {
		UNUSED(scene);
		
		m_seconds_per_frame = (m_nb_frames * m_seconds_per_frame + elapsed_time) / (m_nb_frames + 1);
		const double m_frames_per_second = 1.0 / m_seconds_per_frame;
		++m_nb_frames;

		wchar_t buffer[10];
		_snwprintf_s(buffer, _countof(buffer), L"%u FPS", static_cast< uint32_t >(m_frames_per_second));
		const wstring text = buffer;

		m_text->SetText(text);
	}
}