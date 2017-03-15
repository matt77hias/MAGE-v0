#pragma once

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

	Texture::Texture(const RenderingDevice &device, const wstring &fname)
		: FileResource(fname) {

		// Create the pixel shader.
		const HRESULT result_texture_import = ImportTextureFromFile(GetFilename(), device, m_texture_resource_view.ReleaseAndGetAddressOf());
		if (FAILED(result_texture_import)) {
			Error("Texture initialization failed: %08X.", result_texture_import);
			return;
		}
	}

	SharedPtr< Texture > CreateTexture(const wstring &fname) {
		const RenderingDevice device = GetRenderingDevice();
		ResourceFactory &factory = GetResourceFactory();
		return factory.CreateTexture(device, fname);
	}
}