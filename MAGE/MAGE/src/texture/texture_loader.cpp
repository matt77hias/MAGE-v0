//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture_loader.hpp"
#include "texture\dds\dds_loader.hpp"
#include "texture\dds\screen_grab.hpp"
#include "texture\wic\wic_loader.hpp"
#include "file\file_utils.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <wincodec.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportTextureFromFile(const wstring &fname, 
		ID3D11Device2 *device, 
		ID3D11ShaderResourceView **texture_srv) {
		
		Assert(device);
		Assert(texture_srv);
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"dds" || extension == L"DDS") {
			const HRESULT result = DirectX::CreateDDSTextureFromFile(
				device, fname.c_str(), nullptr, texture_srv);
			ThrowIfFailed(result, "Texture importing failed: %08X.", result);
		}
		else {
			const HRESULT result = DirectX::CreateWICTextureFromFile(
				device, fname.c_str(), nullptr, texture_srv);
			ThrowIfFailed(result, "Texture importing failed: %08X.", result);
		}
	}

	inline const GUID GetGUIDContainerFormat(const wstring &extension) noexcept {
		if (extension == L"png" || extension == L"PNG") {
			return GUID_ContainerFormatGif;
		}
		else if (extension == L"jpe"  || extension == L"JPE"
			  || extension == L"jpeg" || extension == L"JPEG"
			  || extension == L"jpg"  || extension == L"JPG") {
			return GUID_ContainerFormatJpeg;
		}
		else if (extension == L"tif"  || extension == L"TIF"
			  || extension == L"tiff" || extension == L"TIFF") {
			return GUID_ContainerFormatTiff;
		}
		else if (extension == L"gif"  || extension == L"GIF") {
			return GUID_ContainerFormatGif;
		}
		else if (extension == L"bmp"  || extension == L"BMP"
			  || extension == L"dib"  || extension == L"DIB") {
			return GUID_ContainerFormatBmp;
		}
		else if (extension == L"ico"  || extension == L"ICO") {
			return GUID_ContainerFormatIco;
		}
		else if (extension == L"hdp"  || extension == L"HDP"
			  || extension == L"wdp"  || extension == L"WDP"
			  || extension == L"jxr"  || extension == L"JXR") {
			return GUID_ContainerFormatWmp;
		}
		else {
			return GUID_NULL;
		}
	}

	void ExportTextureToFile(const wstring &fname,
		ID3D11DeviceContext2 *device_context,
		ID3D11Resource *texture) {

		Assert(device);
		Assert(texture);

		const wstring extension = GetFileExtension(fname);

		if (extension == L"dds" || extension == L"DDS") {
			const HRESULT result = DirectX::SaveDDSTextureToFile(
				device_context, texture, fname.c_str());
			ThrowIfFailed(result, "Texture exporting failed: %08X.", result);
		}
		else {

			const GUID format = GetGUIDContainerFormat(extension);
			if (GUID_NULL == format) {
				throw FormattedException(
					"Unknown image file extension: %ls", fname.c_str());
			}

			const HRESULT result = DirectX::SaveWICTextureToFile(
				device_context, texture, format, fname.c_str());
			ThrowIfFailed(result, "Texture exporting failed: %08X.", result);
		}
	}


}