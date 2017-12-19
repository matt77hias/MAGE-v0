//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\render_mode_script.hpp"
#include "scene\scene.hpp"
#include "imgui\imgui.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	RenderModeScript::RenderModeScript()
		: BehaviorScript(), 
		m_camera(),
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

	RenderModeScript::RenderModeScript(
		const RenderModeScript &script) = default;

	RenderModeScript::RenderModeScript(
		RenderModeScript &&script) noexcept = default;
	
	RenderModeScript::~RenderModeScript() = default;

	void RenderModeScript::Load() {
		ThrowIfFailed(HasOwner(),
			"This script needs to be attached to a node.");

		m_camera = GetOwner()->Get< PerspectiveCamera >();
		if (nullptr == m_camera) {
			m_camera = GetOwner()->Get< OrthographicCamera >();
		}
		ThrowIfFailed((nullptr != m_camera),
			"This script needs a camera component.");
	}

	void RenderModeScript::Update([[maybe_unused]] F64 delta_time) {
		ImGui::Begin("Configuration");

		ImGui::ListBox("Render Mode", 
			           &m_index,
			           m_render_mode_names.data(), 
			           static_cast< int >(m_render_mode_names.size()));
		m_camera->GetSettings().SetRenderMode(m_render_modes[m_index]);
	
		ImGui::Checkbox("Wireframe", &m_wireframe);
		if (m_wireframe) {
			m_camera->GetSettings().AddRenderLayer(RenderLayer::Wireframe);
		}
		else {
			m_camera->GetSettings().RemoveRenderLayer(RenderLayer::Wireframe);
		}

		ImGui::Checkbox("AABB", &m_aabb);
		if (m_aabb) {
			m_camera->GetSettings().AddRenderLayer(RenderLayer::AABB);
		}
		else {
			m_camera->GetSettings().RemoveRenderLayer(RenderLayer::AABB);
		}

		ImGui::End();
	}
}