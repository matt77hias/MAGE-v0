#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\timer\timer.hpp"
#include "utils\parallel\lock.hpp"

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
						The length of the progress bar. If @a bar_length is 
						equal to 0 the default length will be chosen.
		 */
		explicit ProgressReporter(const string &title, U32 nb_work, 
			char plus_char = '+', U32 bar_length = 0);

		/**
		 Constructs a progress reporter from the given progress reporter.

		 @param[in]		progress_reporter
						A reference to the progress reporter to copy.
		 */
		ProgressReporter(const ProgressReporter &progress_reporter) = delete;

		/**
		 Constructs a progress reporter by moving the given progress reporter.

		 @param[in]		progress_reporter
						A reference to the progress reporter to move.
		 */
		ProgressReporter(ProgressReporter &&progress_reporter);

		/**
		 Destructs this progress reporter.
		 */
		~ProgressReporter();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		progress_reporter
						A reference to the progress reporter to copy.
		 @return		A reference to the copy of the given progress reporter
						(i.e. this progress reporter).
		 */
		ProgressReporter &operator=(
			const ProgressReporter &progress_reporter) = delete;

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		progress_reporter
						A reference to the progress reporter to move.
		 @return		A reference to moved progress reporter (i.e. this 
						progress reporter).
		 */
		ProgressReporter &operator=(
			ProgressReporter &&progress_reporter) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates this progress reporter.

		 @param[in]		nb_work
						The number of work units that are done.
		 */
		void Update(U32 nb_work = 1);
		
		/**
		 Finishes this progress reporter.
		 */
		void Done();

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes this progress reporter.

		 @param[in]		title
						A reference to the title.
		 @param[in]		bar_length
						The length of the progress bar. If @a bar_length is 
						equal to 0 the default length will be chosen.
		 */
		void Initialize(const string &title, U32 bar_length = 0);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The total number of work units that need to be done.
		 */
		const U32 m_nb_work_total;

		/**
		 The number of work units that are already done
		 */
		U32 m_nb_work_done;

		/**
		 The total number of plusses that need to be outputted
		 by this progress reporter.
		 */
		U32 m_nb_plusses_total;

		/**
		 The total number of plusses that are already outputted
		 by this progress reporter.
		 */
		U32 m_nb_plusses_printed;

		/**
		 The character representing a work unit that is already done
		 of this progress reporter.
		 */
		const char m_plus_char;

		/**
		 A pointer to the output file stream of this progress reporter.
		 */
		FILE *m_fout;

		/**
		 A pointer to the output buffer of this progress reporter.
		 */
		UniquePtr< char [] > m_buffer;

		/**
		 A pointer to the current (output) character in the output buffer 
		 of this progress reporter.
		 */
		char *m_current_pos;

		/**
		 A pointer to the timer of this progress reporter.
		 */
		UniquePtr< Timer > m_timer;

		/**
		 The mutex needed for updating this progress reporter.
		 */
		Mutex m_mutex;
	};
}
