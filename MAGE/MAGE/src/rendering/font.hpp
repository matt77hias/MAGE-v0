#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Font {

	public:
		Font(const wstring &name = L"Arial", uint16_t size = 10, uint32_t bold = FW_NORMAL, bool italic = false);

		virtual ~Font();

		void Render(char *text, float x, float y, XMFLOAT4 colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	private:

		bool PrepareFont(HDC hDC, bool measure = false);

		ID3D11Buffer *m_vb; // Vertex buffer for rendering the text.
		ID3D11Texture2D *m_texture; // Direct3D texture for the font.
		uint32_t m_texture_width; // Width of the texture.
		uint32_t m_texture_height; // Height of the texture.
		float m_texture_coords[96][4]; // Character texture coordinates.
		uint16_t m_spacing; // Character pixel spacing per side.
	};
}