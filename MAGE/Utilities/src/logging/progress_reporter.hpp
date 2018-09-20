#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of progress reporters.
	 */
	class ProgressReporter {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a progress reporter.

		 @param[in]		title
						The title.
		 @param[in]		nb_work
						The total number of work units.
		 @param[in]		progress_char
						The character representing the progress.
		 @param[in]		bar_length
						The length of the progress bar. If @a bar_length is
						equal to 0 the default length will be chosen.
		 */
		explicit ProgressReporter(std::string_view title,
			                      U32 nb_work,
			                      char progress_char = '+',
			                      FU16 bar_length = 0u);

		/**
		 Constructs a progress reporter from the given progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to copy.
		 */
		ProgressReporter(const ProgressReporter& reporter) = delete;

		/**
		 Constructs a progress reporter by moving the given progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to move.
		 */
		ProgressReporter(ProgressReporter&& reporter) noexcept;

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
		ProgressReporter& operator=(const ProgressReporter& reporter) = delete;

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to move.
		 @return		A reference to moved progress reporter (i.e. this
						progress reporter).
		 */
		ProgressReporter& operator=(ProgressReporter&& reporter) = delete;

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
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 A pointer to the implementation of this progress reporter.
		 */
		UniquePtr< Impl > m_impl;
	};
}
