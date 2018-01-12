#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "sprite\sprite_text.hpp"

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
namespace mage::script {

	class TextConsoleScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit TextConsoleScript(U32 nb_rows, U32 nb_columns);
		TextConsoleScript(const TextConsoleScript &script);
		TextConsoleScript(TextConsoleScript &&script) noexcept;
		virtual ~TextConsoleScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		TextConsoleScript &operator=(const TextConsoleScript &script) = delete;
		TextConsoleScript &operator=(TextConsoleScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load() override;
		virtual void Update([[maybe_unused]] F64 delta_time) override;
		
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

		void SetCharacter(wchar_t character, U32 row, U32 column);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ProxyPtr< SpriteText > m_text;

		const U32 m_nb_rows;
		const U32 m_nb_columns;
		U32 m_current_column;
		U32 m_current_row;

		UniquePtr< wchar_t[] > m_buffer;
		std::vector< wchar_t > m_temp_buffer;
		
		std::mutex m_mutex;
	};
}