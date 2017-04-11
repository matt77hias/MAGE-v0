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
			m_seconds_per_frame(0.0), m_nb_frames(0),
			m_time(0.0), m_cpu_usage(0.0), m_ram_usage(0),
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

		virtual void Update(double elapsed_time) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		// FPS
		double m_seconds_per_frame;
		uint32_t m_nb_frames;
		
		// CPU + MEM
		double m_time;
		double m_cpu_usage;
		uint32_t m_ram_usage;
		UniquePtr< CPUMonitor > m_monitor;
		
		SharedPtr< SpriteText > m_text;
	};
}