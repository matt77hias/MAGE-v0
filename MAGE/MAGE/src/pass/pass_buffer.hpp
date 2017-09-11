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

		static const uint8_t s_nb_material_coefficients = 2;

		PassBuffer();
		PassBuffer(const PassBuffer &pass_buffer) = default;
		PassBuffer(PassBuffer &&pass_buffer) = default;
		~PassBuffer() = default;

		PassBuffer &operator=(const PassBuffer &pass_buffer) = delete;
		PassBuffer &operator=(PassBuffer &&pass_buffer) = delete;

		void Update(const Scene *scene);

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
	};
}