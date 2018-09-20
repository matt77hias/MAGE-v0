//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\logging.hpp"
#include "logging\progress_reporter.hpp"
#include "system\timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

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
	class ProgressReporter::Impl {

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
		explicit Impl(std::string_view title,
					  U32 nb_work,
					  char progress_char = '+',
					  FU16 bar_length = 0u);

		/**
		 Constructs a progress reporter from the given progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to copy.
		 */
		Impl(const Impl& reporter) = delete;

		/**
		 Constructs a progress reporter by moving the given progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to move.
		 */
		Impl(Impl&& reporter) noexcept;

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
		Impl& operator=(const Impl& reporter) = delete;

		/**
		 Copies the given progress reporter to this progress reporter.

		 @param[in]		reporter
						A reference to the progress reporter to move.
		 @return		A reference to moved progress reporter (i.e. this
						progress reporter).
		 */
		Impl& operator=(Impl&& reporter) = delete;

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
						The title.
		 @param[in]		bar_length
						The length of the progress bar. If @a bar_length is
						equal to 0 the default length will be chosen.
		 */
		void Initialize(std::string_view title, FU16 bar_length = 0u);

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
		FU16 m_nb_progress_total;

		/**
		 The total number of progress characters that are currently outputted
		 by this progress reporter.
		 */
		FU16 m_nb_progress_printed;

		/**
		 The progress character of this progress reporter.
		 */
		char m_progress_char;

		/**
		 A pointer to the output file stream of this progress reporter.
		 */
		NotNull< std::FILE* > m_fout;

		/**
		 A pointer to the output buffer of this progress reporter.
		 */
		DynamicArray< char > m_buffer;

		/**
		 A pointer to the current character in the output buffer of this progress
		 reporter.
		 */
		char* m_current_pos;

		/**
		 The timer of this progress reporter.
		 */
		WallClockTimer m_timer;

		/**
		 The mutex of this progress reporter.
		 */
		std::mutex m_mutex;
	};

	ProgressReporter::Impl::Impl(std::string_view title,
								 U32 nb_work,
								 char progress_char,
								 FU16 bar_length)
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

	ProgressReporter::Impl::Impl(Impl&& reporter) noexcept
		: m_fout(stdout),
		m_mutex() {

		const std::scoped_lock lock(reporter.m_mutex);

		m_nb_work_total       = reporter.m_nb_work_total;
		m_nb_work_done        = reporter.m_nb_work_done;
		m_nb_progress_total   = reporter.m_nb_progress_total;
		m_nb_progress_printed = reporter.m_nb_progress_printed;
		m_progress_char       = reporter.m_progress_char;
		m_fout                = reporter.m_fout;
		m_buffer              = std::move(reporter.m_buffer);
		m_current_pos         = reporter.m_current_pos;
		m_timer               = std::move(reporter.m_timer);
	}

	ProgressReporter::Impl::~Impl() = default;

	void ProgressReporter::Impl::Initialize(std::string_view title,
											FU16 bar_length) {

		const std::scoped_lock lock(m_mutex);

		if (0u == bar_length) {
			bar_length = ConsoleWidth() - 28u;
		}

		m_nb_work_done        = 0u;
		m_nb_progress_printed = 0u;
		m_nb_progress_total   = std::max< FU16 >(2u, bar_length - static_cast< FU16 >(title.size()));

		// Initialize the output buffer.
		const std::size_t buffer_length = title.size() + m_nb_progress_total + 64u;
		m_buffer = DynamicArray< char >(buffer_length);

		WriteTo(NotNull< zstring >(m_buffer.data()), m_buffer.size(), "\r{}: [", title);
		m_current_pos = m_buffer.data() + strlen(m_buffer.data());
		auto s = m_current_pos;
		for (FU16 i = 0u; i < m_nb_progress_total; ++i) {
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
		std::fputs(m_buffer.data(), m_fout);

		std::fflush(m_fout);

		m_timer.Start();
	}

	void ProgressReporter::Impl::Update(U32 nb_work) {
		if (0u == nb_work || LoggingConfiguration::Get().IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		const std::scoped_lock lock(m_mutex);

		m_nb_work_done += nb_work;
		const auto fraction = static_cast< F32 >(m_nb_work_done) / m_nb_work_total;
		const auto nb_progress_total = std::min(static_cast< FU16 >(
			                                    round(fraction * m_nb_progress_total)),
					                            m_nb_progress_total);

		while (m_nb_progress_printed < nb_progress_total) {
			*m_current_pos = m_progress_char;
			++m_current_pos;
			++m_nb_progress_printed;
		}

		// Write the buffer to the output file stream.
		std::fputs(m_buffer.data(), m_fout);

		// Update elapsed time and estimated time to completion
		const auto time = static_cast< F32 >(m_timer.GetTotalDeltaTime().count());
		if (1.0f >= fraction) {
			// Writes the string format to the output file stream.
			WriteTo(m_fout, " ({:.1f}s)       ", time);
		}
		else {
			const auto remaining_time = std::max(0.0f, time / fraction - time);
			// Writes the string format to the output file stream.
			WriteTo(m_fout, " ({:.1f}s|{:.1f}s)  ", time, remaining_time);
		}

		std::fflush(m_fout);
	}

	void ProgressReporter::Impl::Done() {
		if (LoggingConfiguration::Get().IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		const std::scoped_lock lock(m_mutex);

		while (m_nb_progress_printed < m_nb_progress_total) {
			*m_current_pos = m_progress_char;
			++m_current_pos;
			++m_nb_progress_printed;
		}

		// Write the buffer to the output file stream.
		std::fputs(m_buffer.data(), m_fout);

		// Update elapsed time
		const auto time = static_cast< F32 >(m_timer.GetTotalDeltaTime().count());
		// Writes the string format to the output file stream.
		WriteTo(m_fout, " ({:.1f}s)       \n", time);

		std::fflush(m_fout);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ProgressReporter
	//-------------------------------------------------------------------------
	#pragma region

	ProgressReporter::ProgressReporter(std::string_view title,
									   U32 nb_work,
									   char progress_char,
									   FU16 bar_length)
		: m_impl(MakeUnique< Impl >(title,
									nb_work,
									progress_char,
									bar_length)) {}

	ProgressReporter::ProgressReporter(
		ProgressReporter&& reporter) noexcept = default;

	ProgressReporter::~ProgressReporter() = default;

	void ProgressReporter::Update(U32 nb_work) {
		m_impl->Update(nb_work);
	}

	void ProgressReporter::Done() {
		m_impl->Done();
	}

	#pragma endregion
}