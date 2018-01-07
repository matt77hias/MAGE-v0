#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	class RenderModeScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		RenderModeScript();
		RenderModeScript(const RenderModeScript &script);
		RenderModeScript(RenderModeScript &&script) noexcept;
		virtual ~RenderModeScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		RenderModeScript &operator=(const RenderModeScript &script) = delete;
		RenderModeScript &operator=(RenderModeScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load() override;
		virtual void Update([[maybe_unused]] F64 delta_time) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ProxyPtr< Camera > m_camera;
		std::vector< RenderMode > m_render_modes;
		std::vector< const char * > m_render_mode_names;
		int m_index;
		bool m_wireframe;
		bool m_aabb;
	};
}