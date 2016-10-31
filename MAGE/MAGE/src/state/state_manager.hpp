#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of state managers.
	 */
	class StateManager {

	public:

		/**
		 Constructs a state manager.
		 */
		StateManager() : m_current_state(NULL), m_states(list< State * >()) {}

		/**
		 Destructs this state manager.
		 */
		virtual ~StateManager() {
			if (m_current_state) {
				// State postprocessing
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
		 Removes the given state from the states of this state manager.

		 @param[in]		state
		 A pointer to the state.
		 */
		void RemoveState(State *state) {
			m_states.remove(state);
			delete state;
		}

		/**
		 Changes the state of this state manager to the state with the given id.

		 @param[in]		id
						The id.
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

		/**
		 Updates this state manager and its current state.

		 @param[in]		elapsed_time
						The elapsed time since the previous update.
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

	private:

		/**
		 Changes the state of this state manager to the given state.

		 @param[in]		new_state
						A pointer to the new state.
		 */
		void ChangeState(State *new_state) {
			if (m_current_state) {
				// State postprocessing
				m_current_state->Close();
			}

			m_current_state = new_state;
			// State preprocessing
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