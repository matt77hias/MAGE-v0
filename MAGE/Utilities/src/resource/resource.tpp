#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ResourceT >
	Resource< ResourceT >::Resource(wstring guid) noexcept
		: m_guid(std::move(guid)) {}

	template< typename ResourceT >
	Resource< ResourceT >::Resource(Resource &&resource) noexcept = default;

	template< typename ResourceT >
	Resource< ResourceT >::~Resource() = default;

	template< typename ResourceT >
	Resource< ResourceT > &Resource< ResourceT >
		::operator=(Resource &&resource) noexcept = default;

	template< typename ResourceT >
	[[nodiscard]] inline const wstring Resource< ResourceT >
		::GetName() const {
		
		return GetFileName(GetFilename());
	}

	template< typename ResourceT >
	[[nodiscard]] inline const wstring Resource< ResourceT >
		::GetPath() const {
		
		return GetPathName(GetFilename());
	}
}