#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations
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
		virtual ~BehaviorScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given behavior script to this behavior script.

		 @param[in]		script
						A reference to the behavior script to copy.
		 @return		A reference to the copy of the given behavior script
						(i.e. this behavior script).
		 */
		BehaviorScript &operator=(const BehaviorScript &script) = delete;

		/**
		 Moves the given behavior script to this behavior script.

		 @param[in]		script
						A reference to the behavior script to move.
		 @return		A reference to the moved behavior script
						(i.e. this behavior script).
		 */
		BehaviorScript &operator=(BehaviorScript &&script) = delete;

		//-------------------------------------------------------------------------
		// Member Methods: Lifecycle
		//-------------------------------------------------------------------------

		/**
		 Updates this behavior script.

		 @param[in]		delta_time
						The elapsed time since the previous update.
		 */
		virtual void Update(double delta_time) = 0;

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a behavior script.
		 */
		BehaviorScript();

		/**
		 Constructs a behavior script from the given behavior script.

		 @param[in]		script
						A reference to the behavior script to copy.
		 */
		BehaviorScript(const BehaviorScript &script);

		/**
		 Constructs a behavior script by moving the given behavior script.

		 @param[in]		script
						A reference to the behavior script to move.
		 */
		BehaviorScript(BehaviorScript &&script);
	};
}