#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma warning(push)
#pragma warning(disable : 4005)
#pragma warning(pop)

#ifndef _Use_decl_annotations_
#define _Use_decl_annotations_
#endif

namespace mage {

	enum struct DDS_ALPHA_MODE {
		Unknown       = 0,
		Straight      = 1,
		Premultiplied = 2,
		Opaque        = 3,
		Custom        = 4,
	};

	// Standard version
	HRESULT CreateDDSTextureFromMemory(_In_ ID3D11Device2 *device,
		_In_reads_bytes_(dds_dataSize) const uint8_t *dds_data,
		_In_ size_t dds_dataSize,
		_Outptr_opt_ ID3D11Resource **texture,
		_Outptr_opt_ ID3D11ShaderResourceView **texture_view,
		_In_ size_t maxsize = 0,
		_Out_opt_ DDS_ALPHA_MODE *alpha_mode = nullptr
	);

	HRESULT CreateDDSTextureFromFile(_In_ ID3D11Device2 *device,
		_In_z_ const wchar_t *szFileName,
		_Outptr_opt_ ID3D11Resource **texture,
		_Outptr_opt_ ID3D11ShaderResourceView **texture_view,
		_In_ size_t maxsize = 0,
		_Out_opt_ DDS_ALPHA_MODE *alpha_mode = nullptr
	);

	// Standard version with optional auto-gen mipmap support
	HRESULT CreateDDSTextureFromMemory(_In_ ID3D11Device2 *device,
		_In_opt_ ID3D11DeviceContext *device_context,
		_In_reads_bytes_(dds_dataSize) const uint8_t *dds_data,
		_In_ size_t dds_dataSize,
		_Outptr_opt_ ID3D11Resource **texture,
		_Outptr_opt_ ID3D11ShaderResourceView **texture_view,
		_In_ size_t maxsize = 0,
		_Out_opt_ DDS_ALPHA_MODE *alpha_mode = nullptr
	);

	HRESULT CreateDDSTextureFromFile(_In_ ID3D11Device2 *device,
		_In_opt_ ID3D11DeviceContext *device_context,
		_In_z_ const wchar_t *szFileName,
		_Outptr_opt_ ID3D11Resource **texture,
		_Outptr_opt_ ID3D11ShaderResourceView **texture_view,
		_In_ size_t maxsize = 0,
		_Out_opt_ DDS_ALPHA_MODE *alpha_mode = nullptr
	);

	// Extended version
	HRESULT CreateDDSTextureFromMemoryEx(_In_ ID3D11Device2 *device,
		_In_reads_bytes_(dds_dataSize) const uint8_t *dds_data,
		_In_ size_t dds_dataSize,
		_In_ size_t maxsize,
		_In_ D3D11_USAGE usage,
		_In_ uint32_t bindFlags,
		_In_ uint32_t cpu_access_flags,
		_In_ uint32_t misc_flags,
		_In_ bool forceSRGB,
		_Outptr_opt_ ID3D11Resource **texture,
		_Outptr_opt_ ID3D11ShaderResourceView **texture_view,
		_Out_opt_ DDS_ALPHA_MODE* alpha_mode = nullptr
	);

	HRESULT CreateDDSTextureFromFileEx(_In_ ID3D11Device2 *device,
		_In_z_ const wchar_t* szFileName,
		_In_ size_t maxsize,
		_In_ D3D11_USAGE usage,
		_In_ uint32_t bindFlags,
		_In_ uint32_t cpu_access_flags,
		_In_ uint32_t misc_flags,
		_In_ bool forceSRGB,
		_Outptr_opt_ ID3D11Resource **texture,
		_Outptr_opt_ ID3D11ShaderResourceView **texture_view,
		_Out_opt_ DDS_ALPHA_MODE *alpha_mode = nullptr
	);

	// Extended version with optional auto-gen mipmap support
	HRESULT CreateDDSTextureFromMemoryEx(_In_ ID3D11Device2 *device,
		_In_opt_ ID3D11DeviceContext* device_context,
		_In_reads_bytes_(dds_dataSize) const uint8_t *dds_data,
		_In_ size_t dds_dataSize,
		_In_ size_t maxsize,
		_In_ D3D11_USAGE usage,
		_In_ uint32_t bindFlags,
		_In_ uint32_t cpu_access_flags,
		_In_ uint32_t misc_flags,
		_In_ bool forceSRGB,
		_Outptr_opt_ ID3D11Resource **texture,
		_Outptr_opt_ ID3D11ShaderResourceView **texture_view,
		_Out_opt_ DDS_ALPHA_MODE* alpha_mode = nullptr
	);

	HRESULT CreateDDSTextureFromFileEx(_In_ ID3D11Device2 *device,
		_In_opt_ ID3D11DeviceContext *device_context,
		_In_z_ const wchar_t *szFileName,
		_In_ size_t maxsize,
		_In_ D3D11_USAGE usage,
		_In_ uint32_t bindFlags,
		_In_ uint32_t cpu_access_flags,
		_In_ uint32_t misc_flags,
		_In_ bool forceSRGB,
		_Outptr_opt_ ID3D11Resource **texture,
		_Outptr_opt_ ID3D11ShaderResourceView **texture_view,
		_Out_opt_ DDS_ALPHA_MODE *alpha_mode = nullptr
	);
}