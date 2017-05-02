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

		static const double resource_fetch_period;

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
		
		SharedPtr< SpriteText > m_text;
	};
}