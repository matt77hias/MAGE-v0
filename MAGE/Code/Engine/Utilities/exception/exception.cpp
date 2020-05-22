//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Exception::Exception()
		: std::exception(),
		m_text{} {}

	Exception::Exception(const Exception& exception) = default;

	Exception::Exception(Exception&& exception) = default;

	Exception::~Exception() = default;

	Exception& Exception::operator=(const Exception& exception) = default;

	Exception& Exception::operator=(Exception&& exception) = default;

	const char* Exception::what() const noexcept {
		return m_text;
	}
}