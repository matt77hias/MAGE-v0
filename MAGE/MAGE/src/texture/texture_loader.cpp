//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture_loader.hpp"
#include "texture\dds\dds_loader.hpp"
#include "logging\error.hpp"
#include "file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportTextureFromFile(const wstring &fname, ID3D11Device2 &device, ID3D11ShaderResourceView **texture_resource_view) {
		const wstring extension = GetFileExtension(fname);

		if (extension == L"dds" || extension == L"DDS") {
			return CreateDDSTextureFromFile(device, fname.c_str(), nullptr, texture_resource_view);
		}

		Warning("Unknown texture file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}