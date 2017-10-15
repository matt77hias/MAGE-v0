//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "font\spritefont\spritefont_reader.hpp"
#include "font\spritefont\spritefont_tokens.hpp"
#include "texture\texture_utils.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteFontReader::SpriteFontReader(ID3D11Device2 *device, 
		SpriteFontOutput &output, const SpriteFontDescriptor &desc)
		: BigEndianBinaryReader(), m_device(device), 
		m_output(output), m_desc(desc) {

		Assert(device);
	}

	SpriteFontReader::SpriteFontReader(SpriteFontReader &&reader) = default;

	SpriteFontReader::~SpriteFontReader() = default;

	void SpriteFontReader::Read() {
	
		if (!IsHeaderValid()) {
			throw FormattedException(
				"%ls: invalid sprite font header.", GetFilename().c_str());
		}

		// Read glyphs.
		const U32 glyph_count   = ReadValue< U32 >();
		const Glyph *glyph_data = ReadValueArray< Glyph >(glyph_count);
		m_output.m_glyphs.assign(glyph_data, glyph_data + glyph_count);

		// Read font properties.
		m_output.m_line_spacing = ReadValue< F32 >();
		
		// Read default character.
		m_output.m_default_character 
			= static_cast< wchar_t >(ReadValue< U32 >());

		// Read texture.
		ReadTexture();
	}

	bool SpriteFontReader::IsHeaderValid() {
		const char *magic = MAGE_FONT_MAGIC;
		
		while (*magic != L'\0') {
			if (ReadValue< U8 >() != *magic) {
				return false;
			}
			++magic;
		}
		
		return true;
	}

	void SpriteFontReader::ReadTexture() {
		// Read texture data.
		const U32 texture_width     = ReadValue< U32 >();
		const U32 texture_height    = ReadValue< U32 >();
		const DXGI_FORMAT texture_format = m_desc.ForceSRGB() ? 
			ConvertToSRGB(ReadValue< DXGI_FORMAT >()) : ReadValue< DXGI_FORMAT >();
		const U32 texture_stride    = ReadValue< U32 >();
		const U32 texture_rows      = ReadValue< U32 >();
		const U8 *texture_data      = ReadValueArray< U8 >(
											texture_stride * texture_rows);

		// Create the texture descriptor.
		CD3D11_TEXTURE2D_DESC texture_desc(
			texture_format, texture_width, texture_height, 
			1, 1, D3D11_BIND_SHADER_RESOURCE, D3D11_USAGE_IMMUTABLE);
		
		// Create the texture data.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem     = texture_data;
		init_data.SysMemPitch = texture_stride;
		
		// Create the texture resource.
		ComPtr< ID3D11Texture2D > texture;
		const HRESULT result_texture = m_device->CreateTexture2D(
			&texture_desc, &init_data, texture.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_texture, "%ls: Texture creation failed: %08X.", 
			GetFilename().c_str(), result_texture);

		// Create the SRV descriptor.
		CD3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc(
			D3D11_SRV_DIMENSION_TEXTURE2D, texture_format);
		
		// Create the SRV.
		const HRESULT result_texture_srv = 
			m_device->CreateShaderResourceView(texture.Get(), 
				&shader_resource_view_desc, 
				m_output.m_texture_srv.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_texture_srv, "%ls: SRV creation failed: %08X.", 
			GetFilename().c_str(), result_texture_srv);
	}
}