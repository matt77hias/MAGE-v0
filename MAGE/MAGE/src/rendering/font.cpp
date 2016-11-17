//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Font::Font(const wstring &name, uint16_t size, uint32_t bold, bool italic) 
		: m_vertex_buffer(nullptr), m_texture(nullptr) {

		// A handle to a bitmap.
		HBITMAP bitmap = nullptr;
		// A handle to a GDI object.
		// The Microsoft Windows graphics device interface (GDI) enables applications 
		// to use graphics and formatted text on both the video display and the printer.
		HGDIOBJ old_bitmap = nullptr;
		// A handle to a font.
		HFONT old_font = nullptr;

		BYTE *dst_row = nullptr;

		// Create a memory device context (DC) compatible with the application's current screen.
		HDC hDC = CreateCompatibleDC(nullptr);
		// Set the mapping mode of the specified device context.
		// MM_TEXT: Each logical unit is mapped to one device pixel.
		//			Positive x is to the right; positive y is down.
		SetMapMode(hDC, MM_TEXT);

		// Retrieve device-specific information for the specified device.
		// LOGPIXELSY:	Number of pixels per logical inch along the screen height. I
		//				In a system with multiple display monitors, this value is the same for all monitors.
		const char height = -MulDiv(size, GetDeviceCaps(hDC, LOGPIXELSY), 72);
		// Create the font.
		// 1. The height, in logical units, of the font's character cell or character.
		// 2. The width for which the font mapper chooses a closest match value.
		// 3. The angle, in tenths of degrees, between the escapement vector and the x-axis of the device.
		//	  The escapement vector is parallel to the base line of a row of text.
		// 4. The angle, in tenths of degrees, between each character's base line and the x-axis of the device.
		// 5. The weight of the font in the range 0 through 1000. For example, 400 is normal and 700 is bold.
		// 6. Specifies an italic font if set to true.
		// 7. Specifies an underlined font if set to true.
		// 8. A strikeout font if set to true.
		// 9. The character set.
		// 10. The output precision. 
		// 11. The clipping precision.
		// 12. The output quality.
		// 13. The pitch and family of the font.
		// 14. The typeface name of the font
		HFONT font = CreateFont(height, 0, 0, 0, bold, italic, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, name.c_str());
		if (font == nullptr)
			goto End;

		// Select an object into the specified device context (DC). 
		// The new object replaces the previous object of the same type.
		old_font = (HFONT)SelectObject(hDC, font);

		// Find the dimensions of the smallest texture to hold the characters.
		m_texture_width = m_texture_height = 128;
		while (!PrepareFont(hDC, true)) {
			m_texture_width  *= 2;
			m_texture_height *= 2;
		}

		// Create the texture descriptor.
		D3D11_TEXTURE2D_DESC texture_desc;
		ZeroMemory(&texture_desc, sizeof(texture_desc));
		texture_desc.Width	            = m_texture_width;				// Texture width (in texels).
		texture_desc.Height	            = m_texture_height;				// Texture height (in texels).
		texture_desc.MipLevels          = 1;							// The maximum number of mipmap levels in the texture.
		texture_desc.ArraySize          = 1;							// Number of textures in the texture array.
		texture_desc.Format             = DXGI_FORMAT_B4G4R4A4_UNORM;	// Texture format.
		texture_desc.SampleDesc.Count   = 1;							// The number of multisamples per pixel.
		texture_desc.SampleDesc.Quality = 0;							// The image quality level. (lowest)
		texture_desc.Usage              = D3D11_USAGE_DEFAULT;			// Value that identifies how the texture is to be read from and written to.
		texture_desc.BindFlags          = D3D11_BIND_CONSTANT_BUFFER;	// Flags for binding to pipeline stages. 
		texture_desc.CPUAccessFlags     = 0;							// No CPU access is necessary.
		texture_desc.MiscFlags          = 0;							// Flags that identify other, less common resource options.
		// Create the texture.
		const HRESULT result_texture = g_engine->GetRenderer()->CreateTexture2D(&texture_desc, nullptr, &m_texture);
		if (FAILED(result_texture)) {
			goto End;
		}

		// Prepare the bitmap.
		unsigned long *bitmap_bits;
		BITMAPINFO bitmap_info;
		ZeroMemory(&bitmap_info.bmiHeader, sizeof(BITMAPINFOHEADER));
		bitmap_info.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
		bitmap_info.bmiHeader.biWidth       =  (int)m_texture_width;
		bitmap_info.bmiHeader.biHeight      = -(int)m_texture_height;
		bitmap_info.bmiHeader.biPlanes      = 1;
		bitmap_info.bmiHeader.biCompression = BI_RGB;
		bitmap_info.bmiHeader.biBitCount    = 32;

		// Create a bitmap for the font.
		bitmap = CreateDIBSection(hDC, &bitmap_info, DIB_RGB_COLORS, (void**)&bitmap_bits, nullptr, 0);

		old_bitmap = SelectObject(hDC, bitmap);

		// Set the text properties.
		SetTextColor(hDC, RGB(255, 255, 255));
		SetBkColor(hDC, 0x00000000);
		SetTextAlign(hDC, TA_TOP);

		// Prepare the font by drawing the characters onto the bitmap.
		if (!PrepareFont(hDC)) {
			goto End;
		}

		// Lock the surface and write the alpha values for the set pixels.
		/*D3DLOCKED_RECT d3dlr;
		m_texture->LockRect(0, &d3dlr, 0, 0);
		dst_row = (BYTE*)d3dlr.pBits;
		WORD *dst16;
		BYTE alpha;
		for (uint32_t y = 0; y < m_texture_height; ++y) {
			dst16 = (WORD *)dst_row;
			for (uint32_t x = 0; x < m_texture_width; ++x) {
				alpha = (BYTE)((bitmap_bits[m_texture_width * y + x] & 0xff) >> 4);
				if (alpha > 0) {
					*dst16++ = (WORD)((alpha << 12) | 0x0fff);
				}
				else {
					*dst16++ = 0x0000;
				}
			}
			dst_row += d3dlr.Pitch;
		}*/

		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = 1020 * sizeof(TLVertex);  // Size of the buffer in bytes.
		buffer_desc.Usage          = D3D11_USAGE_DYNAMIC;	   // How the buffer is expected to be read from and written to.
		buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER; // How the buffer will be bound to the pipeline.
		buffer_desc.CPUAccessFlags = 0;				           // No CPU access is necessary.
		// Create the vertex buffer.
		const HRESULT result_vertex_buffer = g_engine->GetRenderer()->CreateBuffer(&buffer_desc, nullptr, &m_vertex_buffer);
		if (FAILED(result_vertex_buffer)) {
			goto End;
		}







	//	// Prepare the alpha testing for rendering the characters.
	//	g_engine->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0x08);
	//	g_engine->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//	// Create a state block for capturing the volatile render states.
	//	g_engine->GetDevice()->BeginStateBlock();
	//	g_engine->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	//	g_engine->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	//	g_engine->GetDevice()->SetRenderState(D3DRS_FOGENABLE, false);
	//	g_engine->GetDevice()->EndStateBlock(&m_states);

	// Clean up and return.
	End:
	//	if (m_texture)
	//		m_texture->UnlockRect(0);

	SelectObject(hDC, old_bitmap);
	SelectObject(hDC, old_font);
	DeleteObject(bitmap);
	DeleteObject(font);
	DeleteDC(hDC);
	}

	Font::~Font() {
		SAFE_RELEASE(m_texture);
		SAFE_RELEASE(m_vertex_buffer);
	}






	void Font::Render(char *text, float x, float y, XMFLOAT4 colour) {

	}

	bool Font::PrepareFont(HDC hDC, bool measure) {
		SIZE size;			// Receives the dimensions of the string, in logical units.
		wchar_t buffer[2];	// A buffer that specifies the text string.

		// Find the spacing between the characters based on the line height.
		
		// Compute the width and height of the specified string of text.
		if (GetTextExtentPoint32(hDC, buffer, 1, &size) == 0) {
			// On failure.
			return false;
		}

		m_spacing = (uint16_t)ceil(size.cy * 0.1f);

		// Set the position to start drawing at.
		uint32_t x = m_spacing;
		uint32_t y = 0;

		// Draw each character on the DC and move to the next position.
		for (char c = 32; c < 127; ++c) {
			buffer[0] = c;

			if (GetTextExtentPoint32(hDC, buffer, 1, &size) == 0) {
				// On failure.
				return false;
			}

			if ((uint32_t)(x + size.cx + m_spacing) > m_texture_width) {
				x = m_spacing;
				y += size.cy + 1;
			}

			// Ensure there is enough room to draw the character.
			if (y + size.cy > m_texture_height) {
				// On failure.
				return false;
			}

			// Draw the character if not measuring.
			if (!measure) {

				// Draw text using the currently selected font, background color, and text color. 
				// 1. A handle to the device context.
				// 2. The x-coordinate, in logical coordinates, of the reference point used to position the string.
				// 3. The y-coordinate, in logical coordinates, of the reference point used to position the string.
				// 4. The current background color should be used to fill the rectangle.
				// 5. A pointer to an optional RECT structure that specifies the dimensions, in logical coordinates, of a rectangle that is used for clipping, opaquing, or both.
				// 6. A pointer to a string that specifies the text to be drawn.
				// 7. The length of the string.
				// 8. A pointer to an optional array of values that indicate the distance between origins of adjacent character cells.
				if (ExtTextOut(hDC, x, y, ETO_OPAQUE, nullptr, buffer, 1, nullptr) == 0) {
					// On failure.
					return false;
				}

				m_texture_coords[c - 32][0] = (float)(x - m_spacing) / m_texture_width;
				m_texture_coords[c - 32][1] = (float)(y) / m_texture_height;
				m_texture_coords[c - 32][2] = (float)(x + size.cx + m_spacing) / m_texture_width;
				m_texture_coords[c - 32][3] = (float)(y + size.cy) / m_texture_height;
			}

			x += size.cx + (2 * m_spacing);
		}

		return true;
	}
}