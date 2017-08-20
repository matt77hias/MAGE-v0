//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\render_mode_script.hpp"
#include "input\keyboard.hpp"
#include "rendering\renderer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	RenderModeScript::RenderModeScript(CameraSettings *settings)
		: BehaviorScript(), m_settings(settings), 
		m_render_modes(), m_index(0) {
		
		m_render_modes.push_back(RenderMode::Default);
		m_render_modes.push_back(RenderMode::Solid);
		m_render_modes.push_back(RenderMode::DiffuseTexture);
		m_render_modes.push_back(RenderMode::UVTexture);
		m_render_modes.push_back(RenderMode::ShadingNormal);
		m_render_modes.push_back(RenderMode::TSNMShadingNormal);
		m_render_modes.push_back(RenderMode::Distance);
	}

	RenderModeScript::RenderModeScript(RenderModeScript &&script) = default;
	
	RenderModeScript::~RenderModeScript() = default;

	void RenderModeScript::Update(double delta_time) {
		UNUSED(delta_time);
		
		const Keyboard * const keyboard = Keyboard::Get();
		if (keyboard->GetKeyPress(DIK_RETURN)) {
			m_index = (m_index + 1) % m_render_modes.size();
			m_settings->SetRenderMode(m_render_modes[m_index]);
		}
		if (keyboard->GetKeyPress(DIK_B)) {
			m_settings->ToggleRenderLayer(RenderLayer::AABB);
		}
		if (keyboard->GetKeyPress(DIK_N)) {
			m_settings->ToggleRenderLayer(RenderLayer::Wireframe);
		}
	}
}