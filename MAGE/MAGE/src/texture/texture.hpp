#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "rendering\rendering_device.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Texture : public FileResource {

	public:

		Texture(const RenderingDevice &device, const wstring &fname);
		virtual ~Texture() = default;

		ComPtr< ID3D11ShaderResourceView > GetTextureResourceView() const {
			return m_texture_resource_view;
		}

	private:

		Texture(const Texture &texture) = delete;
		Texture &operator=(const Texture &texture) = delete;

		ComPtr< ID3D11ShaderResourceView > m_texture_resource_view;
	};

	SharedPtr< Texture > CreateTexture(const wstring &fname);
}