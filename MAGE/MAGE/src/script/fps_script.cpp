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
		UNUSED(elapsed_time);
		UNUSED(scene);
		
		m_spf = (m_nb_frames * m_spf + elapsed_time) / (m_nb_frames + 1);
		++m_nb_frames;
		m_text->SetText(to_wstring(1.0 / m_spf));
	}
}