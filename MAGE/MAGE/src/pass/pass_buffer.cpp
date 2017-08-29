//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	PassBuffer::PassBuffer(const Scene *scene) 
		: m_cameras(), m_opaque_models(), m_transparent_models(), 
		m_directional_lights(), m_omni_lights(), m_spot_lights(), 
		m_sprites(), m_ambient_light(), m_fog(nullptr) {
		
		Assert(scene);

		// Collect active cameras.
		m_cameras.clear();
		m_cameras.reserve(scene->GetNumberOfCameras());
		scene->ForEachCamera([this](const CameraNode *node) {
			m_cameras.push_back(node);
		});
	
		// Collect active models.
		m_opaque_models.clear();
		m_transparent_models.clear();
		m_opaque_models.reserve(scene->GetNumberOfModels());
		m_transparent_models.reserve(scene->GetNumberOfModels());
		scene->ForEachModel([this](const ModelNode *node) {

			const Model * const model = node->GetModel();

			if (model->GetNumberOfIndices() == 0) {
				return;
			}

			if (model->GetMaterial()->IsTransparant()) {
				m_transparent_models.push_back(node);
			}
			else {
				m_opaque_models.push_back(node);
			}

		});
	
		// Collect active ambient light.
		m_ambient_light = RGBSpectrum();
		scene->ForEachAmbientLight([this](const AmbientLightNode *node) {
			m_ambient_light = node->GetLight()->GetIntensity();
		});
	
		// Collect active directional lights.
		m_directional_lights.clear();
		m_directional_lights.reserve(scene->GetNumberOfDirectionalLights());
		scene->ForEachDirectionalLight([this](const DirectionalLightNode *node) {
			m_directional_lights.push_back(node);
		});

		// Collect active omni lights.
		m_omni_lights.clear();
		m_omni_lights.reserve(scene->GetNumberOfOmniLights());
		scene->ForEachOmniLight([this](const OmniLightNode *node) {
			m_omni_lights.push_back(node);
		});

		// Collect active spotlights.
		m_spot_lights.clear();
		m_spot_lights.reserve(scene->GetNumberOfSpotLights());
		scene->ForEachSpotLight([this](const SpotLightNode *node) {
			m_spot_lights.push_back(node);
		});
	
		// Collect active sprites.
		m_sprites.clear();
		m_sprites.reserve(scene->GetNumberOfSprites());
		scene->ForEachSprite([this](const SpriteNode *node) {
			m_sprites.push_back(node);
		});
	
		// Collect scene fog.
		m_fog = scene->GetSceneFog();
	}
}