#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\writer.hpp"
#include "collection\collection.hpp"
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class VSWriter : Writer {

	public:

		VSWriter(vector< Variable * > &variable_buffer)
			: Writer(), m_variable_buffer(variable_buffer) {}
		virtual ~VSWriter() = default;

	protected:

		virtual HRESULT Write() const override;

	private:

		VSWriter(const VSWriter &reader) = delete;
		VSWriter &operator=(const VSWriter &reader) = delete;

		vector< Variable * > &m_variable_buffer;
	};
}