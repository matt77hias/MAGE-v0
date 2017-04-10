//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "font\spritefont\spritefont_reader.hpp"
#include "font\spritefont\spritefont_tokens.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteFontReader::SpriteFontReader(ID3D11Device2 *device, SpriteFontOutput &output, const SpriteFontDescriptor &desc)
		: BigEndianBinaryReader(), m_device(device), m_output(output), m_desc(desc) {}

	HRESULT SpriteFontReader::Read() {
	
		if (!IsHeaderValid()) {
			Error("%ls: invalid sprite font header.", GetFilename().c_str());
			return E_FAIL;
		}

		// Read glyphs.
		const uint32_t glyph_count = ReadValue< uint32_t >();
		const Glyph *glyph_data = ReadValueArray< Glyph >(glyph_count);
		m_output.m_glyphs.assign(glyph_data, glyph_data + glyph_count);

		// Read font properties.
		m_output.m_line_spacing = ReadValue< float >();
		
		// Read default character.
		m_output.m_default_character = static_cast< wchar_t >(ReadValue< uint32_t >());

		// Read texture.
		const HRESULT result_texture = ReadTexture();
		if (FAILED(result_texture)) {
			Error("%ls: failed to create texture: %08X.", GetFilename().c_str(), result_texture);
			return result_texture;
		}

		return S_OK;
	}

	bool SpriteFontReader::IsHeaderValid() {
		const char *magic = MAGE_FONT_MAGIC;
		while (*magic != L'\0') {
			if (ReadValue< uint8_t >() != *magic) {
				return false;
			}
			++magic;
		}
		return true;
	}

	HRESULT SpriteFontReader::ReadTexture() {
		// Read texture data.
		const uint32_t texture_width     = ReadValue< uint32_t >();
		const uint32_t texture_height    = ReadValue< uint32_t >();
		const DXGI_FORMAT texture_format = m_desc.ForceSRGB() ? ConvertToSRGB(ReadValue< DXGI_FORMAT >()) : ReadValue< DXGI_FORMAT >();
		const uint32_t texture_stride    = ReadValue< uint32_t >();
		const uint32_t texture_rows      = ReadValue< uint32_t >();
		const uint8_t *texture_data      = ReadValueArray< uint8_t >(texture_stride * texture_rows);

		// Create the texture descriptor.
		CD3D11_TEXTURE2D_DESC texture_desc(texture_format, texture_width, texture_height, 1, 1, D3D11_BIND_SHADER_RESOURCE, D3D11_USAGE_IMMUTABLE);
		// Create the texture data.
		D3D11_SUBRESOURCE_DATA init_data;
		ZeroMemory(&init_data, sizeof(init_data));
		init_data.pSysMem     = texture_data;
		init_data.SysMemPitch = texture_stride;
		// Create the texture resource.
		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = m_device->CreateTexture2D(&texture_desc, &init_data, texture.ReleaseAndGetAddressOf());
		if (FAILED(result_texture)) {
			Error("%ls: failed to create ID3D11Texture2D: %08X.", GetFilename().c_str(), result_texture);
			return result_texture;
		}

		// Create the shader resource view descriptor.
		CD3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc(D3D11_SRV_DIMENSION_TEXTURE2D, texture_format);
		// Create the shader resource view.
		const HRESULT result_shader_resource_view = m_device->CreateShaderResourceView(texture.Get(), &shader_resource_view_desc, m_output.m_texture.ReleaseAndGetAddressOf());
		if (FAILED(result_shader_resource_view)) {
			Error("%ls: failed to create ID3D11ShaderResourceView: %08X.", GetFilename().c_str(), result_texture);
			return result_shader_resource_view;
		}

		return S_OK;
	}
}