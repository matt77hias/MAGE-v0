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

	Texture::Texture(const wstring &fname)
		: Texture(GetRenderingDevice(), fname) {}

	Texture::Texture(ID3D11Device2 *device, const wstring &fname)
		: Resource< Texture >(fname, fname), m_device(device), m_texture_srv() {

		Assert(m_device);

		ImportTextureFromFile(GetFilename(), m_device, m_texture_srv.ReleaseAndGetAddressOf());
	}
}