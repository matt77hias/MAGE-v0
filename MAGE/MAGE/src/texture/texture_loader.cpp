//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture_loader.hpp"
#include "directxtex\dds_texture_loader.hpp"
#include "file\file_utils.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportTextureFromFile(const wstring &fname, ID3D11Device2 *device, 
		ID3D11ShaderResourceView **texture_srv) {
		
		Assert(device);
		Assert(texture_srv);
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"dds" || extension == L"DDS") {
			
			ComPtr< ID3D11Device > device1;
			ComPtr< ID3D11Device2 > device2(device);
			const HRESULT result_device = device2.As(&device1);
			ThrowIfFailed(result_device,
				"ID3D11Device conversion failed: %08X.", result_device);

			const HRESULT result = DirectX::CreateDDSTextureFromFile(
				device1.Get(), fname.c_str(), nullptr, texture_srv);
			ThrowIfFailed(result, "Texture importing failed: %08X.", result);
		}
		else {
			throw FormattedException(
				"Unknown texture file extension: %ls", fname.c_str());
		}
	}
}