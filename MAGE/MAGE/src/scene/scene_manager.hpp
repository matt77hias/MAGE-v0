#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of scene managers.
	 */
	class SceneManager final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a scene manager.
		 */
		SceneManager();
		
		/**
		 Constructs a scene manager from the given scene manager.

		 @param[in]		scene_behavior
						A reference to the scene manager to copy.
		 */
		SceneManager(const SceneManager &scene_behavior) = delete;

		/**
		 Constructs a scene manager by moving the given scene manager.

		 @param[in]		scene_behavior
						A reference to the scene manager to move.
		 */
		SceneManager(SceneManager &&scene_behavior);

		/**
		 Destructs this scene manager.
		 */
		~SceneManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given scene manager to this scene manager.

		 @param[in]		scene_behavior
						A reference to the scene manager to copy.
		 @return		A reference to the copy of the given scene manager
						(i.e. this scene manager).
		 */
		SceneManager &operator=(const SceneManager &scene_behavior) = delete;

		/**
		 Moves the given scene manager to this scene manager.

		 @param[in]		scene_behavior
						A reference to the scene manager to move.
		 @return		A reference to the moved scene manager
						(i.e. this scene manager).
		 */
		SceneManager &operator=(SceneManager &&scene_behavior) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		bool IsFinished() const noexcept {
			return !HasScene();
		}

		bool HasScene() const noexcept {
			return m_scene != nullptr;
		}

		Scene *GetScene() const noexcept {
			return m_scene.get();
		}

		void SetScene(UniquePtr< Scene > &&scene);

		void Update(double delta_time) {
			m_scene->ForEachScript([delta_time](BehaviorScript *script) {
				script->Update(delta_time);
			});
		}

		void Render() {
			m_renderer->Render(GetScene());
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the scene renderer of this scene manager.
		 */
		UniquePtr< SceneRenderer > m_renderer;

		/**
		 A pointer to the current scene of this scene manager.
		 */
		UniquePtr< Scene > m_scene;
	};
}