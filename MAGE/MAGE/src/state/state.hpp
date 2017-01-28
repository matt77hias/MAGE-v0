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
	 A struct of viewer setups.
	 */
	struct ViewerSetup {

	public:

		/**
		 Constructs a viewer setup.
		 */
		ViewerSetup() 
			: m_view_clear_flags(0) {}

		/**
		 Constructs a viewer setup from the given viewer setup.

		 @param[in]		viewer_setup
						A reference to the viewer setup.
		 */
		ViewerSetup(const ViewerSetup &viewer_setup)
			: m_view_clear_flags(viewer_setup.m_view_clear_flags) {}

		/**
		 Destructs this viewer setup.
		 */
		~ViewerSetup() {};

		/**
		 Copies the given viewer setup to this viewer setup.

		 @param[in]		viewer_setup
						A reference to the viewer setup to copy from.
		 @return		A reference to the copy of the given viewer setup
						(i.e. this viewer setup).
		 */
		ViewerSetup &operator=(const ViewerSetup &viewer_setup) {
			m_view_clear_flags = viewer_setup.m_view_clear_flags;
			return (*this);
		}

		/**
		 Flags used for clearing the view.
		 */
		uint64_t m_view_clear_flags;
	};

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
		State(uint64_t id = 0) : m_id(id) {}

		/**
		 Returns the id of this state.

		 @return		The id of this state.
		 */
		uint64_t GetId() const {
			return m_id;
		}

		/**
		Requests the view setup details for the given frame.

		@param[in, out]	viewer_setup
						A reference to a viewer setup.
		*/
		virtual void RequestViewSetup(ViewerSetup &viewer_setup) {
			viewer_setup.m_view_clear_flags = 0;
		}

	protected:

		/**
		 Destructs this state.

		 (This destructor is not allowed to be called manually:
		 Real destruction must take place in State::Close())
		 */
		~State() {}

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