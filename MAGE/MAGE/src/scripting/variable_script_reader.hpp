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

		virtual HRESULT ParseLine(char *line) override;

		void ParseVSBool();
		void ParseVSInt();
		void ParseVSInt2();
		void ParseVSInt3();
		void ParseVSFloat();
		void ParseVSFloat2();
		void ParseVSFloat3();
		void ParseVSFloat4();
		void ParseVSColor();
		void ParseVSString();
		void ParseVSUnknown();

	private:

		VSReader(const VSReader &reader) = delete;
		VSReader &operator=(const VSReader &reader) = delete;

		vector< Variable * > &m_variable_buffer;
	};
}