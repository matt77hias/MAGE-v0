#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "state\state.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of state managers.
	 */
	class StateManager {

	friend class Engine;

	public:

		/**
		 Adds the given state from the states of this state manager.

		 @param[in]		state
						A pointer to the state.
		 @param[in]		change
						Flag indicating whether the current state
						of this engine need to be changed to @a state.
		 */
		void AddState(State *state, bool change = true);

		/**
		 Removes and destructs the given state from the states of this state manager.
		 
		 If the current state of this state manager is removed, 
		 the current state of this state manager is set to @c nullptr.

		 @param[in]		state
						A pointer to the state.
		 */
		void RemoveState(State *state);

		/**
		 Removes and destructs all states of this state manager.

		 The current state of this state manager is set to @c nullptr.
		 */
		void RemoveAllStates();

		/**
		 Changes the state of this state manager to the state with the given id.

		 @param[in]		id
						The id of the state to change to.
		 */
		void ChangeState(uint64_t id);

		/**
		 Returns the current state of this state manager.

		 @return		A pointer to the current state of this state manager.
		 */
		State *GetCurrentState() const {
			return m_current_state;
		}

		/**
		 Checks whether the state of this state manager is changed.

		 @return		@c true if the state is changed.
						@c false otherwise.
		 */
		bool IsStateChanged() const {
			return m_state_changed;
		}

	protected:

		/**
		 Constructs a state manager.
		 */
		 StateManager() 
			 : m_current_state(nullptr), m_states(list< State * >()) {}

		 /**
		  Destructs this state manager.
		  */
		 virtual ~StateManager();

		/**
		 Updates this state manager and its current state.

		 @param[in]		elapsed_time
						The elapsed time since the previous frame.
		 @return		@c true if the state is changed in the current frame.
						@c false otherwise.
		 */
		 bool Update(double elapsed_time);

		/**
		 Changes the state of this state manager to the given state.

		 @pre			@a state is not @c nullptr.
		 @param[in]		state
						A pointer to the new state.
		 */
		 void ChangeState(State *state);

	private:

		/**
		 Constructs a state manager from the given state manager.

		 @param[in]		state_manager
						A reference to the state manager.
		 */
		StateManager(const StateManager &state_manager) = delete;

		/**
		 Copies the given state manager to this state manager.

		 @param[in]		state_manager
						A reference to the state manager to copy from.
		 @return		A reference to the copy of the given state manager
						(i.e. this state manager).
		 */
		StateManager &operator=(const StateManager &state_manager) = delete;

		/**
		 The states of this state manager.
		 */
		list< State * > m_states;

		/**
		 A pointer to the current state of this state manager.
		 */
		State *m_current_state;

		/**
		 Flag indicating if the state changed in the current frame.
		 */
		bool m_state_changed;
	};
}