//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "stats_script.hpp"
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
		m_accumulated_wall_clock_time(0.0),
		m_accumulated_nb_frames(0),
		m_last_frames_per_second(0), 
		m_last_ms_per_frame(0.0),
		m_last_cpu_usage(0.0), 
		m_last_ram_usage(0) {}

	StatsScript::StatsScript(const StatsScript& script) noexcept = default;

	StatsScript::StatsScript(StatsScript&& script) noexcept = default;
	
	StatsScript::~StatsScript() = default;

	StatsScript& StatsScript
		::operator=(const StatsScript& script) noexcept = default;

	StatsScript& StatsScript
		::operator=(StatsScript&& script) noexcept = default;

	void StatsScript::Load([[maybe_unused]] Engine& engine) {
		ThrowIfFailed(HasOwner(), 
					  "This script needs to be attached to a node.");
		
		m_text = GetOwner()->Get< rendering::SpriteText >();
		ThrowIfFailed((nullptr != m_text), 
					  "This script needs a sprite text component.");
	}

	void StatsScript::Update([[maybe_unused]] Engine& engine) {
		const auto wall_clock_delta_time 
			= static_cast< F32 >(engine.GetTime().GetWallClockDeltaTime());
		
		m_accumulated_wall_clock_time += wall_clock_delta_time;
		++m_accumulated_nb_frames;

		if (m_accumulated_wall_clock_time > s_resource_fetch_period) {
			// FPS + SPF
			m_last_frames_per_second = static_cast< U32 >(m_accumulated_nb_frames 
														  / m_accumulated_wall_clock_time);
			m_last_ms_per_frame = 1000.0f * m_accumulated_wall_clock_time 
				                          / m_accumulated_nb_frames;
			
			m_accumulated_wall_clock_time = 0.0f;
			m_accumulated_nb_frames       = 0u;
			
			// CPU
			const auto core_clock_delta_time
				= static_cast< F32 >(engine.GetTime().GetCoreClockDeltaTime());
			m_last_cpu_usage = 100.0f * core_clock_delta_time / wall_clock_delta_time;
			
			// MEM
			m_last_ram_usage = static_cast< U32 >(GetVirtualMemoryUsage() >> 20u);
		}

		RGBA color = (m_last_frames_per_second > 120u) ? color::Green : color::Red;

		m_text->SetText(wstring(L"FPS: "));
		m_text->AppendText(rendering::ColorString(
			std::to_wstring(m_last_frames_per_second), 
			std::move(color)));
		
		wchar_t buffer[64];
		_snwprintf_s(buffer, std::size(buffer), 
			         L"\nSPF: %.2fms\nCPU: %.1f%%\nRAM: %uMB\nDCs: %u", 
			         m_last_ms_per_frame, 
			         m_last_cpu_usage, 
			         m_last_ram_usage, 
			         rendering::Pipeline::s_nb_draws);
		m_text->AppendText(wstring(buffer));
	}
}