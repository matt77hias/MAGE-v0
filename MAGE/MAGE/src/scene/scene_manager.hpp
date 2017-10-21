#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

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
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the scene manager associated with the current engine.

		 @pre			The current engine must exist.
		 @return		A pointer to the scene manager associated with the 
						current engine.
		 */
		static SceneManager *Get() noexcept;

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
		 @return		A reference to the moved scene manager (i.e. this scene 
						manager).
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

		void FixedUpdate();
		void Update(F64 delta_time);
		void Render() const;

	private:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		void ApplyRequestedScene();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the current scene of this scene manager.
		 */
		UniquePtr< Scene > m_scene;

		/**
		 A pointer to the requested scene of this scene manager.
		 */
		UniquePtr< Scene > m_requested_scene;

		/**
		 A flag indicating whether this scene manager has a requested scene.
		 
		 A separate flag is needed, because the requested scene maybe 
		 @c nullptr.
		 */
		bool m_has_requested_scene;
	};
}