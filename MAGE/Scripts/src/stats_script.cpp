//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "stats_script.hpp"
#include "scene\scene.hpp"
#include "core\engine_statistics.hpp"
#include "system\system_usage.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	StatsScript::StatsScript()
		: BehaviorScript(),
		m_text(),
		m_accumulated_time(0.0), 
		m_accumulated_nb_frames(0),
		m_last_frames_per_second(0), 
		m_last_milliseconds_per_frame(0.0),
		m_last_cpu_usage(0.0), 
		m_last_ram_usage(0),
		m_monitor() {}

	StatsScript::StatsScript(const StatsScript &script) noexcept = default;

	StatsScript::StatsScript(StatsScript &&script) noexcept = default;
	
	StatsScript::~StatsScript() = default;

	void StatsScript::Load() {
		ThrowIfFailed(HasOwner(),
			"This script needs to be attached to a node.");
		
		m_text = GetOwner()->Get< SpriteText >();
		ThrowIfFailed((nullptr != m_text),
			"This script needs a sprite text component.");

		m_monitor.Start();
	}

	void StatsScript::Update([[maybe_unused]] F64 delta_time) {
		m_accumulated_time += delta_time;
		++m_accumulated_nb_frames;

		if (m_accumulated_time > s_resource_fetch_period) {
			// FPS + SPF
			m_last_frames_per_second 
				= static_cast< U32 >(m_accumulated_nb_frames / m_accumulated_time);
			m_last_milliseconds_per_frame 
				= 1000.0 * m_accumulated_time / m_accumulated_nb_frames;
			m_accumulated_time = 0.0;
			m_accumulated_nb_frames = 0;
			
			// CPU
			m_last_cpu_usage = m_monitor.GetCPUDeltaPercentage();
			
			// MEM
			m_last_ram_usage 
				= static_cast< U32 >(GetVirtualMemoryUsage() >> 20);
		}

		const SRGBA color = (m_last_frames_per_second > 120) ? 
								color::Green : color::Red;

		m_text->SetText(wstring(L"FPS: "));
		m_text->AppendText(ColorString(std::to_wstring(m_last_frames_per_second), color));
		
		wchar_t buffer[64];
		_snwprintf_s(buffer, std::size(buffer), 
			L"\nSPF: %.2lfms\nCPU: %.1lf%%\nRAM: %uMB\nDCs: %u", 
			m_last_milliseconds_per_frame, m_last_cpu_usage, m_last_ram_usage, 
			EngineStatistics::Get()->GetNumberOfDrawCalls());
		m_text->AppendText(wstring(buffer));
	}
}