//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\stats_script.hpp"
#include "system\system_usage.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	const double StatsScript::resource_fetch_period = 1.0;

	void StatsScript::Update(double delta_time) {
		m_accumulated_time += delta_time;
		++m_accumulated_nb_frames;

		if (m_accumulated_time > StatsScript::resource_fetch_period) {
			// FPS
			m_last_frames_per_second = static_cast< uint32_t >(m_accumulated_nb_frames / m_accumulated_time);
			m_accumulated_time = 0.0;
			m_accumulated_nb_frames = 0;
			
			// CPU
			m_last_cpu_usage = m_monitor->GetCPUDeltaPercentage();
			
			// MEM
			m_last_ram_usage = static_cast< uint32_t >(GetVirtualMemoryUsage() >> 20);
		}

		wchar_t buffer[64];
		_snwprintf_s(buffer, _countof(buffer), L"FPS: %u\nCPU: %.1lf%%\nRAM: %uMB", 
			m_last_frames_per_second, m_last_cpu_usage, m_last_ram_usage);
		const wstring text = buffer;

		m_text->SetText(text);
	}
}