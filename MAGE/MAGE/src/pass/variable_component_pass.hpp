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

	class VariableComponentPass final {

	public:

		VariableComponentPass();
		VariableComponentPass(const VariableComponentPass &render_pass) = delete;
		VariableComponentPass(VariableComponentPass &&render_pass);
		virtual ~VariableComponentPass();

		VariableComponentPass &operator=(const VariableComponentPass &render_pass) = delete;
		VariableComponentPass &operator=(VariableComponentPass &&render_pass) = delete;

		void Render(const PassBuffer *scene, const CameraNode *node);

	private:

		void BindPS() noexcept;
		void BindComponent(const Material *material) noexcept;

		enum struct PSIndex {
			DiffuseTexture = 0,
			Count          = 1
		};

		void ProcessScene(
			FXMMATRIX world_to_view, FXMMATRIX view_to_projection);
		void ProcessModels(const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);

		ID3D11DeviceContext2 * const m_device_context;
		RenderMode m_render_mode;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps[static_cast< size_t >(PSIndex::Count)];

		ConstantBuffer< ModelTransformBuffer > m_model_buffer;
		ConstantBuffer< SceneTransformBuffer > m_scene_buffer;
		ConstantBuffer< XMFLOAT4 > m_color_buffer;
	};
}