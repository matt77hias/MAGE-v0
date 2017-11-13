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

		static const F64 s_resource_fetch_period;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit StatsScript(SpriteText *text);
		StatsScript(const StatsScript &script) = delete;
		StatsScript(StatsScript &&script);
		virtual ~StatsScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		StatsScript &operator=(const StatsScript &script) = delete;
		StatsScript &operator=(StatsScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update([[maybe_unused]] F64 delta_time) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		F64 m_accumulated_time;
		U32 m_accumulated_nb_frames;
		U32 m_last_frames_per_second;
		F64 m_last_milliseconds_per_frame;
		F64 m_last_cpu_usage;
		U32 m_last_ram_usage;
		UniquePtr< CPUMonitor > m_monitor;
		
		SpriteText * const m_text;
	};
}