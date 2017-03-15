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
	 A class of behavior scripts.
	 */
	class BehaviorScript {

	public:

		/**
		 Constructs a behavior script.
		 */
		BehaviorScript() = default;

		/**
		 Destructs this behavior script.
		 */
		~BehaviorScript() = default;

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}

		//-------------------------------------------------------------------------
		// Lifecycle
		//-------------------------------------------------------------------------

		/**
		 Loads this behavior script.
		 Allows this behavior script to preform any pre-processing construction.
		 */
		virtual void Load() {}

		/**
		 Updates this behavior script.

		 @param[in]		elapsed_time
						The elapsed time since the previous update.
		 @param[in]		scene
						A reference to the current scene.
		 */
		virtual void Update(double elapsed_time, const Scene &scene) = 0;

		/**
		 Closes this behavior script.
		 Allows this behavior script to preform any post-processing destruction.
		 */
		virtual void Close() {}

	private:

		/**
		 Constructs a behavior script from the given behavior script.

		 @param[in]		script
						A reference to the behavior script.
		 */
		BehaviorScript(const BehaviorScript &script) = delete;

		/**
		 Copies the given behavior script to this behavior script.

		 @param[in]		script
						A reference to the behavior script to copy from.
		 @return		A reference to the copy of the given behavior script
						(i.e. this behavior script).
		 */
		BehaviorScript &operator=(const BehaviorScript &script) = delete;

		string m_name;
	};
}