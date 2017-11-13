//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\text_console_script.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	TextConsoleScript::TextConsoleScript(
		SpriteText *text, U32 nb_rows, U32 nb_columns)
		: BehaviorScript(),
		m_nb_rows(nb_rows), m_nb_columns(nb_columns + 1),
		m_current_column(0), m_current_row(0),
		m_buffer(MakeUnique< wchar_t[] >((nb_columns + 1) * nb_rows + 1)), 
		m_temp_buffer(), m_mutex(), m_text(text) {
		
		Assert(m_text);

		Clear();
	}

	TextConsoleScript::TextConsoleScript(TextConsoleScript &&script) = default;

	TextConsoleScript::~TextConsoleScript() = default;

	void TextConsoleScript::Update([[maybe_unused]] F64 delta_time) {
		const MutexLock lock(m_mutex);

		SetCharacter(L'\n', m_current_row, m_current_column);
		m_text->SetText(m_buffer.get());
	}

	void TextConsoleScript::Clear() {
		memset(m_buffer.get(), 0, 
			sizeof(wchar_t) * (m_nb_columns * m_nb_rows + 1));
		m_current_row    = 0;
		m_current_column = 0;
	}

	void TextConsoleScript::Write(const wchar_t *str) {
		const MutexLock lock(m_mutex);
		ProcessString(str);
	}

	void TextConsoleScript::WriteLine(const wchar_t *str) {
		const MutexLock lock(m_mutex);
		ProcessString(str);
		IncrementRow();
	}

	void TextConsoleScript::Format(const wchar_t *format, ...) {
		const MutexLock lock(m_mutex);

		va_list args;
		// Retrieve the additional arguments after format
		va_start(args, format);

		const size_t nb_characters 
			= static_cast< size_t >(_vscwprintf(format, args) + 1);
		if (m_temp_buffer.size() < nb_characters) {
			m_temp_buffer.resize(nb_characters);
		}

		memset(m_temp_buffer.data(), 0, sizeof(wchar_t) * nb_characters);
		vswprintf_s(m_temp_buffer.data(), m_temp_buffer.size(), format, args);

		// End using variable argument list
		va_end(args);

		ProcessString(m_temp_buffer.data());
	}

	void TextConsoleScript::ProcessString(const wchar_t *str) {
		for (const wchar_t *character = str; 
			*character != L'\0'; ++character, ++m_current_column) {
			
			if (L'\n' == *character) {
				IncrementRow();
				continue;
			}

			if (m_current_column == m_nb_columns - 1) {
				IncrementRow();
			}

			SetCharacter(*character, m_current_row, m_current_column);
		}
	}

	void TextConsoleScript::SetCharacter(wchar_t character, U32 row, U32 column) {
		const size_t index = row * m_nb_columns + column;
		m_buffer[index] = character;
	}

	void TextConsoleScript::IncrementRow() {
		// Set end of line character.
		SetCharacter(L'\n', m_current_row, m_current_column);

		// Update position.
		m_current_row    = (m_current_row + 1) % m_nb_rows;
		m_current_column = 0;

		// Clear new current row.
		const size_t index = m_current_row * m_nb_columns;
		memset(&m_buffer[index], 0, sizeof(wchar_t) * (m_nb_columns));
	}
}