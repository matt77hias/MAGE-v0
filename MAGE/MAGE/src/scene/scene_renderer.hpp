#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\pass_buffer.hpp"
#include "pass\basic_render_pass.hpp"
#include "sprite\sprite_batch.hpp"

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

		UniquePtr< BasicRenderPass > m_render_pass;
		UniquePtr< SpriteBatch > m_sprite_batch;
	};
}