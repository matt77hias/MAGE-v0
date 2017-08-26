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

	class DistancePass final {

	public:

		DistancePass();
		DistancePass(const DistancePass &render_pass) = delete;
		DistancePass(DistancePass &&render_pass);
		virtual ~DistancePass();

		DistancePass &operator=(const DistancePass &render_pass) = delete;
		DistancePass &operator=(DistancePass &&render_pass) = delete;

		void Render(const PassBuffer *buffer, const CameraNode *node);

	private:

		void ProcessScene(
			FXMMATRIX world_to_view, FXMMATRIX view_to_projection);
		void ProcessModels(const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);

		ID3D11DeviceContext2 * const m_device_context;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps;

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< SceneTransformBuffer > m_scene_buffer;
	};
}