#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_reader.hpp"
#include "font\sprite_font_output.hpp"
#include "font\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SpriteFontReader final : public BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpriteFontReader(ID3D11Device2 *device, SpriteFontOutput &output, const SpriteFontDescriptor &desc);
		SpriteFontReader(const SpriteFontReader &reader) = delete;
		SpriteFontReader(SpriteFontReader &&reader) = delete;
		virtual ~SpriteFontReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteFontReader &operator=(const SpriteFontReader &reader) = delete;
		SpriteFontReader &operator=(SpriteFontReader &&reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual HRESULT Read() override;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		bool IsHeaderValid();
		HRESULT ReadTexture();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11Device2 * const m_device;
		SpriteFontOutput &m_output;
		const SpriteFontDescriptor &m_desc;
	};
}