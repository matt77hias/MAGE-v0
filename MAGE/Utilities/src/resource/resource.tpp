#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ResourceT >
	Resource< ResourceT >::Resource(wstring guid) noexcept
		: m_guid(std::move(guid)) {
		TransformToLowerCase(m_guid);
	}

	template< typename ResourceT >
	Resource< ResourceT >::Resource(Resource&& resource) noexcept = default;

	template< typename ResourceT >
	Resource< ResourceT >::~Resource() = default;

	template< typename ResourceT >
	Resource< ResourceT >& Resource< ResourceT >
		::operator=(Resource&& resource) noexcept = default;

	template< typename ResourceT >
	[[nodiscard]]
	bool Resource< ResourceT >::IsFileResource() const {
		return std::filesystem::is_regular_file(m_guid);
	}

	template< typename ResourceT >
	[[nodiscard]]
	inline const std::filesystem::path Resource< ResourceT >::GetPath() const {
		return m_guid;
	}
}