#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"
#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the texture from the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[in]		device
					A reference to the rendering device.
	 @param[out]	texture_resource_view
					A pointer to a pointer to a shader resource view.
	 @return		A success/error value.
	 */
	HRESULT ImportTextureFromFile(const wstring &fname, ID3D11Device2 &device, ID3D11ShaderResourceView **texture_resource_view);
}