//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\texture_loader.hpp"
#include "loaders\dds\dds_loader.hpp"
#include "loaders\dds\screen_grab.hpp"
#include "loaders\wic\wic_loader.hpp"
#include "string\string_utils.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <wincodec.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	void ImportTextureFromFile(const std::filesystem::path& path, 
		                       ID3D11Device& device, 
		                       NotNull< ID3D11ShaderResourceView** > texture_srv) {
		
		std::wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L".dds" == extension) {
			const HRESULT result = DirectX::CreateDDSTextureFromFile(
				&device, path.c_str(), nullptr, texture_srv);
			ThrowIfFailed(result, "Texture importing failed: %08X.", result);
		}
		else {
			const HRESULT result = DirectX::CreateWICTextureFromFile(
				&device, path.c_str(), nullptr, texture_srv);
			ThrowIfFailed(result, "Texture importing failed: %08X.", result);
		}
	}

	/**
	 Returns the WIC container format associated with the given image file 
	 extension.

	 @param[in]		extension
					A reference to the (lower case) file extension.
	 @return		@c GUID_NULL if no WIC container format is associated with 
					the given file extension.
	 @return		The WIC container format associated with the given image
					file extension.
	 */
	[[nodiscard]]
	static inline const GUID 
		GetGUIDContainerFormat(const std::wstring& extension) noexcept {

		if (L".png" == extension) {
			return GUID_ContainerFormatPng;
		}
		else if (L".jpe"  == extension
			  || L".jpeg" == extension
			  || L".jpg"  == extension) {
			return GUID_ContainerFormatJpeg;
		}
		else if (L".tif"  == extension
			  || L".tiff" == extension) {
			return GUID_ContainerFormatTiff;
		}
		else if (L".gif"  == extension) {
			return GUID_ContainerFormatGif;
		}
		else if (L".bmp"  == extension
			  || L".dib"  == extension) {
			return GUID_ContainerFormatBmp;
		}
		else if (L".ico"  == extension) {
			return GUID_ContainerFormatIco;
		}
		else if (L".hdp"  == extension
			  || L".wdp"  == extension
			  || L".jxr"  == extension) {
			return GUID_ContainerFormatWmp;
		}
		else {
			return GUID_NULL;
		}
	}

	void ExportTextureToFile(const std::filesystem::path& path, 
		                     ID3D11DeviceContext& device_context, 
		                     ID3D11Resource& texture) {

		std::wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L".dds" == extension) {
			const HRESULT result = DirectX::SaveDDSTextureToFile(
				&device_context, &texture, path.c_str());
			ThrowIfFailed(result, "Texture exporting failed: %08X.", result);
		}
		else {

			const auto format = GetGUIDContainerFormat(extension);
			ThrowIfFailed((GUID_NULL != format), 
						  "Unknown image file extension: %ls", 
						  path.c_str());

			const HRESULT result = DirectX::SaveWICTextureToFile(
				&device_context, &texture, format, path.c_str());
			ThrowIfFailed(result, "Texture exporting failed: %08X.", result);
		}
	}
}