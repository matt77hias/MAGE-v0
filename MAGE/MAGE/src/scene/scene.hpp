#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
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
		void AddScript(SharedPtr< BehaviorScript > script);
		void RemoveScript(SharedPtr< BehaviorScript > script);
		void RemoveAllScripts();
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

		 @param[in]		delta_time
						The elapsed time since the previous update.
		 */
		void Update(double delta_time);

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
			: m_name(name), m_camera(), 
			m_world(new World()), m_scripts() {}
		Scene(const Scene &scene) = delete;
		Scene(Scene &&scene) = default;

	private:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

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