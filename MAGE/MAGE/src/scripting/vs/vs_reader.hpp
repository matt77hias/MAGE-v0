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

	class VSReader : public LineReader {

	public:

		VSReader(vector< Variable * > &variable_buffer)
			: LineReader(), m_variable_buffer(variable_buffer) {}
		virtual ~VSReader() = default;

	protected:

		virtual HRESULT ReadLine(char *line) override;

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
		void ReadVSUnknown();

	private:

		VSReader(const VSReader &reader) = delete;
		VSReader(VSReader &&reader) = delete;
		VSReader &operator=(const VSReader &reader) = delete;
		VSReader &operator=(VSReader &&reader) = delete;

		vector< Variable * > &m_variable_buffer;
	};
}