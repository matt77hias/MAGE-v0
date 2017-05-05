//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture_loader.hpp"
#include "texture\dds\dds_loader.hpp"
#include "file\file_utils.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportTextureFromFile(const wstring &fname, ID3D11Device2 *device, ID3D11ShaderResourceView **texture_srv) {
		Assert(device);
		Assert(texture_srv);
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"dds" || extension == L"DDS") {
			const HRESULT result = CreateDDSTextureFromFile(device, fname.c_str(), nullptr, texture_srv);
			if (FAILED(result)) {
				throw FormattedException("Texture importing failed: %08X.", result);
			}
		}
		else {
			throw FormattedException("Unknown texture file extension: %ls", fname.c_str());
		}
	}
}