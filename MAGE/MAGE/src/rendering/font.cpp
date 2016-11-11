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

	Font::Font(const wstring &name, uint16_t size, uint32_t bold, bool italic) {

		// A handle to a bitmap.
		HBITMAP bitmap = NULL;
		// A handle to a GDI object.
		// The Microsoft Windows graphics device interface (GDI) enables applications 
		// to use graphics and formatted text on both the video display and the printer.
		HGDIOBJ old_bitmap = NULL;
		// A handle to a font.
		HFONT old_font = NULL;

		BYTE *dst_row = NULL;
		uint32_t x, y;

		// Create a memory device context (DC) compatible with the application's current screen.
		HDC hDC = CreateCompatibleDC(NULL);
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
		if (font == NULL)
			goto End;

		// Select an object into the specified device context (DC). 
		// The new object replaces the previous object of the same type.
		old_font = (HFONT)SelectObject(hDC, font);

		// Find the dimensions of the smallest texture to hold the characters.
		m_texture_width = m_texture_height = 128;
		while (!PrepareFont(hDC, true)) {
			m_texture_width *= 2;
			m_texture_height *= 2;
		}

		// Create a new texture for the font
	//	if (FAILED(g_engine->GetDevice()->CreateTexture(m_textureWidth, m_textureHeight, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, &m_texture, NULL)))
	//		goto End;

	//	// Prepare the bitmap.
	//	unsigned long *bitmapBits;
	//	BITMAPINFO bmi;
	//	ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
	//	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//	bmi.bmiHeader.biWidth = (int)m_textureWidth;
	//	bmi.bmiHeader.biHeight = -(int)m_textureHeight;
	//	bmi.bmiHeader.biPlanes = 1;
	//	bmi.bmiHeader.biCompression = BI_RGB;
	//	bmi.bmiHeader.biBitCount = 32;

	//	// Create a bitmap for the font.
	//	bitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void**)&bitmapBits, NULL, 0);

	//	oldBitmap = SelectObject(hDC, bitmap);

	//	// Set the text properties.
	//	SetTextColor(hDC, RGB(255, 255, 255));
	//	SetBkColor(hDC, 0x00000000);
	//	SetTextAlign(hDC, TA_TOP);

	//	// Prepare the font by drawing the characters onto the bitmap.
	//	if (!PrepareFont(hDC))
	//		goto End;

	//	// Lock the surface and write the alpha values for the set pixels.
	//	D3DLOCKED_RECT d3dlr;
	//	m_texture->LockRect(0, &d3dlr, 0, 0);
	//	dstRow = (BYTE*)d3dlr.pBits;
	//	WORD *dst16;
	//	BYTE alpha;

	//	for (y = 0; y < m_textureHeight; y++)
	//	{
	//		dst16 = (WORD*)dstRow;
	//		for (x = 0; x < m_textureWidth; x++)
	//		{
	//			alpha = (BYTE)((bitmapBits[m_textureWidth*y + x] & 0xff) >> 4);
	//			if (alpha > 0)
	//				*dst16++ = (WORD)((alpha << 12) | 0x0fff);
	//			else
	//				*dst16++ = 0x0000;
	//		}
	//		dstRow += d3dlr.Pitch;
	//	}

	//	// Create the vertex buffer for the characters.
	//	g_engine->GetDevice()->CreateVertexBuffer(1020 * sizeof(TLVertex), D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_vb, NULL);

	//	// Prepare the alpha testing for rendering the characters.
	//	g_engine->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0x08);
	//	g_engine->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//	// Create a state block for capturing the volatile render states.
	//	g_engine->GetDevice()->BeginStateBlock();
	//	g_engine->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	//	g_engine->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	//	g_engine->GetDevice()->SetRenderState(D3DRS_FOGENABLE, false);
	//	g_engine->GetDevice()->EndStateBlock(&m_states);

	//	// Clean up and return.
	End:
		return;
	//	if (m_texture)
	//		m_texture->UnlockRect(0);

	//	SelectObject(hDC, oldBitmap);
	//	SelectObject(hDC, oldFont);
	//	DeleteObject(bitmap);
	//	DeleteObject(font);
	//	DeleteDC(hDC);
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
				if (ExtTextOut(hDC, x, y, ETO_OPAQUE, NULL, buffer, 1, NULL) == 0) {
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