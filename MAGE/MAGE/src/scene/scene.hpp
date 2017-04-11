#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declaration
	class BehaviorScript;

	class Scene {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~Scene() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		Scene &operator=(const Scene &scene) = delete;
		Scene &operator=(Scene &&scene) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		SharedPtr< Camera > GetCamera() {
			return m_camera;
		}
		void SetCamera(SharedPtr< Camera > camera) {
			m_camera = camera;
		}
		World *GetWorld() {
			return m_world.get();
		}
		const World *GetWorld() const {
			return m_world.get();
		}

		//-------------------------------------------------------------------------
		// Member Methods: Scripts
		//-------------------------------------------------------------------------

		size_t GetNumberOfScripts() const {
			return m_scripts.size();
		}
		bool HasScript(const SharedPtr< BehaviorScript > script) const;
		void AddScript(SharedPtr< BehaviorScript > script, bool load = false);
		void RemoveScript(SharedPtr< BehaviorScript > script, bool close = false);
		void RemoveAllScripts(bool close = false);
		template< typename ActionT >
		void ForEachScript(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Lifecycle
		//-------------------------------------------------------------------------

		/**
		 Initializes this scene.
		 */
		void Initialize();

		/**
		 Updates this scene.

		 @param[in]		elapsed_time
						The elapsed time since the previous update.
		 */
		void Update(double elapsed_time);

		/**
		 Renders this scene.
		 */
		void Render2D() const;

		/**
		 Renders this scene.
		 */
		void Render3D() const;

		/**
		 Uninitializes this scene.
		 */
		void Uninitialize();

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit Scene(const string &name)
			: m_name(name), m_world(new World()) {}
		Scene(const Scene &scene) = delete;
		Scene(Scene &&scene) = default;

		/**
		 Loads this scene.
		 Allows this scene to preform any pre-processing construction.
		 */
		virtual void Load() {}

		/**
		 Closes this scene.
		 Allows this scene to preform any post-processing destruction.
		 */
		virtual void Close() {}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_name;
		SharedPtr< Camera > m_camera;
		UniquePtr< World > m_world;
		vector< SharedPtr< BehaviorScript > > m_scripts;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.tpp"

#pragma endregion