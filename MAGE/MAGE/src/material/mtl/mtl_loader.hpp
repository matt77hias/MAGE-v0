#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "collection\collection.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
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
	HRESULT ImportMTLMaterialFromFile(const wstring &fname, vector< Material > &material_buffer);
}