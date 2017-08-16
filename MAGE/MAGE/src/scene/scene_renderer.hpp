#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "sprite\sprite_batch.hpp"
#include "rendering\structured_buffer.hpp"
#include "buffer\transform_buffer.hpp"
#include "buffer\light_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class SceneRenderer {

	public:

		SceneRenderer();
		SceneRenderer(const SceneRenderer &scene_renderer) = delete;
		SceneRenderer(SceneRenderer &&scene_renderer);
		virtual ~SceneRenderer();

		SceneRenderer &operator=(const SceneRenderer &scene_renderer) = delete;
		SceneRenderer &operator=(SceneRenderer &&scene_renderer) = delete;

		void Render(const Scene *scene);

	private:

		void CreateBox();
		void Preprocess(const Scene *scene);
		void Render3D(const Scene *scene);
		void RenderAABBs();
		void Render2D();

		vector< const CameraNode * > m_cameras;
		vector< const ModelNode * > m_opaque_models;
		vector< const ModelNode * > m_transparent_models;
		vector< const DirectionalLightNode * > m_directional_lights;
		vector< const OmniLightNode * > m_omni_lights;
		vector< const SpotLightNode * > m_spot_lights;
		vector< const SpriteNode * > m_sprites;
		RGBSpectrum m_ambient_light;
		UniquePtr< ModelNode > m_box;

		UniquePtr< SpriteBatch > m_sprite_batch;

		ConstantBuffer< TransformBuffer > m_transform_buffer;
		ConstantBuffer< SceneBuffer > m_scene_buffer;
		StructuredBuffer< DirectionalLightBuffer > m_directional_lights_buffer;
		StructuredBuffer< OmniLightBuffer > m_omni_lights_buffer;
		StructuredBuffer< SpotLightBuffer > m_spot_lights_buffer;
	};
}