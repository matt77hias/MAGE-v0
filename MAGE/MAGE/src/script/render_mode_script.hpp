#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "collection\collection.hpp"
#include "camera\camera_settings.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class RenderModeScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		RenderModeScript(CameraSettings *settings);
		RenderModeScript(const RenderModeScript &script) = delete;
		RenderModeScript(RenderModeScript &&script);
		virtual ~RenderModeScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		RenderModeScript &operator=(const RenderModeScript &script) = delete;
		RenderModeScript &operator=(RenderModeScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		CameraSettings * const m_settings;
		vector< RenderMode > m_render_modes;
		size_t m_index;
	};
}