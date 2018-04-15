#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of behavior scripts.
	 */
	class BehaviorScript : public Component {

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
		BehaviorScript& operator=(const BehaviorScript& script) noexcept;

		/**
		 Moves the given behavior script to this behavior script.

		 @param[in]		script
						A reference to the behavior script to move.
		 @return		A reference to the moved behavior script (i.e. this 
						behavior script).
		 */
		BehaviorScript& operator=(BehaviorScript&& script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Loads this behavior script. Allows this behavior script to preform any 
		 pre-processing.

		 @param[in]		engine
						A reference to the engine.
		 @throws		Exception
						Failed to load this behavior script.
		 */
		virtual void Load([[maybe_unused]] Engine& engine);

		/**
		 Updates this behavior script.
		 
		 This method can be called zero, one or multiple times per frame 
		 depending on the fixed delta time used by the engine.

		 @param[in]		engine
						A reference to the engine.
		 @throws		Exception
						Failed to update this behavior script.
		 */
		virtual void FixedUpdate([[maybe_unused]] Engine& engine);

		/**
		 Updates this behavior script.
		 
		 This method is called once per frame.

		 @param[in]		engine
						A reference to the engine.
		 @throws		Exception
						Failed to update this behavior script.
		 */
		virtual void Update([[maybe_unused]] Engine& engine);

		/**
		 Closes this behavior script. Allows this behavior script to preform any 
		 post-processing destruction.

		 @param[in]		engine
						A reference to the engine.
		 @throws		Exception
						Failed to close this behavior script.
		 */
		virtual void Close([[maybe_unused]] Engine& engine);

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a behavior script.
		 */
		BehaviorScript() noexcept;

		/**
		 Constructs a behavior script from the given behavior script.

		 @param[in]		script
						A reference to the behavior script to copy.
		 */
		BehaviorScript(const BehaviorScript& script) noexcept;

		/**
		 Constructs a behavior script by moving the given behavior script.

		 @param[in]		script
						A reference to the behavior script to move.
		 */
		BehaviorScript(BehaviorScript&& script) noexcept;
	};
}