#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "system\cpu_monitor.hpp"
#include "text\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SystemUsageScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		static const double resource_fetch_period;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SystemUsageScript(SharedPtr< SpriteText > text)
			: BehaviorScript(), m_accumulated_time(0.0),
			m_last_cpu_usage(0.0), m_last_ram_usage(0),
			m_monitor(), m_text(text) {}
		SystemUsageScript(const SystemUsageScript &script) = delete;
		SystemUsageScript(SystemUsageScript &&script) = default;
		virtual ~SystemUsageScript() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SystemUsageScript &operator=(const SystemUsageScript &script) = delete;
		SystemUsageScript &operator=(SystemUsageScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override;

		SpriteText *GetTransform() {
			return m_text.get();
		}
		const SpriteText *GetTransform() const {
			return m_text.get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		double m_accumulated_time;
		double m_last_cpu_usage;
		uint32_t m_last_ram_usage;
		UniquePtr< CPUMonitor > m_monitor;

		SharedPtr< SpriteText > m_text;
	};
}