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

		set< SharedPtr< BehaviorScript > >::iterator ScriptsBegin() {
			return m_scripts.begin();
		}
		set< SharedPtr< BehaviorScript > >::iterator ScriptsEnd() {
			return m_scripts.end();
		}
		set< SharedPtr< BehaviorScript > >::const_iterator ScriptsBegin() const {
			return m_scripts.cbegin();
		}
		set< SharedPtr< BehaviorScript > >::const_iterator ScriptsEnd() const {
			return m_scripts.cend();
		}
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

		 @param[in]		device_context
						A pointer to the device context.
		 */
		void Render(ID3D11DeviceContext2 &device_context);

		/**
		 Closes this scene.
		 Allows this scene to preform any post-processing destruction.
		 */
		virtual void Close();

	protected:

		Scene(const string &name)
			: m_name(name), m_world(new World()) {}

	private:

		Scene(const Scene &scene) = delete;
		Scene &operator=(const Scene &scene) = delete;
		
		string m_name;
		SharedPtr< Camera > m_camera;
		SharedPtr< World > m_world;
		set< SharedPtr< BehaviorScript >, std::less<> > m_scripts;
	};
}