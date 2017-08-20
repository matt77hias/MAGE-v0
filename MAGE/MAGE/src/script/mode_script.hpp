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

	class ModeScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ModeScript(CameraSettings *settings);
		ModeScript(const ModeScript &script) = delete;
		ModeScript(ModeScript &&script);
		virtual ~ModeScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ModeScript &operator=(const ModeScript &script) = delete;
		ModeScript &operator=(ModeScript &&script) = delete;

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