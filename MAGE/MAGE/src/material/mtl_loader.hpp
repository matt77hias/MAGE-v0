#pragma once

//-----------------------------------------------------------------------------
// System Defines
//-----------------------------------------------------------------------------
#pragma region

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <windows.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\collection.hpp"
#include "string\string_utils.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Loads an MTL material from file.

	 @param[in]		fname
					A reference to the file name.
	 @param[out]	material_buffer
					A reference to the empty material buffer.
	 @return		A success/error value.
	 */
	HRESULT LoadMTLMaterialFromFile(const wstring &fname, vector< Material > &material_buffer);
}