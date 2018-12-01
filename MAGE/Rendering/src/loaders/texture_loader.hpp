#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "direct3d11.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <filesystem>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	/**
	 Imports the texture from the file associated with the given path.

	 @param[in]		path
					A reference to the path.
	 @param[in,out]	device
					A reference to the device.
	 @param[out]	texture_srv
					A pointer to a pointer to a shader resource view.
	 @throws		Exception
					Failed to import the texture from file.
	 */
	void ImportTextureFromFile(const std::filesystem::path& path,
		                       ID3D11Device& device,
		                       NotNull< ID3D11ShaderResourceView** > texture_srv);

	/**
	 Exports the texture to the file associated with the given path.

	 @param[in]		path
					A reference to the path.
	 @param[in,out]	device_context
					A reference to the device context.
	 @param[in,out]	texture
					A reference to the texture.
	 @throws		Exception
					Failed to export the texture to file.
	 */
	void ExportTextureToFile(const std::filesystem::path& path,
		                     ID3D11DeviceContext& device_context,
		                     ID3D11Resource& texture);
}