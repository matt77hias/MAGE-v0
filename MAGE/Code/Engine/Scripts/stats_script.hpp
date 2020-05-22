#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\script\behavior_script.hpp"
#include "scene\sprite\sprite_text.hpp"
#include "system\cpu_monitor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	class StatsScript : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		StatsScript();
		StatsScript(const StatsScript& script) noexcept;
		StatsScript(StatsScript&& script) noexcept;
		virtual ~StatsScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		StatsScript& operator=(const StatsScript& script) noexcept;
		StatsScript& operator=(StatsScript&& script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load([[maybe_unused]] Engine& engine) override;
		virtual void Update([[maybe_unused]] Engine& engine) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ProxyPtr< rendering::SpriteText > m_text;

		U32 m_accumulated_nb_frames;
		TimeIntervalSeconds m_prev_wall_clock_time;
		TimeIntervalSeconds m_prev_core_clock_time;
		U32 m_fps;
		F64 m_spf;
		F64 m_cpu;
		U64 m_ram;
	};
}