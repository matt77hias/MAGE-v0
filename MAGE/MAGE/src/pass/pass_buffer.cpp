//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	PassBuffer::PassBuffer()
		: m_cameras(),
		m_opaque_emissive_models(), m_opaque_brdf_models(),
		m_transparent_emissive_models(), m_transparent_brdf_models(),
		m_directional_lights(), m_omni_lights(), m_spot_lights(),
		m_opaque_sprites(), m_transparent_sprites(),
		m_ambient_light(), m_fog(nullptr),
		m_material_coefficient_min{},
		m_material_coefficient_max{} {}
		
	void PassBuffer::Update(const Scene *scene) {

		Assert(scene);

		for (uint8_t i = 0; i < s_nb_material_coefficients; ++i) {
			m_material_coefficient_min[i] = FLT_MAX;
			m_material_coefficient_max[i] = FLT_MIN;
		}

		// Collect active cameras.
		m_cameras.clear();
		scene->ForEachCamera([this](const CameraNode *node) {
			m_cameras.push_back(node);
		});
	
		// Collect active models.
		m_opaque_emissive_models.clear();
		m_opaque_brdf_models.clear();
		m_transparent_emissive_models.clear();
		m_transparent_brdf_models.clear();
		scene->ForEachModel([this](const ModelNode *node) {

			const Model * const model = node->GetModel();
			if (model->GetNumberOfIndices() == 0) {
				return;
			}

			const Material * const material = model->GetMaterial();
			const bool is_transparant = material->IsTransparant();
			const bool is_emissive    = !material->InteractsWithLight();

			if (is_transparant) {
				
				if (is_emissive) {
					m_transparent_emissive_models.push_back(node);
					return;
				}
				
				m_transparent_brdf_models.push_back(node);
				return;
			}
			
			if (is_emissive) {
				m_opaque_emissive_models.push_back(node);
				return;
			}
			
			m_opaque_brdf_models.push_back(node);

			// Update min/max material coefficients for deferred shading.
			for (uint8_t i = 0; i < s_nb_material_coefficients; ++i) {
				const float p = material->GetMaterialParameter(i);
				m_material_coefficient_min[i] = std::min(p, m_material_coefficient_min[i]);
				m_material_coefficient_max[i] = std::max(p, m_material_coefficient_max[i]);
			}
		});
	
		// Collect active ambient light.
		m_ambient_light = RGBSpectrum();
		scene->ForEachAmbientLight([this](const AmbientLightNode *node) {
			m_ambient_light = node->GetLight()->GetIntensity();
		});
	
		// Collect active directional lights.
		m_directional_lights.clear();
		scene->ForEachDirectionalLight([this](const DirectionalLightNode *node) {
			m_directional_lights.push_back(node);
		});

		// Collect active omni lights.
		m_omni_lights.clear();
		scene->ForEachOmniLight([this](const OmniLightNode *node) {
			m_omni_lights.push_back(node);
		});

		// Collect active spotlights.
		m_spot_lights.clear();
		scene->ForEachSpotLight([this](const SpotLightNode *node) {
			m_spot_lights.push_back(node);
		});
	
		// Collect active sprites.
		m_opaque_sprites.clear();
		m_transparent_sprites.clear();
		scene->ForEachSprite([this](const SpriteNode *node) {
			if (node->GetSprite()->IsTransparant()) {
				m_transparent_sprites.push_back(node);
			}
			else {
				m_opaque_sprites.push_back(node);
			}
		});
	
		// Collect scene fog.
		m_fog = scene->GetSceneFog();
	}
}