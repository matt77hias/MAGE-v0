#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\depth_pass.hpp"
#include "pass\gbuffer_pass.hpp"
#include "pass\deferred_shading_pass.hpp"
#include "pass\variable_shading_pass.hpp"
#include "pass\sprite_pass.hpp"
#include "pass\image_pass.hpp"

#include "pass\constant_shading_pass.hpp"
#include "pass\constant_component_pass.hpp"
#include "pass\variable_component_pass.hpp"
#include "pass\shading_normal_pass.hpp"
#include "pass\wireframe_pass.hpp"
#include "pass\bounding_volume_pass.hpp"

#include "buffer\gbuffer.hpp"
#include "buffer\lbuffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class SceneRenderer final {

	public:

		static SceneRenderer *Get() noexcept;

		SceneRenderer();
		SceneRenderer(const SceneRenderer &scene_renderer) = delete;
		SceneRenderer(SceneRenderer &&scene_renderer);
		~SceneRenderer();

		SceneRenderer &operator=(const SceneRenderer &scene_renderer) = delete;
		SceneRenderer &operator=(SceneRenderer &&scene_renderer) = delete;

		void Render(const Scene *scene);

		DepthPass *GetDepthPass() {
			if (!m_depth_pass) {
				m_depth_pass = MakeUnique< DepthPass >();
			}
			return m_depth_pass.get();
		}

		GBufferPass *GetGBufferPass() {
			if (!m_gbuffer_pass) {
				m_gbuffer_pass = MakeUnique< GBufferPass >();
			}
			return m_gbuffer_pass.get();
		}

		DeferredShadingPass *GetDeferredShadingPass() {
			if (!m_deferred_shading_pass) {
				m_deferred_shading_pass = MakeUnique< DeferredShadingPass >();
			}
			return m_deferred_shading_pass.get();
		}

		VariableShadingPass *GetVariableShadingPass() {
			if (!m_variable_shading_pass) {
				m_variable_shading_pass = MakeUnique< VariableShadingPass >();
			}
			return m_variable_shading_pass.get();
		}

		SpritePass *GetSpritePass() {
			if (!m_sprite_pass) {
				m_sprite_pass = MakeUnique< SpritePass >();
			}
			return m_sprite_pass.get();
		}

		ImagePass *GetImagePass() {
			if (!m_image_pass) {
				m_image_pass = MakeUnique< ImagePass >();
			}
			return m_image_pass.get();
		}

		ConstantShadingPass *GetConstantShadingPass() {
			if (!m_constant_shading_pass) {
				m_constant_shading_pass = MakeUnique< ConstantShadingPass >();
			}
			return m_constant_shading_pass.get();
		}

		ConstantComponentPass *GetConstantComponentPass() {
			if (!m_constant_component_pass) {
				m_constant_component_pass = MakeUnique< ConstantComponentPass >();
			}
			return m_constant_component_pass.get();
		}

		VariableComponentPass *GetVariableComponentPass() {
			if (!m_variable_component_pass) {
				m_variable_component_pass = MakeUnique< VariableComponentPass >();
			}
			return m_variable_component_pass.get();
		}

		ShadingNormalPass *GetShadingNormalPass() {
			if (!m_shading_normal_pass) {
				m_shading_normal_pass = MakeUnique< ShadingNormalPass >();
			}
			return m_shading_normal_pass.get();
		}

		WireframePass *GetWireframePass() {
			if (!m_wireframe_pass) {
				m_wireframe_pass = MakeUnique< WireframePass >();
			}
			return m_wireframe_pass.get();
		}

		BoundingVolumePass *GetBoundingVolumePass() {
			if (!m_bounding_volume_pass) {
				m_bounding_volume_pass = MakeUnique< BoundingVolumePass >();
			}
			return m_bounding_volume_pass.get();
		}

	private:

		ID3D11DeviceContext2 * const m_device_context;

		UniquePtr< PassBuffer >            m_pass_buffer;
		UniquePtr< GBuffer >               m_gbuffer;
		UniquePtr< LBuffer >               m_lbuffer;

		UniquePtr< DepthPass >             m_depth_pass;
		UniquePtr< GBufferPass >           m_gbuffer_pass;
		UniquePtr< DeferredShadingPass >   m_deferred_shading_pass;
		UniquePtr< VariableShadingPass >   m_variable_shading_pass;
		UniquePtr< SpritePass >            m_sprite_pass;
		UniquePtr< ImagePass >             m_image_pass;
		
		UniquePtr< ConstantShadingPass >   m_constant_shading_pass;
		UniquePtr< ConstantComponentPass > m_constant_component_pass;
		UniquePtr< VariableComponentPass > m_variable_component_pass;
		UniquePtr< ShadingNormalPass >     m_shading_normal_pass;
		
		UniquePtr< WireframePass >         m_wireframe_pass;
		UniquePtr< BoundingVolumePass >    m_bounding_volume_pass;
		
		Viewport m_viewport;
	};
}