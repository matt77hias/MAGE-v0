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

		~Scene() = default;

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		Camera &GetCamera() const {
			return *m_camera;
		}
		void SetCamera(SharedPtr< Camera > camera) {
			m_camera = camera;
		}
		World &GetWorld() const {
			return *m_world;
		}

		//-------------------------------------------------------------------------
		// Scripts
		//-------------------------------------------------------------------------

		size_t GetNumberOfScripts() const {
			return m_scripts.size();
		}
		SharedPtr< BehaviorScript > GetScript(const string &name) const;
		bool HasScript(const string &name) const {
			return GetScript(name) != nullptr;
		}
		bool HasScript(const SharedPtr< BehaviorScript > script) const;
		void AddScript(SharedPtr< BehaviorScript > script, bool load = false);
		void RemoveScript(const string &name, bool close = false);
		void RemoveScript(SharedPtr< BehaviorScript > script, bool close = false);
		void RemoveAllScripts(bool close = false);
		template< typename ActionT >
		void ForEachScript(ActionT action) const;

		//-------------------------------------------------------------------------
		// Lifecycle
		//-------------------------------------------------------------------------

		/**
		 Loads this scene.
		 Allows this scene to preform any pre-processing construction.
		 */
		virtual void Load();

		/**
		 Updates this scene.

		 @param[in]		elapsed_time
						The elapsed time since the previous update.
		 */
		void Update(double elapsed_time);

		/**
		 Renders this scene.
		 */
		void Render() const;

		/**
		 Closes this scene.
		 Allows this scene to preform any post-processing destruction.
		 */
		virtual void Close();

	protected:

		explicit Scene(const string &name)
			: m_name(name), m_world(new World()) {}
		Scene(Scene &&scene) = default;

	private:

		Scene(const Scene &scene) = delete;
		Scene &operator=(const Scene &scene) = delete;
		Scene &operator=(Scene &&scene) = delete;
		
		string m_name;
		SharedPtr< Camera > m_camera;
		UniquePtr< World > m_world;
		set< SharedPtr< BehaviorScript >, std::less<> > m_scripts;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.tpp"

#pragma endregion