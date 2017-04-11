#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of behavior scripts.
	 */
	class BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this behavior script.
		 */
		virtual ~BehaviorScript() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given behavior script to this behavior script.

		 @param[in]		script
						A reference to the behavior script to copy from.
		 @return		A reference to the copy of the given behavior script
						(i.e. this behavior script).
		 */
		BehaviorScript &operator=(const BehaviorScript &script) = delete;

		/**
		 Copies the given behavior script to this behavior script.

		 @param[in]		script
						A reference to the behavior script to copy from.
		 @return		A reference to the copy of the given behavior script
						(i.e. this behavior script).
		 */
		BehaviorScript &operator=(BehaviorScript &&script) = delete;

		//-------------------------------------------------------------------------
		// Member Methods: Lifecycle
		//-------------------------------------------------------------------------

		/**
		 Updates this behavior script.

		 @param[in]		elapsed_time
						The elapsed time since the previous update.
		 @param[in]		scene
						A reference to the current scene.
		 */
		virtual void Update(double elapsed_time) = 0;

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a behavior script.
		 */
		BehaviorScript() = default;

		/**
		 Constructs a behavior script from the given behavior script.

		 @param[in]		script
						A reference to the behavior script.
		 */
		BehaviorScript(const BehaviorScript &script) = default;

		/**
		 Constructs a behavior script from the given behavior script.

		 @param[in]		script
						A reference to the behavior script.
		 */
		BehaviorScript(BehaviorScript &&script) = default;
	};
}