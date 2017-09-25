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
			u32 nb_rows, u32 nb_columns);
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

		virtual void Update(f64 delta_time) override;
		
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

		void SetCharacter(wchar_t character, u32 row, u32 column);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SpriteText * const m_text;

		const u32 m_nb_rows;
		const u32 m_nb_columns;
		u32 m_current_column;
		u32 m_current_row;

		UniquePtr< wchar_t[] > m_buffer;
		vector< wchar_t > m_temp_buffer;
		
		Mutex m_mutex;
	};
}