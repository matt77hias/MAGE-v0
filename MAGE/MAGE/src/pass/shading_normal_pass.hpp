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

	class ShadingNormalPass final {

	public:

		ShadingNormalPass();
		ShadingNormalPass(const ShadingNormalPass &render_pass) = delete;
		ShadingNormalPass(ShadingNormalPass &&render_pass);
		virtual ~ShadingNormalPass();

		ShadingNormalPass &operator=(const ShadingNormalPass &render_pass) = delete;
		ShadingNormalPass &operator=(ShadingNormalPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);

	private:

		enum struct PSIndex {
			ShadingNormal     = 0,
			TSNMShadingNormal = 1,
			Count             = 2
		};

		void BindPS(PSIndex index) noexcept;
		void BindPS(const Material *material) noexcept;

		void ProcessScene(
			FXMMATRIX world_to_view, FXMMATRIX view_to_projection);
		void ProcessModels(const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);

		ID3D11DeviceContext2 * const m_device_context;
		RenderMode m_render_mode;
		
		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];
		PSIndex m_bound_ps;

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< SceneTransformBuffer > m_scene_buffer;
	};
}