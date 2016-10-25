#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of progress reporters.
	 */
	class ProgressReporter {

	public:

		/**
		 Constructs a progress reporter.

		 @param[in]		nb_work
						The number of parts of the total work.
		 @param[in]		title
						A reference to the title.
		 @param[in]		bar_length
						The length of the progress bar.
						If 0 the default length will be chosen.
		 */
		ProgressReporter(uint32_t nb_work, const string &title, uint32_t bar_length = 0);

		/**
		 Destructs this progress reporter.
		 */
		virtual ~ProgressReporter();

		/**
		 Updates this progress reporter.

		 @param[in]		nb_work
						The number of parts of the total work
						that are done.
		 */
		void Update(uint32_t nb_work = 1);
		
		/**
		 Finishes this progress reporter.
		 */
		void Done();

	private:

		/**
		 The number of parts of the total work.
		 */
		const uint32_t m_nb_work_total;
		
		/**
		 The number of parts of the total work that are already done.
		 */
		uint32_t m_nb_work_done;

		/**
		 The total number of plusses to output.
		 */
		uint32_t m_nb_plusses_total;

		/**
		 The total number of plusses that are already outputted.
		 */
		uint32_t m_nb_plusses_printed;
		
		/**
		 The timer of this progress reporter.
		 */
		Timer *m_timer;
		
		/**
		 The output file stream of this progress reporter.
		 */
		FILE *m_fout;
		
		/**
		 The output buffer of this progress reporter.
		 */
		char *m_buffer;

		/**
		 The current (output) position of this progress reporter.
		 */
		char *m_current_pos;
		
		/**
		 The mutex needed for updating this progress reporter.
		 */
		Mutex *m_mutex;
	};
}
