#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "file\file_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//---------------------------------------------------------------------
// Engine Definitions
//---------------------------------------------------------------------
namespace mage {

	template< typename ResourceT >
	Resource< ResourceT >::Resource(const wstring &guid, const wstring &fname)
		: m_guid(guid), m_fname(fname) {}

	template< typename ResourceT >
	Resource< ResourceT >::Resource(Resource< ResourceT > &&resource) = default;

	template< typename ResourceT >
	Resource< ResourceT >::~Resource() = default;

	template< typename ResourceT >
	inline bool Resource< ResourceT >::IsFileResource() const noexcept {
		return m_fname == L"";
	}

	template< typename ResourceT >
	inline bool Resource< ResourceT >::IsMemoryResource() const noexcept {
		return !IsFileResource();
	}

	template< typename ResourceT >
	inline const wstring &Resource< ResourceT >::GetFilename() const noexcept {
		Assert(IsFileResource());
		return m_fname;
	}

	template< typename ResourceT >
	inline const wstring Resource< ResourceT >::GetName() const noexcept {
		Assert(IsFileResource());
		return GetFileName(m_fname);
	}

	template< typename ResourceT >
	inline const wstring Resource< ResourceT >::GetPath() const noexcept {
		Assert(IsFileResource());
		return GetPathName(m_fname);
	}
}