#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "text\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class FrameRateScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		static const double s_resource_fetch_period;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit FrameRateScript(SharedPtr< SpriteText > text);
		FrameRateScript(const FrameRateScript &script) = delete;
		FrameRateScript(FrameRateScript &&script);
		virtual ~FrameRateScript();
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		FrameRateScript &operator=(const FrameRateScript &script) = delete;
		FrameRateScript &operator=(FrameRateScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		double m_accumulated_time;
		uint32_t m_accumulated_nb_frames;
		uint32_t m_last_frames_per_second;
		double m_last_milliseconds_per_frame;
		
		SharedPtr< SpriteText > m_text;
	};
}