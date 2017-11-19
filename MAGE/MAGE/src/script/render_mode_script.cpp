//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\render_mode_script.hpp"
#include "imgui\imgui.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	RenderModeScript::RenderModeScript(CameraSettings *settings)
		: BehaviorScript(), 
		m_settings(settings), 
		m_render_modes(), 
		m_render_mode_names(), 
		m_index(0),
		m_wireframe(false), 
		m_aabb(false) {
		
		m_render_modes.push_back(RenderMode::Forward);
		m_render_modes.push_back(RenderMode::Deferred);
		m_render_modes.push_back(RenderMode::Solid);
		m_render_modes.push_back(RenderMode::BaseColor);
		m_render_modes.push_back(RenderMode::BaseColorCoefficient);
		m_render_modes.push_back(RenderMode::BaseColorTexture);
		m_render_modes.push_back(RenderMode::Material);
		m_render_modes.push_back(RenderMode::MaterialCoefficient);
		m_render_modes.push_back(RenderMode::MaterialTexture);
		m_render_modes.push_back(RenderMode::NormalTexture);
		m_render_modes.push_back(RenderMode::UVTexture);
		m_render_modes.push_back(RenderMode::Distance);
		m_render_modes.push_back(RenderMode::ShadingNormal);
		m_render_modes.push_back(RenderMode::TSNMShadingNormal);
		m_render_modes.push_back(RenderMode::None);

		m_render_mode_names.push_back("Forward");
		m_render_mode_names.push_back("Deferred");
		m_render_mode_names.push_back("Solid");
		m_render_mode_names.push_back("Base Color");
		m_render_mode_names.push_back("Base Color Coefficient");
		m_render_mode_names.push_back("Base Color Texture");
		m_render_mode_names.push_back("Material");
		m_render_mode_names.push_back("Material Coefficient");
		m_render_mode_names.push_back("Material Texture");
		m_render_mode_names.push_back("Normal Texture");
		m_render_mode_names.push_back("UV Texture");
		m_render_mode_names.push_back("Distance");
		m_render_mode_names.push_back("Shading Normal");
		m_render_mode_names.push_back("TSNM Shading Normal");
		m_render_mode_names.push_back("None");

		Assert(m_render_modes.size() == m_render_mode_names.size());
	}

	RenderModeScript::RenderModeScript(RenderModeScript &&script) = default;
	
	RenderModeScript::~RenderModeScript() = default;

	void RenderModeScript::Update([[maybe_unused]] F64 delta_time) {
		ImGui::Begin("Configuration");

		ImGui::ListBox("Render Mode", 
			           &m_index,
			           m_render_mode_names.data(), 
			           static_cast< int >(m_render_mode_names.size()));
		m_settings->SetRenderMode(m_render_modes[m_index]);
	
		ImGui::Checkbox("Wireframe", &m_wireframe);
		if (m_wireframe) {
			m_settings->AddRenderLayer(RenderLayer::Wireframe);
		}
		else {
			m_settings->RemoveRenderLayer(RenderLayer::Wireframe);
		}

		ImGui::Checkbox("AABB", &m_aabb);
		if (m_aabb) {
			m_settings->AddRenderLayer(RenderLayer::AABB);
		}
		else {
			m_settings->RemoveRenderLayer(RenderLayer::AABB);
		}

		ImGui::End();
	}
}