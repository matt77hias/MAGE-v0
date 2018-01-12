#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "timer\timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <mutex>

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
		 @param[in]		progress_char
						The character representing the progress.
		 @param[in]		bar_length
						The length of the progress bar. If @a bar_length is 
						equal to 0 the default length will be chosen.
		 */
		explicit ProgressReporter(const string &title, 
			                      U32 nb_work, 
			                      char progress_char = '+', 
			                      U16 bar_length = 0u);

		/**
		 Constructs a progress reporter from the given progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to copy.
		 */
		ProgressReporter(const ProgressReporter &reporter) = delete;

		/**
		 Constructs a progress reporter by moving the given progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to move.
		 */
		ProgressReporter(ProgressReporter &&reporter) = delete;

		/**
		 Destructs this progress reporter.
		 */
		~ProgressReporter();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to copy.
		 @return		A reference to the copy of the given progress reporter
						(i.e. this progress reporter).
		 */
		ProgressReporter &operator=(const ProgressReporter &reporter) = delete;

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to move.
		 @return		A reference to moved progress reporter (i.e. this 
						progress reporter).
		 */
		ProgressReporter &operator=(ProgressReporter &&reporter) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates this progress reporter.

		 @param[in]		nb_work
						The number of work units that are done.
		 */
		void Update(U32 nb_work = 1u);
		
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
		void Initialize(const string &title, U16 bar_length = 0u);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The total number of work units that need to be done.
		 */
		U32 m_nb_work_total;

		/**
		 The number of work units that are currently done.
		 */
		U32 m_nb_work_done;

		/**
		 The total number of progress characters that need to be outputted by 
		 this progress reporter.
		 */
		U16 m_nb_progress_total;

		/**
		 The total number of progress characters that are currently outputted 
		 by this progress reporter.
		 */
		U16 m_nb_progress_printed;

		/**
		 The progress character of this progress reporter.
		 */
		char m_progress_char;

		/**
		 A pointer to the output file stream of this progress reporter.
		 */
		FILE *m_fout;

		/**
		 A pointer to the output buffer of this progress reporter.
		 */
		UniquePtr< char[] > m_buffer;

		/**
		 A pointer to the current character in the output buffer of this progress 
		 reporter.
		 */
		char *m_current_pos;

		/**
		 The timer of this progress reporter.
		 */
		Timer m_timer;

		/**
		 The mutex of this progress reporter.
		 */
		std::mutex m_mutex;
	};
}
