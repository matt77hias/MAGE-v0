#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "buffer\scene_buffer.hpp"
#include "buffer\model_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations end Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class BoundingVolumePass final {

	public:

		BoundingVolumePass();
		BoundingVolumePass(const BoundingVolumePass &render_pass) = delete;
		BoundingVolumePass(BoundingVolumePass &&render_pass);
		~BoundingVolumePass();

		BoundingVolumePass &operator=(const BoundingVolumePass &render_pass) = delete;
		BoundingVolumePass &operator=(BoundingVolumePass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);

	private:

		void XM_CALLCONV ProcessScene(
			FXMMATRIX world_to_view, FXMMATRIX view_to_projection);
		void XM_CALLCONV ProcessLights(
			const vector< const OmniLightNode * > &lights,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);
		void XM_CALLCONV ProcessLights(
			const vector< const SpotLightNode * > &lights,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);
		void XM_CALLCONV ProcessModels(
			const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< SceneTransformBuffer > m_scene_buffer;
		ConstantBuffer< RGBASpectrum > m_color_buffer;
		UniquePtr< const StaticMesh > m_box;
	};
}
