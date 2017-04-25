#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\line_reader.hpp"
#include "collection\collection.hpp"
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class VSReader final : public LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit VSReader(vector< Variable * > &variable_buffer)
			: LineReader(), m_variable_buffer(variable_buffer) {}
		VSReader(const VSReader &reader) = delete;
		VSReader(VSReader &&reader) = delete;
		virtual ~VSReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		VSReader &operator=(const VSReader &reader) = delete;
		VSReader &operator=(VSReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void ReadLine(char *line) override;

		void ReadVSBool();
		void ReadVSInt();
		void ReadVSInt2();
		void ReadVSInt3();
		void ReadVSFloat();
		void ReadVSFloat2();
		void ReadVSFloat3();
		void ReadVSFloat4();
		void ReadVSColor();
		void ReadVSString();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		vector< Variable * > &m_variable_buffer;
	};
}