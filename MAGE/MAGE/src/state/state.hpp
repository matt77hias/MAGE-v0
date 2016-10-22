#pragma once

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
		ViewerSetup() : m_view_clear_flags(0) {};

		/**
		 Flags used for clearing the view.
		 */
		uint64_t m_view_clear_flags;
	};

	/**
	 A class of states
	 */
	class State {

	public:

		/**
		 Constructs a state with given id.

		 @param[in]		id
						The id.
		 */
		State(uint64_t id = 0) : m_id(id) {}

		/**
		 Destructs this state.
		 */
		virtual ~State() {}

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
		 Requests the view setup details for the given frame.

		 @param[in]		viewer_setup
						A pointer to a viewer setup.
		 */
		virtual void RequestViewer(ViewerSetup *viewer_setup) {
			viewer_setup->m_view_clear_flags = 0;
		}

		/**
		 Updates this state.

		 @param[in]		elapsed_time
						The elapsed time since the previous update.
		 */
		virtual void Update(float elapsed_time) {
			// Supresses C4100: unreferenced formal parameter
			(void)elapsed_time;
		}

		/**
		 Render this state.
		 */
		virtual void Render() {}

		/**
		 Returns the id of this state.

		 @return		The id of this state.
		 */
		uint64_t GetId() const {
			return m_id;
		}

	private:

		/**
		 Application defined identifier (must be unique for state switching)
		 of this state.
		 */
		const uint64_t m_id;
	};
}