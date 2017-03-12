#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_reader.hpp"
#include "rendering\rendering_device.hpp"
#include "sprite\sprite_font_output.hpp"
#include "sprite\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class FontReader : public BigEndianBinaryReader {

	public:

		FontReader(const RenderingDevice &device, SpriteFontOutput &output, const SpriteFontDescriptor &desc);
		virtual ~FontReader() = default;

		virtual HRESULT Read() override;

	protected:

		bool IsHeaderValid();
		HRESULT ReadTexture();

	private:

		FontReader(const FontReader &reader) = delete;
		FontReader &operator=(const FontReader &reader) = delete;

		const RenderingDevice &m_device;
		SpriteFontOutput &m_output;
		const SpriteFontDescriptor &m_desc;
	};
}