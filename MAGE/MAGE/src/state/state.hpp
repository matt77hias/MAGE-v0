#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of states
	 */
	class State {

	friend class StateManager;

	public:

		/**
		 Constructs a state with given id.

		 @param[in]		id
						The id.
		 */
		State(uint64_t id = 0) 
			: m_id(id) {}

		/**
		 Destructs this state.
		 */
		~State() {}

		/**
		 Returns the id of this state.

		 @return		The id of this state.
		 */
		uint64_t GetId() const {
			return m_id;
		}

	protected:

		/**
		 Loads this state.
		 Allows this state to preform any pre-processing construction.
		 */
		virtual void Load() {}

		/**
		 Closes this state.
		 Allows this state to preform any post-processing destruction.
		 */
		virtual void Close() {}

		/**
		 Updates this state.

		 @param[in]		elapsed_time
						The elapsed time since the previous update.
		 */
		virtual void Update(double elapsed_time) {
			UNUSED(elapsed_time);
		}

		/**
		 Render this state.
		 */
		virtual void Render() {}

	private:

		/**
		 Constructs a state from the given state.

		 @param[in]		state
						A reference to the state.
		 */
		State(const State &state) = delete;

		/**
		 Copies the given state to this state.

		 @param[in]		state
						A reference to the state to copy from.
		 @return		A reference to the copy of the given state
						(i.e. this state).
		 */
		State &operator=(const State &state) = delete;

		/**
		 Application defined identifier (must be unique for state switching)
		 of this state.
		 */
		const uint64_t m_id;
	};
}