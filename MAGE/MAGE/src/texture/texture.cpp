//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "texture\texture_loader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Texture::Texture(ID3D11Device2 *device, const wstring &fname)
		: FileResource(fname), m_device(device), m_texture_srv() {

		Assert(m_device);

		ImportTextureFromFile(GetFilename(), m_device, m_texture_srv.ReleaseAndGetAddressOf());
	}

	SharedPtr< Texture > CreateTexture(const wstring &fname) {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);
		
		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);
		
		return factory->CreateTexture(device, fname);
	}
}