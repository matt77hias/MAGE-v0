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
		m_directional_lights(), m_sm_directional_lights(),
		m_omni_lights(), m_sm_omni_lights(),
		m_spot_lights(), m_sm_spot_lights(),
		m_sprites(),
		m_ambient_light(), 
		m_fog(nullptr), m_sky(nullptr),
		m_material_coefficient_min{},
		m_material_coefficient_max{} {}
		
	void PassBuffer::Update(const Scene *scene) {

		Assert(scene);

		// Update the cameras.
		UpdateCameras(scene);
		// Update the models.
		UpdateModels(scene);
		// Update the lights.
		UpdateLights(scene);
		// Update the sprites.
		UpdateSprites(scene);

		// Collect the scene fog.
		m_fog = scene->GetSceneFog();
		// Collect the sky.
		m_sky = scene->GetSky();
	}

	void PassBuffer::UpdateCameras(const Scene *scene) {
		// Clear active cameras.
		m_cameras.clear();

		// Collect active cameras.
		scene->ForEachCamera([this](const CameraNode *node) {
			m_cameras.push_back(node);
		});
	}

	void PassBuffer::UpdateModels(const Scene *scene) {
		// Reset the material coefficients.
		ResetMaterialCoefficients();

		// Clear active models.
		m_opaque_emissive_models.clear();
		m_opaque_brdf_models.clear();
		m_transparent_emissive_models.clear();
		m_transparent_brdf_models.clear();

		// Collect active models.
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

			// Update the material coefficients.
			UpdateMaterialCoefficients(material);
		});
	
		// Finish the material coefficients.
		FinishMaterialCoefficients();
	}

	void PassBuffer::UpdateLights(const Scene *scene) {
		// Clear active lights.
		m_directional_lights.clear();
		m_omni_lights.clear();
		m_spot_lights.clear();
		m_sm_directional_lights.clear();
		m_sm_omni_lights.clear();
		m_sm_spot_lights.clear();
		m_ambient_light = RGBSpectrum();
		
		// Collect active directional lights.
		scene->ForEachDirectionalLight([this](const DirectionalLightNode *node) {
			if (node->GetLight()->UseShadows()) {
				m_sm_directional_lights.push_back(node);
			}
			else {
				m_directional_lights.push_back(node);
			}
		});

		// Collect active omni lights.
		scene->ForEachOmniLight([this](const OmniLightNode *node) {
			if (node->GetLight()->UseShadows()) {
				m_sm_omni_lights.push_back(node);
			}
			else {
				m_omni_lights.push_back(node);
			}
		});

		// Collect active spotlights.
		scene->ForEachSpotLight([this](const SpotLightNode *node) {
			if (node->GetLight()->UseShadows()) {
				m_sm_spot_lights.push_back(node);
			}
			else {
				m_spot_lights.push_back(node);
			}
		});

		// Collect active ambient light.
		scene->ForEachAmbientLight([this](const AmbientLightNode *node) {
			m_ambient_light = node->GetLight()->GetIntensity();
		});
	}

	void PassBuffer::UpdateSprites(const Scene *scene) {
		// Clear active sprites.
		m_sprites.clear();
		
		// Collect active sprites.
		scene->ForEachSprite([this](const SpriteNode *node) {
			m_sprites.push_back(node);
		});
	}

	void PassBuffer::ResetMaterialCoefficients() noexcept {
		for (u8 i = 0; i < s_nb_material_coefficients; ++i) {
			m_material_coefficient_min[i] = FLT_MAX;
			m_material_coefficient_max[i] = FLT_MIN;
		}
	}

	void PassBuffer::UpdateMaterialCoefficients(const Material *material) noexcept {
		// Update min/max material coefficients for deferred shading.
		for (u8 i = 0; i < s_nb_material_coefficients; ++i) {
			const f32 p = material->GetMaterialParameter(i);
			m_material_coefficient_min[i] = std::min(p, m_material_coefficient_min[i]);
			m_material_coefficient_max[i] = std::max(p, m_material_coefficient_max[i]);
		}
	}

	void PassBuffer::FinishMaterialCoefficients() noexcept {
		for (u8 i = 0; i < s_nb_material_coefficients; ++i) {
			if (m_material_coefficient_min[i] == m_material_coefficient_max[i]) {
				if (0.0f == m_material_coefficient_max[i]) {
					// min := 0 and max := 1 and mat := 0
					// Normalization: nmat = (mat - min) / (max - min) = 0
					// Recover:        mat = min + nmat * (max - min)  = mat
					m_material_coefficient_max[i] = 1.0f;
				}
				else {
					// min := 0 and 0 < max := mat
					// Normalization: nmat = (mat - min) / (max - min) = 1
					// Recover:        mat = min + nmat * (max - min)  = mat
					m_material_coefficient_min[i] = 0.0f;
				}
			}
		}
	}

	f32 PassBuffer::GetMaterialCoefficientMinimum(u8 index) const noexcept {
		Assert(index < s_nb_material_coefficients);
		
		return m_material_coefficient_min[index];
	}

	f32 PassBuffer::GetMaterialCoefficientMaximum(u8 index) const noexcept {
		Assert(index < s_nb_material_coefficients);
		
		return m_material_coefficient_max[index];
	}

	f32 PassBuffer::GetMaterialCoefficientRange(u8 index) const noexcept {
		Assert(index < s_nb_material_coefficients);

		return GetMaterialCoefficientMaximum(index) 
			- GetMaterialCoefficientMinimum(index);
	}
}