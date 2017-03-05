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
	 Imports the materials from the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[out]	material_buffer
					A reference to the empty material buffer.
	 @return		A success/error value.
	*/
	HRESULT ImportMaterialFromFile(const wstring &fname, vector< Material > &material_buffer);
}