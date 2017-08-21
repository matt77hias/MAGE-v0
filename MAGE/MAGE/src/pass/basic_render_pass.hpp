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

	class BasicRenderPass final {

	public:

		BasicRenderPass();
		BasicRenderPass(const BasicRenderPass &render_pass) = delete;
		BasicRenderPass(BasicRenderPass &&render_pass);
		virtual ~BasicRenderPass();

		BasicRenderPass &operator=(const BasicRenderPass &render_pass) = delete;
		BasicRenderPass &operator=(BasicRenderPass &&render_pass) = delete;

		void Render(const PassBuffer *buffer);

	private:

		void RenderDefault(const CameraNode *node);
		void RenderSolid(const CameraNode *node);
		void RenderDiffuseTexture(const CameraNode *node);
		void RenderUVTexture(const CameraNode *node);
		void RenderShadingNormal(const CameraNode *node);
		void RenderTSNMShadingNormal(const CameraNode *node);
		void RenderDistance(const CameraNode *node);
		void RenderAABB(const CameraNode *node);
		void RenderWireframe(const CameraNode *node);

		size_t ProcessDirectionalLights(FXMMATRIX world_to_view);
		size_t ProcessOmniLights(FXMMATRIX world_to_projection, FXMMATRIX world_to_view);
		size_t ProcessSpotLights(FXMMATRIX world_to_projection, FXMMATRIX world_to_view);
		void ProcessConstant(FXMMATRIX world_to_projection, FXMMATRIX world_to_view, 
			FXMMATRIX view_to_projection, bool lighting);
		void ProcessNonConstant(FXMMATRIX object_to_world, FXMMATRIX view_to_object,
			const Material *material);
		void ProcessModels(const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world);
		void ProcessModels(const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world,
			const Material *material);
		void ProcessModelAABBs(const vector< const ModelNode * > &models,
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world,
			const Material *material);
		void ProcessOmniLightAABBs(
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world,
			const Material *material);
		void ProcessSpotLightAABBs(
			FXMMATRIX world_to_projection, FXMMATRIX view_to_world,
			const Material *material);

		void BindDirectionalLightsBuffer() noexcept {
			PS::BindSRV(0, m_directional_lights_buffer.Get());
		}
		void BindOmniLightsBuffer() noexcept {
			PS::BindSRV(1, m_omni_lights_buffer.Get());
		}
		void BindSpotLightsBuffer() noexcept {
			PS::BindSRV(2, m_spot_lights_buffer.Get());
		}
		void BindSceneBuffer() noexcept {
			VS::BindConstantBuffer(0, m_scene_buffer.Get());
			PS::BindConstantBuffer(0, m_scene_buffer.Get());
		}
		void BindModelBuffer() noexcept {
			VS::BindConstantBuffer(1, m_model_buffer.Get());
			PS::BindConstantBuffer(1, m_model_buffer.Get());
		}

		enum PSIndex {
			Default_Emissive           = 0,
			Default_BRDF               = 1,
			Default_BRDFTSNM           = 2,
			DiffuseReflectivity        = 3,
			DiffuseReflectivityTexture = 4,
			ShadingNormal              = 5,
			TSNMShadingNormal          = 6,
			Distance                   = 7,
			Count                      = 8
		};

		void InitializeShaders();
		void UpdatePixelShaders(BRDFType brdf);
		void BindPixelShader(PSIndex index) noexcept;
		void BindPixelShader(const Material *material) noexcept;

		const PassBuffer *m_scene;

		SharedPtr< const VertexShader > m_vs;
		SharedPtr< const PixelShader > m_ps[Count];

		PSIndex m_bound_ps;
		RenderMode m_render_mode;
		BRDFType m_brdf;

		ConstantBuffer< ModelBuffer > m_model_buffer;
		ConstantBuffer< SceneBuffer > m_scene_buffer;
		StructuredBuffer< DirectionalLightBuffer > m_directional_lights_buffer;
		StructuredBuffer< OmniLightBuffer > m_omni_lights_buffer;
		StructuredBuffer< SpotLightBuffer > m_spot_lights_buffer;

		SharedPtr< const Texture > m_uv;
		UniquePtr< const StaticMesh > m_box;
	};
}