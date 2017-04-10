#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\system_usage_script.hpp"
#include "system\system.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	const double SystemUsageScript::resource_fetch_period = 0.25;

	void SystemUsageScript::Update(double elapsed_time, const Scene &scene) {
		UNUSED(elapsed_time);
		UNUSED(scene);

		m_time += elapsed_time;
		if (m_time > SystemUsageScript::resource_fetch_period) {
			const uint32_t cpu_usage = static_cast<uint32_t>(GetProcessorUsage());
			const uint32_t ram_usage = static_cast<uint32_t>(GetPhysicalMemoryUsage() >> 20);

			m_cpu_usage = (cpu_usage) ? cpu_usage : m_cpu_usage;
			m_ram_usage = (ram_usage) ? ram_usage : m_ram_usage;

			m_time = 0.0;
		}

		wchar_t buffer[32];
		_snwprintf_s(buffer, _countof(buffer), L"CPU: %u %%\nRAM: %u MB", m_cpu_usage, m_ram_usage);
		const wstring text = buffer;

		m_text->SetText(text);
	}
}