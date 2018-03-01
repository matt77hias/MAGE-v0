//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\progress_reporter.hpp"
#include "logging\logging.hpp"
#include "system\timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>
#include <mutex>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ProgressReporter::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of progress reporters.
	 */
	class ProgressReporter::Impl final {

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
		explicit Impl(const string &title, 
					  U32 nb_work, 
					  char progress_char = '+', 
					  U16 bar_length = 0u);

		/**
		 Constructs a progress reporter from the given progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to copy.
		 */
		Impl(const Impl &reporter) = delete;

		/**
		 Constructs a progress reporter by moving the given progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to move.
		 */
		Impl(Impl &&reporter) = delete;

		/**
		 Destructs this progress reporter.
		 */
		~Impl();

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
		Impl &operator=(const Impl &reporter) = delete;

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to move.
		 @return		A reference to moved progress reporter (i.e. this 
						progress reporter).
		 */
		Impl &operator=(Impl &&reporter) = delete;

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
		WallClockTimer m_timer;

		/**
		 The mutex of this progress reporter.
		 */
		std::mutex m_mutex;
	};

	ProgressReporter::Impl::Impl(const string &title, 
								 U32 nb_work, 
								 char progress_char, 
								 U16 bar_length)
		: m_nb_work_total(nb_work), 
		m_nb_work_done(0u), 
		m_nb_progress_total(),
		m_nb_progress_printed(0u), 
		m_progress_char(progress_char),
		m_fout(stdout), 
		m_buffer(), 
		m_current_pos(nullptr), 
		m_timer(), 
		m_mutex() {
		
		Initialize(title, bar_length);
	}

	ProgressReporter::Impl::~Impl() = default;

	void ProgressReporter::Impl::Initialize(const string &title, 
											U16 bar_length) {
		if (0u == bar_length) {
			bar_length = ConsoleWidth() - U16(28u);
		}

		m_nb_progress_total = std::max< U16 >(2, bar_length - static_cast< U16 >(title.size()));
		
		// Initialize the output buffer.
		const size_t buffer_length = title.size() + m_nb_progress_total + 64;
		m_buffer = MakeUnique< char[] >(buffer_length);
		
		snprintf(m_buffer.get(), buffer_length, "\r%s: [", title.c_str());
		m_current_pos = m_buffer.get() + strlen(m_buffer.get());
		auto s = m_current_pos;
		for (U16 i = 0; i < m_nb_progress_total; ++i) {
			*s++ = ' ';
		}
		*s++ = ']';
		*s++ = ' ';
		*s++ = '\0';

		if (LoggingConfiguration::Get().IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		// Write the buffer to the output file stream.
		fputs(m_buffer.get(), m_fout);

		fflush(m_fout);

		m_timer.Start();
	}

	void ProgressReporter::Impl::Update(U32 nb_work) {
		if (0u == nb_work || LoggingConfiguration::Get().IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		const std::lock_guard< std::mutex > lock(m_mutex);
		
		m_nb_work_done += nb_work;
		const auto fraction = static_cast< F32 >(m_nb_work_done) / m_nb_work_total;
		const auto nb_progress_total = std::min(static_cast< U16 >(
			                                    round(fraction * m_nb_progress_total)),
					                            m_nb_progress_total);
		
		while (m_nb_progress_printed < nb_progress_total) {
			*m_current_pos = m_progress_char;
			++m_current_pos;
			++m_nb_progress_printed;
		}

		// Write the buffer to the output file stream.
		fputs(m_buffer.get(), m_fout);

		// Update elapsed time and estimated time to completion
		const auto time = static_cast< F32 >(m_timer.GetTotalDeltaTime());
		if (1.0f == fraction) {
			// Writes the string format to the output file stream.
			fprintf(m_fout, " (%.1fs)       ", time);
		}
		else {
			const auto remaining_time = std::max(0.0f, time / fraction - time);
			// Writes the string format to the output file stream.
			fprintf(m_fout, " (%.1fs|%.1fs)  ", time, remaining_time);
		}

		fflush(m_fout);
	}

	void ProgressReporter::Impl::Done() {
		if (LoggingConfiguration::Get().IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		const std::lock_guard< std::mutex > lock(m_mutex);
		
		while (m_nb_progress_printed < m_nb_progress_total) {
			*m_current_pos = m_progress_char;
			++m_current_pos;
			++m_nb_progress_printed;
		}

		// Write the buffer to the output file stream.
		fputs(m_buffer.get(), m_fout);

		// Update elapsed time
		const auto time = static_cast< F32 >(m_timer.GetTotalDeltaTime());
		// Writes the string format to the output file stream.
		fprintf(m_fout, " (%.1fs)       \n", time);
	
		fflush(m_fout);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ProgressReporter
	//-------------------------------------------------------------------------
	#pragma region

	ProgressReporter::ProgressReporter(const string &title, 
									   U32 nb_work, 
									   char progress_char, 
									   U16 bar_length)
		: m_impl(MakeUnique< Impl >(title, 
									nb_work, 
									progress_char, 
									bar_length)) {}

	ProgressReporter::~ProgressReporter() = default;

	void ProgressReporter::Update(U32 nb_work) {
		m_impl->Update(nb_work);
	}

	void ProgressReporter::Done() {
		m_impl->Done();
	}

	#pragma endregion
}