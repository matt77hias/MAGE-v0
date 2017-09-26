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
	Resource< ResourceT >::Resource(const wstring &guid)
		: m_guid(guid) {}

	template< typename ResourceT >
	Resource< ResourceT >::Resource(Resource< ResourceT > &&resource) = default;

	template< typename ResourceT >
	Resource< ResourceT >::~Resource() = default;

	template< typename ResourceT >
	inline const wstring &Resource< ResourceT >::GetFilename() const noexcept {
		return m_guid;
	}

	template< typename ResourceT >
	inline const wstring Resource< ResourceT >::GetName() const noexcept {
		return GetFileName(m_guid);
	}

	template< typename ResourceT >
	inline const wstring Resource< ResourceT >::GetPath() const noexcept {
		return GetPathName(m_guid);
	}
}