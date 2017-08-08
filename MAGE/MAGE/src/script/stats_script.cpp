//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\stats_script.hpp"
#include "system\system_usage.hpp"
#include "core\engine_statistics.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	const double StatsScript::s_resource_fetch_period = 1.0;

	StatsScript::StatsScript(SharedPtr< SpriteText > text)
		: BehaviorScript(),
		m_accumulated_time(0.0), m_accumulated_nb_frames(0),
		m_last_frames_per_second(0), m_last_milliseconds_per_frame(0.0),
		m_last_cpu_usage(0.0), m_last_ram_usage(0),
		m_monitor(std::make_unique< CPUMonitor >()), m_text(text) {
		m_monitor->Start();
	}

	StatsScript::StatsScript(StatsScript &&script) = default;
	
	StatsScript::~StatsScript() = default;

	void StatsScript::Update(double delta_time) {
		m_accumulated_time += delta_time;
		++m_accumulated_nb_frames;

		if (m_accumulated_time > s_resource_fetch_period) {
			// FPS + SPF
			m_last_frames_per_second = static_cast< uint32_t >(m_accumulated_nb_frames / m_accumulated_time);
			m_last_milliseconds_per_frame = 1000.0 * m_accumulated_time / m_accumulated_nb_frames;
			m_accumulated_time = 0.0;
			m_accumulated_nb_frames = 0;
			
			// CPU
			m_last_cpu_usage = m_monitor->GetCPUDeltaPercentage();
			
			// MEM
			m_last_ram_usage = static_cast< uint32_t >(GetVirtualMemoryUsage() >> 20);
		}

		const XMVECTOR color = (m_last_frames_per_second > 120) ? Colors::Green : Colors::Red;

		m_text->SetText(L"FPS: ");
		m_text->AppendText(ColorString(std::to_wstring(m_last_frames_per_second), color));
		
		wchar_t buffer[64];
		_snwprintf_s(buffer, _countof(buffer), L"\nSPF: %.2lfms\nCPU: %.1lf%%\nRAM: %uMB\nDCs: %u", 
			m_last_milliseconds_per_frame, m_last_cpu_usage, m_last_ram_usage, 
			GetEngineStatistics()->GetNumberOfDrawCalls());
		m_text->AppendText(buffer);
	}
}