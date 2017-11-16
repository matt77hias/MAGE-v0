#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

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
		 @return		A reference to the moved behavior script (i.e. this 
						behavior script).
		 */
		BehaviorScript &operator=(BehaviorScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods: State
		//---------------------------------------------------------------------

		/**
		 Checks whether this behavior script is active.

		 @return		@c true if this behavior script is active. @c false 
						otherwise (i.e. passive).
		 */
		bool IsActive() const noexcept {
			return m_active;
		}

		/**
		 Checks whether this behavior script is passive.

		 @return		@c true if this behavior script is passive. @c false 
						otherwise (i.e. active).
		 */
		bool IsPassive() const noexcept {
			return !m_active;
		}

		/**
		 Activates this behavior script (and its descendant behavior scripts).
		 */
		void Activate() noexcept {
			SetActive(true);
		}

		/**
		 Deactives this behavior script (and its descendant behavior scripts).
		 */
		void Deactivate() noexcept {
			SetActive(false);
		}

		/**
		 Sets this behavior script active flag to the given value.

		 @param[in]		active
						The active flag.
		 */
		void SetActive(bool active) noexcept;

		/**
		 Checks whether this behavior script is terminated or not.

		 @return		@c true if this behavior script is terminated. @c false 
						otherwise.
		 */
		bool IsTerminated() const noexcept {
			return m_terminated;
		}

		/**
		 Terminates this behavior script.
		 */
		void Terminate() noexcept;

		//-------------------------------------------------------------------------
		// Member Methods: Lifecycle
		//-------------------------------------------------------------------------

		/**
		 Updates this behavior script.
		 
		 This method can be called zero, one or multiple times per frame depending 
		 on the fixed delta time used by the engine.
		 */
		virtual void FixedUpdate();

		/**
		 Updates this behavior script.
		 
		 This method is called once per frame.

		 @param[in]		delta_time
						The elapsed time since the previous update.
		 */
		virtual void Update([[maybe_unused]] F64 delta_time);

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

	private:

		//---------------------------------------------------------------------
		// Member Methods: State
		//---------------------------------------------------------------------

		/**
		 Notifies this transform behavior script of a change in activeness.
		 */
		virtual void OnActiveChange() noexcept;

		//---------------------------------------------------------------------
		// Member Variables: State
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether this behavior script is active or not (i.e. 
		 passive).
		 */
		bool m_active;

		/**
		 A flag indicating whether this behavior script is terminated or not. 
		 */
		bool m_terminated;
	};
}