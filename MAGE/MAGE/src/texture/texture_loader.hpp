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

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a texture_resource_view is not equal to @c nullptr.
	 @param[in]		fname
					A reference to the filename.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	texture_resource_view
					A pointer to a pointer to a shader resource view.
	 @throws		FormattedException
					Failed to import the texture from file.
	 */
	void ImportTextureFromFile(const wstring &fname, ID3D11Device2 *device, ID3D11ShaderResourceView **texture_resource_view);
}