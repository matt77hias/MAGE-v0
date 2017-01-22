#pragma once

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
		 Destructs this state manager.
		 */
		virtual ~StateManager() {
			if (m_current_state) {
				// State post-processing
				m_current_state->Close();
			}

			m_states.clear();
		}

		/**
		 Adds the given state from the states of this state manager.

		 @param[in]		state
						A pointer to the state.
		 @param[in]		change
						Flag indicating whether the current state
						of this engine need to be changed to @a state.
		 */
		void AddState(State *state, bool change = true) {
			m_states.push_back(state);

			if (change == false) {
				return;
			}

			ChangeState(m_states.back());
		}

		/**
		 Removes (and destructs) the given state from the states of this state manager.

		 @param[in]		state
						A pointer to the state.
		 */
		void RemoveState(State *state) {
			m_states.remove(state);
		}

		/**
		 Changes the state of this state manager to the state with the given id.

		 @param[in]		id
						The id of the state to change to.
		 */
		void ChangeState(uint64_t id) {
			// Iterate the states looking for the specified state.
			for (list< State * >::iterator it = m_states.begin(); it != m_states.end(); ++it) {
				if ((*it)->GetId() == id) {
					ChangeState(*it);
					break;
				}
			}
		}

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
		 Updates this state manager and its current state.

		 @param[in]		elapsed_time
						The elapsed time since the previous frame.
		 @return		@c true if the state is changed in the current frame.
						@c false otherwise.
		 */
		bool Update(double elapsed_time) {
			m_state_changed = false;

			if (m_current_state) {
				m_current_state->Update(elapsed_time);
			}

			return m_state_changed;
		}

		/**
		 Changes the state of this state manager to the given state.

		 @pre			@a state is not @c nullptr.
		 @param[in]		state
						A pointer to the new state.
		 */
		void ChangeState(State *state) {
			if (m_current_state) {
				// State post-processing
				m_current_state->Close();
			}

			m_current_state = state;
			// State pre-processing
			m_current_state->Load();

			m_state_changed = true;
		}

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