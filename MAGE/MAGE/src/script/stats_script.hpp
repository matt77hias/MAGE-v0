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

	class StatsScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		static const double resource_fetch_period;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit StatsScript(SharedPtr< SpriteText > text)
			: BehaviorScript(), 
			m_accumulated_time(0.0), m_accumulated_nb_frames(0),
			m_last_cpu_usage(0.0), m_last_ram_usage(0),
			m_monitor(new CPUMonitor()), m_text(text) {
			m_monitor->Start();
		}
		StatsScript(const StatsScript &script) = delete;
		StatsScript(StatsScript &&script) = default;
		virtual ~StatsScript() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		StatsScript &operator=(const StatsScript &script) = delete;
		StatsScript &operator=(StatsScript &&script) = delete;

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
		uint32_t m_accumulated_nb_frames;
		uint32_t m_last_frames_per_second;
		double m_last_cpu_usage;
		uint32_t m_last_ram_usage;
		UniquePtr< CPUMonitor > m_monitor;
		
		SharedPtr< SpriteText > m_text;
	};
}