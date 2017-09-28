//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\render_mode_script.hpp"
#include "input\keyboard.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	RenderModeScript::RenderModeScript(CameraSettings *settings)
		: BehaviorScript(), m_settings(settings), 
		m_render_modes(), m_index(0) {
		
		m_render_modes.push_back(RenderMode::Forward);
		m_render_modes.push_back(RenderMode::Deferred);
		m_render_modes.push_back(RenderMode::Solid);
		m_render_modes.push_back(RenderMode::DiffuseColor);
		m_render_modes.push_back(RenderMode::DiffuseReflectivity);
		m_render_modes.push_back(RenderMode::DiffuseReflectivityTexture);
		m_render_modes.push_back(RenderMode::SpecularColor);
		m_render_modes.push_back(RenderMode::SpecularReflectivity);
		m_render_modes.push_back(RenderMode::SpecularReflectivityTexture);
		m_render_modes.push_back(RenderMode::NormalTexture);
		m_render_modes.push_back(RenderMode::UVTexture);
		m_render_modes.push_back(RenderMode::Distance);
		m_render_modes.push_back(RenderMode::ShadingNormal);
		m_render_modes.push_back(RenderMode::TSNMShadingNormal);
		m_render_modes.push_back(RenderMode::None);
	}

	RenderModeScript::RenderModeScript(RenderModeScript &&script) = default;
	
	RenderModeScript::~RenderModeScript() = default;

	void RenderModeScript::Update(F64 delta_time) {
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