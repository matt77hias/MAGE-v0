//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text_console_script.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	TextConsoleScript::TextConsoleScript(U32 nb_rows, U32 nb_columns)
		: BehaviorScript(),
		m_text(),
		m_nb_rows(nb_rows), 
		m_nb_columns(nb_columns + 1),
		m_current_column(0), 
		m_current_row(0),
		m_buffer(MakeUnique< wchar_t[] >((nb_columns + 1) * nb_rows + 1)), 
		m_temp_buffer(), 
		m_mutex() {
		
		Clear();
	}

	TextConsoleScript::TextConsoleScript(const TextConsoleScript& script) 
		: BehaviorScript(script),
		m_text(),
		m_nb_rows(script.m_nb_rows),
		m_nb_columns(script.m_nb_columns),
		m_current_column(script.m_current_column),
		m_current_row(script.m_current_row),
		m_buffer(MakeUnique< wchar_t[] >((script.m_nb_columns) * script.m_nb_rows + 1)),
		m_temp_buffer(script.m_temp_buffer),
		m_mutex() {

		memcpy(m_buffer.get(), script.m_buffer.get(),
			   sizeof(wchar_t) * (m_nb_columns * m_nb_rows + 1));

	}

	TextConsoleScript::TextConsoleScript(TextConsoleScript&& script) noexcept 
		: BehaviorScript(std::move(script)),
		m_text(std::move(script.m_text)),
		m_nb_rows(script.m_nb_rows),
		m_nb_columns(script.m_nb_columns),
		m_current_column(script.m_current_column),
		m_current_row(script.m_current_row),
		m_buffer(std::move(script.m_buffer)),
		m_temp_buffer(std::move(script.m_temp_buffer)),
		m_mutex() {}

	TextConsoleScript::~TextConsoleScript() = default;

	void TextConsoleScript::Load([[maybe_unused]] Engine& engine) {
		ThrowIfFailed(HasOwner(), 
					  "This script needs to be attached to a node.");

		m_text = GetOwner()->Get< rendering::SpriteText >();
		ThrowIfFailed((nullptr != m_text), 
					  "This script needs a sprite text component.");
	}

	void TextConsoleScript::Update([[maybe_unused]] Engine& engine) {
		const std::scoped_lock lock(m_mutex);

		SetCharacter(L'\n', m_current_row, m_current_column);
		m_text->SetText(std::wstring(m_buffer.get()));
	}

	void TextConsoleScript::Clear() {
		memset(m_buffer.get(), 0, 
			   sizeof(wchar_t) * (m_nb_columns * m_nb_rows + 1));
		m_current_row    = 0;
		m_current_column = 0;
	}

	void TextConsoleScript::Write(NotNull< const_wzstring > str) {
		const std::scoped_lock lock(m_mutex);
		
		ProcessString(str);
	}

	void TextConsoleScript::WriteLine(NotNull< const_wzstring > str) {
		const std::scoped_lock lock(m_mutex);
		
		ProcessString(str);
		IncrementRow();
	}

	void TextConsoleScript::Format(const_wzstring format, ...) {
		const std::scoped_lock lock(m_mutex);

		va_list args;
		// Retrieve the additional arguments after format
		va_start(args, format);

		const auto nb_characters 
			= static_cast< std::size_t >(_vscwprintf(format, args) + 1);
		if (m_temp_buffer.size() < nb_characters) {
			m_temp_buffer.resize(nb_characters);
		}

		memset(m_temp_buffer.data(), 0, sizeof(wchar_t) * nb_characters);
		vswprintf_s(m_temp_buffer.data(), m_temp_buffer.size(), format, args);

		// End using variable argument list
		va_end(args);

		ProcessString(NotNull< const_wzstring >(m_temp_buffer.data()));
	}

	void TextConsoleScript::ProcessString(NotNull< const_wzstring > str) {
		const wchar_t* const c_str = str;
		for (auto character = c_str;
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
		const std::size_t index = row * m_nb_columns + column;
		m_buffer[index] = character;
	}

	void TextConsoleScript::IncrementRow() {
		// Set end of line character.
		SetCharacter(L'\n', m_current_row, m_current_column);

		// Update position.
		m_current_row    = (m_current_row + 1) % m_nb_rows;
		m_current_column = 0;

		// Clear new current row.
		const std::size_t index = m_current_row * m_nb_columns;
		memset(&m_buffer[index], 0, sizeof(wchar_t) * (m_nb_columns));
	}
}