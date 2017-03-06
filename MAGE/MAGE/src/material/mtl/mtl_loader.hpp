#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the materials from the given MTL file.

	 @param[in]		fname
					A reference to the MTL filename.
	 @param[out]	material_buffer
					A reference to the empty material buffer.
	 @return		A success/error value.
	 */
	HRESULT ImportMTLMaterialFromFile(const wstring &fname, vector< Material > &material_buffer);
}