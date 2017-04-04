#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "resource\resource.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Texture : public FileResource {

	public:

		explicit Texture(ID3D11Device2 *device, const wstring &fname);
		Texture(Texture &&texture) = default;
		virtual ~Texture() = default;

		ID3D11ShaderResourceView *GetTextureResourceView() const {
			return m_texture_resource_view.Get();
		}
		ID3D11ShaderResourceView * const *GetTextureResourceViewAddress() const {
			return m_texture_resource_view.GetAddressOf();
		}

	private:

		Texture(const Texture &texture) = delete;
		Texture &operator=(const Texture &texture) = delete;
		Texture &operator=(Texture &&texture) = delete;

		ID3D11Device2 * const m_device;
		ComPtr< ID3D11ShaderResourceView > m_texture_resource_view;
	};

	SharedPtr< Texture > CreateTexture(const wstring &fname);
}