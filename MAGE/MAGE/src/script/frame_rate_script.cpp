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

	const double FrameRateScript::s_resource_fetch_period = 1.00;

	FrameRateScript::FrameRateScript(SharedPtr< SpriteText > text)
		: BehaviorScript(), 
		m_accumulated_time(0.0), m_accumulated_nb_frames(0), 
		m_last_frames_per_second(0), m_last_milliseconds_per_frame(0.0),
		m_text(text) {}
	
	FrameRateScript::FrameRateScript(FrameRateScript &&script) = default;
	
	FrameRateScript::~FrameRateScript() = default;

	void FrameRateScript::Update(double delta_time) {
		m_accumulated_time += delta_time;
		++m_accumulated_nb_frames;
		
		if (m_accumulated_time > s_resource_fetch_period) {
			// FPS + SPF
			m_last_frames_per_second = static_cast< uint32_t >(m_accumulated_nb_frames / m_accumulated_time);
			m_last_milliseconds_per_frame = 1000.0 * m_accumulated_time / m_accumulated_nb_frames;
			m_accumulated_time = 0.0;
			m_accumulated_nb_frames = 0;
		}

		wchar_t buffer[32];
		_snwprintf_s(buffer, _countof(buffer), L"FPS: %u\nSPF: %.2lfms", 
			m_last_frames_per_second, m_last_milliseconds_per_frame);
		
		m_text->SetText(buffer);
	}
}