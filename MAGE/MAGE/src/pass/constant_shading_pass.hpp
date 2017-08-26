#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\structured_buffer.hpp"
#include "buffer\scene_buffer.hpp"
#include "buffer\light_buffer.hpp"
#include "buffer\model_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ConstantShadingPass final {

	public:

		ConstantShadingPass();
		ConstantShadingPass(const ConstantShadingPass &render_pass) = delete;
		ConstantShadingPass(ConstantShadingPass &&render_pass);
		virtual ~ConstantShadingPass();

		ConstantShadingPass &operator=(const ConstantShadingPass &render_pass) = delete;
		ConstantShadingPass &operator=(ConstantShadingPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);

	private:

		void BindComponents(
			FXMMATRIX object_to_world, FXMMATRIX view_to_object);

		void ProcessScene(
			FXMMATRIX world_to_view, FXMMATRIX view_to_projection);
		void ProcessLights(const vector< const DirectionalLightNode * > &lights,
			FXMMATRIX world_to_view);
		void ProcessLights(const vector< const OmniLightNode * > &lights,
			FXMMATRIX world_to_projection, FXMMATRIX world_to_view);
		void ProcessLights(const vector< const SpotLightNode * > &lights,
			FXMMATRIX world_to_projection, FXMMATRIX world_to_view);
		void ProcessModels(const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;

		ConstantBuffer< ModelBuffer > m_model_buffer;
		ConstantBuffer< SceneBuffer > m_scene_buffer;
		StructuredBuffer< DirectionalLightBuffer > m_directional_lights_buffer;
		StructuredBuffer< OmniLightBuffer > m_omni_lights_buffer;
		StructuredBuffer< SpotLightBuffer > m_spot_lights_buffer;
		const SharedPtr< const Texture > m_white;
	};
}
