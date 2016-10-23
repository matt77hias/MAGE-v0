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
		LinkedList< State >::LinkedListIterator it = m_states->GetIterator();
		while (it.HasNext()) {
			State *next = it.Next();
			if (next->GetId() == id) {
				ChangeState(next);
				break;
			}
		}
	}
}