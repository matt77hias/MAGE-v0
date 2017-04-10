#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "string\string.hpp"
#include "logging\timer.hpp"
#include "parallel\lock.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of progress reporters.
	 */
	class ProgressReporter final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a progress reporter.

		 @param[in]		title
						A reference to the title.
		 @param[in]		nb_work
						The total number of work units.
		 @param[in]		plus_char
						The character representing a work unit 
						that is already done.
		 @param[in]		bar_length
						The length of the progress bar.
						If 0 the default length will be chosen.
		 */
		explicit ProgressReporter(const string &title, uint32_t nb_work, char plus_char = '+', uint32_t bar_length = 0);

		/**
		 Constructs a progress reporter from the given progress reporter.

		 @param[in]		progress_reporter
						A reference to the progress reporter.
		 */
		ProgressReporter(const ProgressReporter &progress_reporter) = delete;

		/**
		 Constructs a progress reporter from the given progress reporter.

		 @param[in]		progress_reporter
						A reference to the progress reporter.
		 */
		ProgressReporter(ProgressReporter &&progress_reporter) = default;

		/**
		 Destructs this progress reporter.
		 */
		virtual ~ProgressReporter();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		progress_reporter
						A reference to the progress reporter to copy from.
		 @return		A reference to the copy of the given progress reporter
						(i.e. this progress reporter).
		 */
		ProgressReporter &operator=(const ProgressReporter &progress_reporter) = delete;

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		progress_reporter
						A reference to the progress reporter to copy from.
		 @return		A reference to the copy of the given progress reporter
						(i.e. this progress reporter).
		 */
		ProgressReporter &operator=(ProgressReporter &&progress_reporter) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates this progress reporter.

		 @param[in]		nb_work
						The number of work units that are done.
		 */
		void Update(uint32_t nb_work = 1);
		
		/**
		 Finishes this progress reporter.
		 */
		void Done();

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The total number of work units that need to be done.
		 */
		const uint32_t m_nb_work_total;

		/**
		 The number of work units that are already done.
		 */
		uint32_t m_nb_work_done;

		/**
		 The total number of plusses that need to be outputted.
		 */
		uint32_t m_nb_plusses_total;

		/**
		 The total number of plusses that are already outputted.
		 */
		uint32_t m_nb_plusses_printed;

		/**
		 The character representing a work unit that is already done.
		 */
		const char m_plus_char;

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
		 The timer of this progress reporter.
		 */
		UniquePtr< Timer > m_timer;

		/**
		 The mutex needed for updating this progress reporter.
		 */
		Mutex m_mutex;
	};
}
