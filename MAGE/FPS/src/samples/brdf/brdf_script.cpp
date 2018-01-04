//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\brdf\brdf_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	BRDFScript::BRDFScript(std::vector< ProxyPtr< Node > > models)
		: m_camera(),
		m_models(std::move(models)), 
		m_model_index(0),
		m_wireframe(false),
		m_aabb(false),
		m_material(), 
		m_tsnm(false), 
		m_tsnm_texture(ResourceManager::Get()->GetOrCreate< Texture >(
			L"assets/textures/tsnm/rock 4.dds")),
		m_brdf_index(0) {

		m_model_names.reserve(models.size());
		for (const auto &node : m_models) {
			m_model_names.push_back(node->GetName().c_str());
			node->SetState(State::Passive);
		}
		m_models[m_model_index]->SetState(State::Active);
	}

	BRDFScript::BRDFScript(const BRDFScript &script) = default;

	BRDFScript::BRDFScript(BRDFScript &&script) noexcept = default;

	BRDFScript::~BRDFScript() = default;

	void BRDFScript::Load() {
		ThrowIfFailed(HasOwner(),
			"This script needs to be attached to a node.");

		m_camera = GetOwner()->Get< PerspectiveCamera >();
		if (nullptr == m_camera) {
			m_camera = GetOwner()->Get< OrthographicCamera >();
		}
		ThrowIfFailed((nullptr != m_camera),
			"This script needs a camera component.");
	}

	void BRDFScript::Update([[maybe_unused]] F64 time) {
		ImGui::Begin("Configuration");
			
		if (ImGui::TreeNode("Model")) {
			// Model
			m_models[m_model_index]->SetState(State::Passive);
			ImGui::ListBox("Model", &m_model_index, 
				m_model_names.data(), static_cast< int >(m_model_names.size()));
			m_models[m_model_index]->SetState(State::Active);

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
			
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Material")) {
			// Material: Base Color
			ImGui::ColorEdit4("Base Color", m_material.GetBaseColor().GetData());
			
			// Material: Roughness
			F32 roughness = m_material.GetRoughness();
			ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f);
			m_material.SetRoughness(roughness);
			
			// Material: Metalness
			F32 metalness = m_material.GetMetalness();
			ImGui::SliderFloat("Metalness", &metalness, 0.0f, 1.0f);
			m_material.SetMetalness(metalness);

			// Material: Normal Mapping
			ImGui::Checkbox("Normal mapping", &m_tsnm);
			if (m_tsnm) {
				m_material.SetNormalTexture(m_tsnm_texture);
			}
			else {
				m_material.SetNormalTexture(nullptr);
			}

			// Material: Light Interaction
			bool light_interaction = m_material.InteractsWithLight();
			ImGui::Checkbox("Light interaction", &light_interaction);
			m_material.SetLightInteraction(light_interaction);

			// Material: BRDF
			if (light_interaction) {
				static constexpr const char *brdf_names[] = {
					"Lambertian",
					"Frostbite",
					"Cook-Torrance",
					"Blinn-Phong",
					"Ward-Duer"
				};
				static constexpr BRDFType brdfs[] = {
					BRDFType::Lambertian,
					BRDFType::Frostbite,
					BRDFType::CookTorrance,
					BRDFType::BlinnPhong,
					BRDFType::WardDuer
				};
				ImGui::ListBox("BRDF", 
					           &m_brdf_index, 
					           brdf_names, 
					           static_cast< int >(std::size(brdf_names)));
				
				m_camera->GetSettings().SetBRDF(brdfs[m_brdf_index]);
			}

			// Set the material.
			m_models[m_model_index]->Get< Model >()->GetMaterial() = m_material;

			ImGui::TreePop();
		}
	
		ImGui::End();
	}
}