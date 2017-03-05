#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture.hpp"
#include "texture\texture_loader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Texture::Texture(const RenderingDevice &device, const wstring &fname)
		: Resource(fname) {

		// Create the pixel shader.
		const HRESULT result_texture_import = ImportTextureFromFile(GetFilename(), device, m_texture_resource_view.ReleaseAndGetAddressOf());
		if (FAILED(result_texture_import)) {
			Error("Texture initialization failed: %ld.", result_texture_import);
			return;
		}
	}
}