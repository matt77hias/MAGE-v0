#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct PassBuffer final {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		static const uint8_t s_nb_material_coefficients = 2;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		PassBuffer();
		PassBuffer(const PassBuffer &pass_buffer) = default;
		PassBuffer(PassBuffer &&pass_buffer) = default;
		~PassBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		PassBuffer &operator=(const PassBuffer &pass_buffer) = delete;
		PassBuffer &operator=(PassBuffer &&pass_buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void Update(const Scene *scene);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		vector< const CameraNode * >			m_cameras;
		vector< const ModelNode * >				m_opaque_emissive_models;
		vector< const ModelNode * >				m_opaque_brdf_models;
		vector< const ModelNode * >				m_transparent_emissive_models;
		vector< const ModelNode * >				m_transparent_brdf_models;
		vector< const DirectionalLightNode * >	m_directional_lights;
		vector< const DirectionalLightNode * >	m_sm_directional_lights;
		vector< const OmniLightNode * >			m_omni_lights;
		vector< const OmniLightNode * >			m_sm_omni_lights;
		vector< const SpotLightNode * >			m_spot_lights;
		vector< const SpotLightNode * >			m_sm_spot_lights;
		vector< const SpriteNode * >			m_sprites;
		RGBSpectrum								m_ambient_light;
		const SceneFog *						m_fog;

		float m_material_coefficient_min[s_nb_material_coefficients];
		float m_material_coefficient_max[s_nb_material_coefficients];

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void UpdateCameras(const Scene *scene);
		void UpdateModels(const Scene *scene);
		void UpdateLights(const Scene *scene);
		void UpdateSprites(const Scene *scene);
		void ResetMaterialCoefficients() noexcept;
		void UpdateMaterialCoefficients(const Material *material) noexcept;
	};
}