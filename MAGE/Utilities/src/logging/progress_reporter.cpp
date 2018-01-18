//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\progress_reporter.hpp"
#include "logging\logging.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ProgressReporter::ProgressReporter(const string &title, 
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

	ProgressReporter::~ProgressReporter() = default;

	void ProgressReporter::Initialize(const string &title, U16 bar_length) {
		if (0u == bar_length) {
			bar_length = ConsoleWidth() - U16(28u);
		}

		m_nb_progress_total = std::max< U16 >(2, bar_length - static_cast< U16 >(title.size()));
		
		// Initialize the output buffer.
		const size_t buffer_length = title.size() + m_nb_progress_total + 64;
		m_buffer = MakeUnique< char[] >(buffer_length);
		
		snprintf(m_buffer.get(), buffer_length, "\r%s: [", title.c_str());
		m_current_pos = m_buffer.get() + strlen(m_buffer.get());
		char *s = m_current_pos;
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

	void ProgressReporter::Update(U32 nb_work) {
		if (0u == nb_work || LoggingConfiguration::Get().IsQuiet()) {
			// Do not output the progression in quiet mode.
			return;
		}

		const std::lock_guard< std::mutex > lock(m_mutex);
		
		m_nb_work_done += nb_work;
		const F32 fraction = static_cast< F32 >(m_nb_work_done) / m_nb_work_total;
		const U16 nb_progress_total = std::min(static_cast< U16 >(
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
		const F32 time = static_cast< F32 >(m_timer.GetTotalDeltaTime());
		if (1.0f == fraction) {
			// Writes the string format to the output file stream.
			fprintf(m_fout, " (%.1fs)       ", time);
		}
		else {
			const F32 remaining_time = std::max(0.0f, time / fraction - time);
			// Writes the string format to the output file stream.
			fprintf(m_fout, " (%.1fs|%.1fs)  ", time, remaining_time);
		}

		fflush(m_fout);
	}

	void ProgressReporter::Done() {
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
		const F32 time = static_cast< F32 >(m_timer.GetTotalDeltaTime());
		// Writes the string format to the output file stream.
		fprintf(m_fout, " (%.1fs)       \n", time);
	
		fflush(m_fout);
	}
}