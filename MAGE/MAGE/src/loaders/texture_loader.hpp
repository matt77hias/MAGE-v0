#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the texture from the given file.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a texture_srv is not equal to @c nullptr.
	 @param[in]		fname
					A reference to the filename.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	texture_srv
					A pointer to a pointer to a shader resource view.
	 @throws		FormattedException
					Failed to import the texture from file.
	 */
	void ImportTextureFromFile(const wstring &fname, 
		ID3D11Device5 *device, 
		ID3D11ShaderResourceView **texture_srv);

	/**
	 Exports the texture to the given file.

	 @pre			@a device_context is not equal to @c nullptr.
	 @pre			@a texture is not equal to @c nullptr.
	 @param[in]		fname
					A reference to the filename.
	 @param[in]		device_context
					A pointer to the device context.
	 @param[out]	texture_srv
					A pointer to the texture.
	 @throws		FormattedException
					Failed to export the texture to file.
	 */
	void ExportTextureToFile(const wstring &fname, 
		ID3D11DeviceContext4 *device_context, 
		ID3D11Resource *texture);
}