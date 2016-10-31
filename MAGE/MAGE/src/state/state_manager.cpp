//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	void StateManager::ChangeState(uint64_t id) {
		// Iterate the states looking for the specified state.
		for (list< State * >::iterator it = m_states.begin(); it != m_states.end(); ++it) {
			if ((*it)->GetId() == id) {
				ChangeState(*it);
				break;
			}
		}
	}
}