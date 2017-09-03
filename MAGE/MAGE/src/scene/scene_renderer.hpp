#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\bounding_volume_pass.hpp"
#include "pass\constant_component_pass.hpp"
#include "pass\constant_shading_pass.hpp"
#include "pass\gbuffer_pass.hpp"
#include "pass\sprite_pass.hpp"
#include "pass\variable_component_pass.hpp"
#include "pass\variable_shading_pass.hpp"
#include "pass\shading_normal_pass.hpp"
#include "pass\wireframe_pass.hpp"
#include "buffer\gbuffer.hpp"
#include "buffer\lbuffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {


	class SceneRenderer final {

	public:

		SceneRenderer();
		SceneRenderer(const SceneRenderer &scene_renderer) = delete;
		SceneRenderer(SceneRenderer &&scene_renderer);
		~SceneRenderer();

		SceneRenderer &operator=(const SceneRenderer &scene_renderer) = delete;
		SceneRenderer &operator=(SceneRenderer &&scene_renderer) = delete;

		void Render(const Scene *scene);

	private:

		ID3D11DeviceContext2 * const m_device_context;

		UniquePtr< PassBuffer > m_pass_buffer;
		UniquePtr< GBuffer > m_gbuffer;
		UniquePtr< LBuffer > m_lbuffer;

		UniquePtr< BoundingVolumePass > m_bounding_volume_pass;
		UniquePtr< ConstantComponentPass > m_constant_component_pass;
		UniquePtr< ConstantShadingPass > m_constant_shading_pass;
		UniquePtr< GBufferPass > m_gbuffer_pass;
		UniquePtr< SpritePass > m_sprite_pass;
		UniquePtr< VariableComponentPass > m_variable_component_pass;
		UniquePtr< VariableShadingPass > m_variable_shading_pass;
		UniquePtr< ShadingNormalPass > m_shading_normal_pass;
		UniquePtr< WireframePass > m_wireframe_pass;
		
		Viewport m_viewport;
	};
}