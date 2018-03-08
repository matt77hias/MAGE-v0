#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declaration.
	class Engine;

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

		 @throws		Exception
						Failed to load this behavior script.
		 */
		virtual void Load();

		/**
		 Updates this behavior script.
		 
		 This method can be called zero, one or multiple times per frame 
		 depending on the fixed delta time used by the engine.

		 @throws		Exception
						Failed to update this behavior script.
		 */
		virtual void FixedUpdate();

		/**
		 Updates this behavior script.
		 
		 This method is called once per frame.

		 @param[in]		delta_time
						The elapsed time since the previous update.
		 @throws		Exception
						Failed to update this behavior script.
		 */
		virtual void Update([[maybe_unused]] F64 delta_time);

		/**
		 Closes this behavior script. Allows this behavior script to preform any 
		 post-processing destruction.

		 @throws		Exception
						Failed to close this behavior script.
		 */
		virtual void Close();

		//---------------------------------------------------------------------
		// Member Methods: Scripting API
		//---------------------------------------------------------------------

		/**
		 Returns the engine belonging to this behavior script.

		 @return		The engine belonging to this behavior script.
		 */
		[[nodiscard]]
		Engine& GetEngine() noexcept {
			return m_engine;
		}

		/**
		 Returns the engine belonging to this behavior script.

		 @return		The engine belonging to this behavior script.
		 */
		[[nodiscard]]
		const Engine& GetEngine() const noexcept {
			return m_engine;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a behavior script.

		 @param[in]		engine
						A reference to the engine.
		 */
		BehaviorScript(Engine& engine) noexcept;

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

		/**
		 The engine belonging to this behavior script.
		 */
		std::reference_wrapper< Engine > m_engine;
	};
}