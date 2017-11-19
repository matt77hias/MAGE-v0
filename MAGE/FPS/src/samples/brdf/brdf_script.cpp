//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\brdf\brdf_script.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	BRDFScript::BRDFScript(CameraSettings *settings,
		const vector< ModelNode * > &models)
		: m_settings(settings),
		m_models(models), 
		m_model_index(0),
		m_wireframe(false),
		m_aabb(false),
		m_material(), 
		m_tsnm(false), 
		m_tsnm_texture(ResourceManager::Get()->GetOrCreateTexture(L"assets/textures/tsnm/rock 4.dds")),
		m_brdf_index(0) {

		Assert(m_settings);

		m_model_names.reserve(models.size());
		for (const auto &node : m_models) {
			m_model_names.push_back(node->GetName().c_str());
			node->Deactivate();
		}
		m_models[m_model_index]->Activate();
	}

	BRDFScript::BRDFScript(BRDFScript &&script) = default;

	BRDFScript::~BRDFScript() = default;

	void BRDFScript::Update([[maybe_unused]] F64 time) {
		ImGui::Begin("Configuration");
			
		if (ImGui::TreeNode("Model")) {
			// Model
			m_models[m_model_index]->Deactivate();
			ImGui::ListBox("Model", &m_model_index, 
				m_model_names.data(), static_cast< int >(m_model_names.size()));
			m_models[m_model_index]->Activate();

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
			
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Material")) {
			// Material: Base Color
			ImGui::ColorEdit4("Base Color", &(m_material.GetBaseColor().x));
			
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
				static const char *brdf_names[] = {
					"Lambertian",
					"Frostbite",
					"Cook-Torrance",
					"Blinn-Phong",
					"Ward-Duer"
				};
				static const BRDFType brdfs[] = {
					BRDFType::Lambertian,
					BRDFType::Frostbite,
					BRDFType::CookTorrance,
					BRDFType::BlinnPhong,
					BRDFType::WardDuer
				};
				ImGui::ListBox("BRDF", &m_brdf_index, 
					brdf_names, _countof(brdf_names));
				m_settings->SetBRDF(brdfs[m_brdf_index]);
			}

			// Set the material.
			*(m_models[m_model_index]->GetModel()->GetMaterial()) = m_material;

			ImGui::TreePop();
		}
	
		ImGui::End();
	}
}