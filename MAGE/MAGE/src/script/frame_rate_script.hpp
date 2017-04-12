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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit FrameRateScript(SharedPtr< SpriteText > text)
			: BehaviorScript(), m_seconds_per_frame(0.0), m_nb_frames(0), 
			m_text(text) {}
		FrameRateScript(const FrameRateScript &script) = delete;
		FrameRateScript(FrameRateScript &&script) = default;
		virtual ~FrameRateScript() = default;
		
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
		double m_seconds_per_frame;
		uint32_t m_nb_frames;
		SharedPtr< SpriteText > m_text;
	};
}