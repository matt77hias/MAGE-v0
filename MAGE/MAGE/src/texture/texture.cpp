//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "texture\texture_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Texture::Texture(ComPtr< ID3D11Device2 > device, const wstring &fname)
		: FileResource(fname), m_device(device) {

		// Create the pixel shader.
		const HRESULT result_texture_import = ImportTextureFromFile(GetFilename(), *m_device.Get(), m_texture_resource_view.ReleaseAndGetAddressOf());
		if (FAILED(result_texture_import)) {
			Error("Texture initialization failed: %08X.", result_texture_import);
			return;
		}
	}

	SharedPtr< Texture > CreateTexture(const wstring &fname) {
		ComPtr< ID3D11Device2 > device = GetRenderingDevice();
		ResourceFactory &factory = GetResourceFactory();
		return factory.CreateTexture(device, fname);
	}
}