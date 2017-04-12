#pragma once

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

	const double StatsScript::resource_fetch_period = 1.00;

	void StatsScript::Update(double elapsed_time) {
		// FPS
		m_seconds_per_frame = (m_nb_frames * m_seconds_per_frame + elapsed_time) / (m_nb_frames + 1);
		const uint32_t frames_per_second = static_cast< uint32_t >(1.0 / m_seconds_per_frame);
		++m_nb_frames;

		// CPU + MEM
		m_time += elapsed_time;
		if (m_time > StatsScript::resource_fetch_period) {
			m_cpu_usage = m_monitor->GetCPUDeltaPercentage();
			m_ram_usage = static_cast< uint32_t >(GetVirtualMemoryUsage() >> 20);
			m_time = 0.0;
		}

		wchar_t buffer[64];
		_snwprintf_s(buffer, _countof(buffer), L"FPS: %u\nCPU: %.1lf %%\nRAM: %u MB", 
			frames_per_second, m_cpu_usage, m_ram_usage);
		const wstring text = buffer;

		m_text->SetText(text);
	}
}