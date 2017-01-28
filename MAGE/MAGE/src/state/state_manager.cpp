//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "state\state_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	StateManager::~StateManager() {
		if (m_current_state) {
			// State post-processing
			m_current_state->Close();
		}

		m_states.clear();
	}

	void StateManager::AddState(State *state, bool change) {
		m_states.push_back(state);

		if (change == false) {
			return;
		}

		ChangeState(m_states.back());
	}

	void StateManager::RemoveState(State *state) {
		if (state == m_current_state) {
			return;
		}

		m_states.remove(state);
	}

	void StateManager::ChangeState(uint64_t id) {
		// Iterate the states looking for the specified state.
		for (list< State * >::iterator it = m_states.begin(); it != m_states.end(); ++it) {
			if ((*it)->GetId() == id) {
				ChangeState(*it);
				break;
			}
		}
	}

	bool StateManager::Update(double elapsed_time) {
		m_state_changed = false;

		if (m_current_state) {
			m_current_state->Update(elapsed_time);
		}

		return m_state_changed;
	}

	void StateManager::ChangeState(State *state) {
		if (m_current_state) {
			// State post-processing
			m_current_state->Close();
		}

		m_current_state = state;
		// State pre-processing
		m_current_state->Load();

		m_state_changed = true;
	}
}