#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "text\sprite_text.hpp"
#include "parallel\lock.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class TextConsoleScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit TextConsoleScript(SpriteText *text,
			uint32_t nb_rows, uint32_t nb_columns);
		TextConsoleScript(const TextConsoleScript &script) = delete;
		TextConsoleScript(TextConsoleScript &&script);
		virtual ~TextConsoleScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		TextConsoleScript &operator=(const TextConsoleScript &script) = delete;
		TextConsoleScript &operator=(TextConsoleScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override;
		
		void Clear();
		void Write(const wchar_t *str);
		void WriteLine(const wchar_t *str);
		void Format(const wchar_t *format, ...);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void ProcessString(const wchar_t *str);
		void IncrementRow();

		void SetCharacter(wchar_t character, uint32_t row, uint32_t column);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SpriteText * const m_text;

		const uint32_t m_nb_rows;
		const uint32_t m_nb_columns;
		uint32_t m_current_column;
		uint32_t m_current_row;

		UniquePtr< wchar_t[] > m_buffer;
		vector< wchar_t > m_temp_buffer;
		
		Mutex m_mutex;
	};
}